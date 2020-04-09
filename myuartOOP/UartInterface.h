#ifndef MYUART_UARTINTERFACE_H
#define MYUART_UARTINTERFACE_H
#include <termios.h>
#include "HardInterface.h"

#define  MCUUARTPORT  "/dev/ttyLP3"
#define  BAUDRATEINDEXMAX 9
#define  BAUDRATEINDEX    8
#define  GET_BAUDRATEINDEX(index) ( (BAUDRATEINDEXMAX - 1) & index) 
#define TIMEOUT_SEC(buflen, baudrate)    ((buflen)*20/(baudrate) + 2)
#define TIMEOUT_USEC    0
//波特率数组
static const int speed_arr[] = { B300, B1200, B2400, B4800, B9600, B19200,
                                   B38400, B57600, B115200 };
//根据枚举钟不同的值设置不同的串口属性
enum UARTPROPERTI{ SERIAL_STOPBITS_ONE, SERIAL_STOPBITS_TWO, SERIAL_DATABITS_SEVEN, \
    SERIAL_DATABITS_EIGHT, SERIAL_HARDWARE_UNCTRL, SERIAL_HARDWARE_XONXOFF, \
    SERIAL_HARDWARE_CTRL, SERIAL_PARITY_NONE, SERIAL_PARITY_ODD, SERIAL_PARITY_EVEN, \
    SERIAL_PARITY_MARK, SERIAL_PARITY_SPACE };

static const int name_arr[] = { 300, 1200, 2400, 4800, 9600, 19200, 38400,
                               57600, 115200 };

class UartInterface : public HardInterface
{
private:
    bool uart_error;/* data */
public:
    UartInterface(/* args */)
    {
        init_dev();
    }
    ~UartInterface(){
        uart_close(this->fd);
    }
    int init_dev();//设备初始化
    int txdata(unsigned char* txbuf, unsigned int txcount);//向串口发送数据
    int rxdata(unsigned char* rxbuf, unsigned int rxcount);//接收来自串口端的数据
    int uart_sest_baudrate(int handle, int baudrateindex);//设置波特率
    //设置串口属性
    int uart_set_properties(int handle, unsigned char databits, unsigned char stopbits, \
        unsigned char parity, unsigned char flow_control);
    //关闭对应的文件描述符
    int uart_close(int handle);
};


#endif