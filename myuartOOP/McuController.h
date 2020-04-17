/*
 * McuController.h
 *
 */

#ifndef MCUCONTROLLER_H_
#define MCUCONTROLLER_H_
#include <utils/Singleton.h>
#include <utils/threads.h>
#include "UartInterface.h"


#define CRC_LEN			2
#define APP_REPLY_LEN	2
#define APP_REPLY_ERROR	0x80
#define APP_REPLY_OK	0x00

#define APP_WRITE_ERROR	0x80
#define APP_WRITE_MASK	0x7F

#define SEND_TYPE_ACK	1
#define SEND_TYPE_DATA	0

#define SENT_TYPE_MASK	0x7F

#define ACK_CKSUM_OK	0x00
#define ACK_CKSUM_ERROR	0x01
#define ACK_PRIORITY	0
#define ACK_FRM_LEN_MPU		5

#define COMMAND_MASK	0x7F
#define SN_MASK			0xF0
#define RET_MASK		0x0F
#define PRIORITY_MASK	0x0F
#define ACK_LEN			5

#define SEND_MAX_RETRIES	1
#define RESEND_TIME			40
#define _PULSE_CODE_IPC_SEND_MSG  _PULSE_CODE_MINAVAIL+20

#define CMD_MAX			16
#define SMD_MAX			32

#define MCU_INIT_SMD    1
#define MCU_INIT_CMD    0

namespace android {


typedef int (*notify_callback)(int cmd,int smd,uint8_t *data,int len);

static bool g_InitSendStatus =false;
static bool g_InitReceStatus =false;
static bool g_InitMcuStatus =false;
static uint8_t g_InitData[256] ;
static int g_InitLen=0;

class SendThread :public Thread{
public:
    virtual bool threadLoop() ;
    void  block();
    void unblock();
	Condition  mCondition;
	Mutex  mConditionMutex;

};

class ReceiveThread :public Thread{
public:
    virtual bool threadLoop() ;
    void  block();
    void unblock();

	Condition  mCondition;
	Mutex  mConditionMutex;

};


class McuController:public Singleton<McuController> {//单例模式，在android命名空间里面
public:
	McuController();
	virtual ~McuController();
	void send(int cmd,int smd,uint8_t *data, size_t len);
	static void init();//初始启动串口线程的收发线程和缓冲
    void initUart();//初始化串口
    void deiniUart();//关闭串口
    void initThread();//初始化收发线程
    bool isInitFinish();
	int txdata(uint8_t* data, size_t len);//向串口发送数据
	int rxdata(uint8_t* data, size_t len);//从串口接收数据
	sp<SendThread> mSendThread;//发送线程定义指针变量，sp属于android命名空间里面定义
	sp<ReceiveThread> mReceiveThread;//接收线程定义指针变量，sp属于android命名空间里面定义
private:
	UartInterface*  mUart;

};

} /* namespace android */
#endif /* MCUCONTROLLER_H_ */
