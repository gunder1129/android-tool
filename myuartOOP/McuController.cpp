/*
 * McuController.cpp
 *
 */
#define LOG_TAG "McuController"
#include "McuController.h"
#include <errno.h>
#include <log/log.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "DataFrame.h"
#include "cobs.h"
#include "queue.h"
//#include "DataBuffManager.h"
#include <android-base/properties.h>
#include <cutils/properties.h>
#include <sys/stat.h>

//#define TEST_D 1			// 对数据的传输流进行测试，设置是不进行串口操作。
#define CAR_TYPE_FILE_PATH "/backconf/carType.txt"
#define PARTION_FORMAT_PATH "/data/partionformat.txt"

namespace android {
queue_t g_queue_send_data;     //发送队列
queue_t g_queue_sent_data;     //已发送队列
queue_t g_queue_receive_data;  //接收队列
pthread_mutex_t time_mutex;    //定时器互斥锁
// static bool g_parking_status =false;
notify_callback g_CallbackFun;  // mcu_service 中设置进来用于通知，上层应用的notify回调
// McuBuffer *p_testRxbuf = NULL;	//接收缓冲仅用于数据测试
static bool g_heartbeat_status = false;
static int g_heartbeat_count = 0;  //计数心跳次数

static bool g_update_mcu = false;


/**根据 命令号累加计算每个命令的流水号
 *	@param uint8_t cmd 主命令号
 *	@param uint8_t smd  子命令号
 *	@return uint8_t 返回流号
 *
 */
static uint8_t get_seq_number(uint8_t cmd, uint8_t smd) {
    static uint8_t sequence_number[CMD_MAX][SMD_MAX];
    static uint8_t invalid = 0;

    if ((cmd >= CMD_MAX) || (smd >= SMD_MAX)) {
        if (invalid >= 13) {
            invalid = 0;
        } else {
            invalid++;
        }
        return invalid;
    }

    if (sequence_number[cmd][smd] >= 13) {
        sequence_number[cmd][smd] = 0;
    } else {
        sequence_number[cmd][smd] += 1;
    }
    return (sequence_number[cmd][smd]);
}

/**
 * 从指定的数据中找到一帧cobs编码数据
 *@param uint8_t *buf 输入的数据指针
 *@param	int *len  输入的数据长度
 *@param int *frm_size 返回找到的cobs编码数据包长度
 *@return int 0表示找到数据包
 *						-1 表示没有找到数据包
 */
static int get_one_frame(uint8_t* buf, int* len, int* frm_size) {
    int i;
    int ret = -1;
    int frame_found = 0;
    uint8_t* p = buf;

    /* check if frame seperater exist */
    for (i = 0; i < *len; i++) {
        if (*p == 0) {
            p++;
            frame_found = 1;
            break;
        }

        p++;
    }

    /* found a frame */
    if (frame_found) {
        ret = 0;
        *frm_size = i + 1;
        *len -= (i + 1);
    }

    return ret;
}

/**
 * 把已发送的数据包加重新加到队列进行重发
 * @param queue_t *queue 要加入的队列
 * @param uint8_t *buf 要加入的数据包
 * @param len 要加入的数据包长度
 * @param uint8_t retries已重发的次数，目前只重发1 次
 * @return int -1 表示加入队列失败
 * 					 0 表示加入队列成功
 */
int append_resend(queue_t* queue, uint8_t* buf, int len, uint8_t retries) {
    list_head_t* list;
    data_entry_t* entry;

    /* check the data length */
    if (len > FRAME_MAX_LEN) {
        return -1;
    }

    /* lock the queue */
    pthread_mutex_lock(&queue->mutex);

    if (list_empty(&queue->empty_list)) {
        pthread_mutex_unlock(&queue->mutex);
        return -1;
    }

    /* get an empty entry */
    list = queue->empty_list.next;
    list_del(list);
    entry = (data_entry_t*)list;

    /* fill the entry */
    entry->priority = buf[4] & PRIORITY_MASK;
    entry->retries = retries;
    entry->len = len;
    memcpy(entry->data, buf, len);

    /* append the list to the suitable position in the busy list */
    list_append(list, &queue->busy_list);

    /* unlock the queue */
    pthread_mutex_unlock(&queue->mutex);

    return 0;
}

/**
 * 调用callBack接口，通知上层应用收到一个新的数据包
 */
static void reply_ipc_read(void) {
    data_entry_t* entry;

    /* get the first entry in the receive queue */
    entry = queue_get_first_entry(&g_queue_receive_data);
    if (entry) {
        DataFrame frame;
        frame.setFrameData(entry->data, entry->len);

        if (frame.getCmd() == MCU_INIT_CMD && frame.getSmd() == MCU_INIT_SMD) {
            printf(" reply_ipc_read----->mcu init success!\n");
            g_InitMcuStatus = true;
        }

        if (frame.getCmd() == 0x02 && frame.getSmd() == 0x00) {
            printf(" reply_ipc_read----->mcu status heartbeat----g_heartbeat_count=%d\n", g_heartbeat_count);
            g_heartbeat_status = true;
            g_heartbeat_count++;
        }

        printf(" reply_ipc_read----->rec data: cmd=0x%02x smd=0x%02x \n",frame.getCmd(),frame.getSmd());
        for(int i=0; i < frame.getDataLen();i++){
        	printf(" 0x%02x",frame.getData()[i]);
        }
        printf("\n");
        /* delete the entry from the queue */
        queue_delete(&g_queue_receive_data, entry);
    }
}

/* append the ack frame to the send queue */
int send_ack(uint8_t cmd, uint8_t smd, uint8_t sn) {
    DataFrame frame;
    frame.setAck(cmd, smd, sn);
    /* append the data to the send queue */
    if (NULL == queue_append(&g_queue_send_data, frame.getFrame(), ACK_FRM_LEN_MPU, ACK_PRIORITY)) {
        return -1;
    }

    /* wake up send task */
   McuController::getInstance().mSendThread->unblock();

    return 0;
}



/* analysis the frame received from MCU */
static void received_one_frame(uint8_t* buf, int size) {
    // uint8_t *cobs_dst_buf;
    uint8_t cmd, smd, sn;  // priority;//,ret;
    // uint16_t check_sum;
    // int len;

    Cobs cobs;
    cobs.setCobsData(buf, size);
    cobs.unStuffData();

    DataFrame frame;
    frame.setFrameData(cobs.getData(), cobs.getDataLength());
    if (frame.getFrameLen() == 0) {  // ERROR frame
        printf("received_one_frame:errro framerame.getFrameLen() ==0%s %d\n", __FUNCTION__, __LINE__);
        return;
    }
    cmd = frame.getCmd();
    smd = frame.getSmd();
    sn = frame.getSn();

    uint8_t ret = frame.getPriorityRet();  // add by max
    printf("received_one_frame: cmd =%02x smd =%02x sn =%02x ret=%02x\n",cmd,smd,sn,ret);//add by max

    if (frame.getCt() == SEND_TYPE_ACK) /* the ack from mcu */
    {
        // received_ack(cmd, smd, sn);
    } else /* data packet from mcu */
    {
        {
            printf("received_one_frame: queue_append  data---\n");
            if (NULL == queue_append(&g_queue_receive_data, frame.getFrame(), frame.getFrameLen(),
                                     frame.getPriorityRet())) {
                printf("received_one_frame:frame queue_append error data---\n");
            }
            reply_ipc_read();
        }
        send_ack(cmd, smd, sn);
    }
}

ANDROID_SINGLETON_STATIC_INSTANCE(McuController)

/**
 * 初始化对队列，建立缓冲区
 */
static void init_queue() {
    queue_init(&g_queue_send_data);
    queue_init(&g_queue_sent_data);
    queue_init(&g_queue_receive_data);
}

pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * 阻塞当前线程
 */
void SendThread::block() {
    pthread_mutex_lock(&clifd_mutex);
}

/**
 * 唤醒当前线程
 */
void SendThread::unblock() {
    pthread_mutex_unlock(&clifd_mutex);
}

/**
 * 发送数据的线程队列
 */
bool SendThread::threadLoop() {
    data_entry_t* entry;
    int ret;
    DataFrame frame;
    Cobs cobs;

    while (1) {
        g_InitSendStatus = true;
        printf("\nSendThread::threadLoop() before block---->\n");
        block();
        printf("SendThread::threadLoop() after block---->\n");
        while (1) {
            usleep(10 * 1000);  //间隔发送
            entry = queue_get_first_entry(&g_queue_send_data);//获取队列中第一个节点数据
            if (NULL == entry) {
                break;
            }

            frame.setFrameData(entry->data, entry->len);
            cobs.setData(frame.getFrame(), frame.getFrameLen());//进行cobs封装
            cobs.stuffData();
            
            ret = McuController::getInstance().txdata(cobs.getCobsData(), cobs.getCobsDataLength());//向串口发送（写）数据

            if (ret != -1) {
                queue_delete(&g_queue_send_data, entry);//删除队列中第一个节点数据，以便下次获取下一个节点数据
                printf("SendThread::threadLoop() send received ---ret=%d,cmd=%02x,smd=%02x\n", ret, frame.getCmd(),
                      frame.getSmd());
            } else /* low level error, re-init the uart */
            {
                printf("SendThread::threadLoop() send received error ---ret=%d,cmd=%02x,smd=%02x\n", ret, frame.getCmd(),
                      frame.getSmd());
                McuController::getInstance().deiniUart();
            }
        } /* END while (1) */
    }     // while
    printf("exit send thread!");
    return false;
}

/**
 * 接收数据的线程
 */
bool ReceiveThread::threadLoop() {
    static uint8_t recv_buf[FRAME_MAX_LEN];
    int len;
    int total_len = 0;
    int frame_size;
    int readLen = -1;

    while (1) {
        /* receive raw data from UART */
        len = sizeof(recv_buf) - total_len;
        // printf("ReceiveThread::threadLoop--->len=%d\n",len);
		
        /*从串口端接收收据*/
        readLen = McuController::getInstance().rxdata(recv_buf + total_len, len);

        if (readLen == 0) {//如果没有接收到数据，一秒后继续新的接收
            usleep(10 * 1000);
            //printf("ReceiveThread::threadLoop--->uart return readLen==0\n");
            continue;
        }
        if (readLen == -1) {
            printf("ReceiveThread::threadLoop--->uart read error!\n");
            //McuController::getInstance().deiniUart();
            total_len = 0;
            continue;
        }
        total_len += readLen;
        printf("ReceiveThread::threadLoop--->len=%d, readLen = %d\n",len, readLen);
        /* decode one frame from the raw buffer */
        while (1) {
            if (0 == get_one_frame(recv_buf, &total_len, &frame_size)) {//从指定的数据中找到一帧cobs编码数据
                printf("ReceiveThread::threadLoop---> found one frame!\n");
                received_one_frame(recv_buf, frame_size);//解析获取的数据，即cobs解码
                if (total_len > 0) memmove(recv_buf, recv_buf + frame_size, total_len);
            } else {
                printf("ReceiveThread::threadLoop--->not found frame!\n");
                break;
            }
        }
    }
    printf("ReceiveThread::threadLoop--->exit receive thread!\n");
    return false;
}
/**
 * 阻塞当前线程
 */
void ReceiveThread::block() {
    AutoMutex _l(mConditionMutex);
    mCondition.wait(mConditionMutex);
}

/**
 * 唤醒当前线程
 */
void ReceiveThread::unblock() {
    AutoMutex _l(mConditionMutex);  //读取加锁
    mCondition.broadcast();         //读取线程唤醒
}


bool McuController::isInitFinish() {
    return g_InitMcuStatus;
}

McuController::McuController() {
    mSendThread = new SendThread;
    mReceiveThread = new ReceiveThread;
}

/**
 * 用于上层发送数据给MCU.这些数据由上层传下来，在底层组包
 * @param int cmd 要发送的主命令
 * @param int smd 要发送的子命令
 * @param uint8_t *data 要发送的用户数据可以为NULL
 * @param size_t len 要发送的用户数据长度
 */
void McuController::send(int cmd, int smd, uint8_t* data, size_t len) {
    
    if (len > 200) {
        printf("----McuController::send too big len");
        return;
    }

    DataFrame frame;
    uint8_t sn = get_seq_number(cmd, smd);
    frame.setData(SEND_TYPE_DATA, cmd, smd, sn, ACK_PRIORITY, data, len);//数据封装，会进行CRC检验
    if (NULL == queue_append(&g_queue_send_data, frame.getFrame(), frame.getFrameLen(),
                             frame.getPriorityRet())) {
        return;
    } else {
        McuController::getInstance().mSendThread->unblock();//解锁，mSendThread->block()的地方会继续往下执行
        printf("McuController::send cmd = %02x, smd = %02x, data[0] = %u, len = %zu\n",cmd, smd, data[0], len);
    }
}


McuController::~McuController() {
    // TODO Auto-generated destructor stub
}

/**
 * 初始化串口
 */
void McuController::initUart() {
    mUart = new UartInterface();
}

/**
 * 关闭串口
 */
void McuController::deiniUart() {
    delete mUart;
    mUart = NULL;
    printf("------------------- deiniUart  by max ------------- \n");
    if (!g_update_mcu) {
        mUart = new UartInterface();
        printf("deiniUart complete!");
    }
}

/**
 *启动接收线程和发送线程
 */
void McuController::initThread() {
    mReceiveThread->run("receiveThread");
    mSendThread->run("sendThread");
}


/**
 * 初始启动串口线程的收发线程和缓冲
 */
void McuController::init() {
    printf("----------------McuController::init--------------\n");

    /* init the send/receive queue */
    init_queue();
    McuController::getInstance().initUart();//初始化串口
    McuController::getInstance().initThread();//初始化收发线程
    pthread_mutex_init(&time_mutex, NULL);
}

/* 向串口发送数据*/
int McuController::txdata(uint8_t* data, size_t len) {
	return mUart->txdata(data, len);
}

/* 从串口端接收数据*/
int McuController::rxdata(uint8_t* data, size_t len) {
	return mUart->rxdata(data, len);
}

} /* namespace android */