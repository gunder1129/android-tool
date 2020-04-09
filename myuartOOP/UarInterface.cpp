#include <errno.h>
#include <linux/fb.h>
#include <unistd.h>
#include "UartInterface.h"

//初始化设备
int UartInterface::init_dev()
{
    int ret = 0;
    this->uart_error = false;
    printf("UartInterface--> init dev start--\n");
    this->fd = open(MCUUARTPORT, O_RDWR | O_NDELAY | O_NOCTTY | O_NONBLOCK);
    if (-1 == this->fd)
    {
        printf("UartInterface--> open serial port %s fail %d--\n", MCUUARTPORT, this->fd);
        this->uart_error = true;
        return this->fd;
    }

    fcntl(fd, F_SETFL, 0);//设置文件状态标志值为０,阻塞模式
    //设置波特率
    ret = uart_sest_baudrate(this->fd, GET_BAUDRATEINDEX(BAUDRATEINDEX));
    if (ret == -1)
    {
         printf("UartInterface--> uart_sest_baudrate %s fail %d\n", MCUUARTPORT, ret);
         this->uart_error = true;
         return ret;
    }
    //串口属性配置
    ret = uart_set_properties(this->fd, SERIAL_DATABITS_EIGHT, SERIAL_STOPBITS_ONE, \
    SERIAL_PARITY_NONE, SERIAL_HARDWARE_UNCTRL);
    if (ret == -1)
    {
         printf("UartInterface--> uart_set_properties %s fail %d\n", MCUUARTPORT, ret);
         this->uart_error = true;
         return ret;
    }
    printf("UartInterface--> init dev end--\n");
    return 0;
}

//向串口发送数据
int UartInterface::txdata(unsigned char* txbuf, unsigned int txcount)
{
    unsigned char* write_data = txbuf;
    unsigned int total_len = 0;
    int len =0;
    unsigned int size = txcount;
    if ( this->fd <= 0)
    {
        printf("UartInterface-->txdata fd = %d litter zero\n", this->fd);
        return this->fd;
    }
    for (total_len = 0; total_len < size;)
    {
        len = write(this->fd, &write_data[total_len], size - total_len);
        if (len > 0)
        {
            total_len += len;
        }
        else if (len < 0)
        {
            if (total_len == 0)
            {
                tcflush(this->fd, TCOFLUSH);//清除正写入的数据，且不会发送至终端。
                return -1;
            }
            return total_len;
        }else
        {
            printf("UartInterface-->txdata len = %d \n", len);
            break;
        }
               
    }//for
    return 0;
}

//从串口读取数据
int UartInterface::rxdata(unsigned char* rxbuf, unsigned int rxcount)
{
    if (this->fd <= 0)
    {
        printf("UartInterface-->rxdata fd = %d \n", this->fd);
        return -1;
    }
    int len = read(this->fd, rxbuf, rxcount);
    if (len < 0)
    {
        printf("UartInterface-->rxdata len = %d \n", len);
        return -1;
    }
    return len;
    
}

//设置波特率
int UartInterface::uart_sest_baudrate(int handle, int baudrateindex)
{
    struct termios options;
    memset(&options, 0x00, sizeof(options));
    if (baudrateindex >= BAUDRATEINDEXMAX)
    {
        printf("UartInterface--> ot support BAUDRATEINDEXMAX %d", BAUDRATEINDEXMAX);
        return -1;
    }
    
    if (tcgetattr(handle, &options) != 0)
     {
        printf("UartInterface--> tcgetattr error\n");
        return -1;
    }
    tcflush(this->fd, TCIOFLUSH);//刷新输入输出缓冲区
    cfsetispeed(&options, speed_arr[baudrateindex]);//设置输入速度
    cfsetospeed(&options, speed_arr[baudrateindex]);//设置输出速度

    if (tcsetattr(handle, TCSANOW, &options)  != 0)//设置串口属性，TCSANOW：不等数据传输完毕就立即改变属性
    {
        printf("UartInterface--> tcsetattr \n");
        return -1;
    }
    
    tcflush(this->fd, TCIOFLUSH);//刷新输入输出缓冲区
    return 0;
    
}

//设置串口属性
int UartInterface::uart_set_properties(int handle, unsigned char databits, unsigned char stopbits, \
    unsigned char parity, unsigned char flow_control)
{
    struct termios options;
    if (this->fd <= 0)
    {
        printf("UartInterface--> fd litter zero \n");
        return -1;
    }
    memset(&options, 0x00, sizeof(options));
    if (tcgetattr(handle, &options) != 0)
    {
        printf("UartInterface--> tcgetattr error \n");
        return -1;
    }
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;

    switch (stopbits) 
    {
        case SERIAL_STOPBITS_ONE:
            options.c_cflag &= ~CSTOPB;
            break;
        case SERIAL_STOPBITS_TWO:
            options.c_cflag |= CSTOPB;
            break;
        default:
            return -1;
    }

    switch (databits)
    {
        case SERIAL_DATABITS_SEVEN:
            options.c_cflag |= CS7;
            break;
        case SERIAL_DATABITS_EIGHT:
            options.c_cflag |= CS8;
            break;
        default:
            return -1;
    }

    switch (flow_control) 
    {
        case SERIAL_HARDWARE_UNCTRL:
            options.c_cflag &= ~CRTSCTS;
            options.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        case SERIAL_HARDWARE_XONXOFF:
            options.c_iflag |= IXON | IXOFF | IXANY;
            break;
        case SERIAL_HARDWARE_CTRL:
            options.c_cflag |= CRTSCTS;
            options.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        default:
            return -1;
    }
    options.c_iflag &= IGNCR;

    switch (parity)
    {
        case SERIAL_PARITY_NONE:
            options.c_cflag &= ~PARENB;
            break;
        case SERIAL_PARITY_ODD:
            options.c_cflag |= PARENB;
            options.c_cflag |= PARODD;
            break;
        case SERIAL_PARITY_EVEN:
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            break;
        case SERIAL_PARITY_MARK:
            options.c_cflag &= ~PARENB;
            options.c_cflag |= CSTOPB;
            break;
        case SERIAL_PARITY_SPACE:
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;
        default:
            return -1;
    }

    options.c_oflag &= ~OPOST;

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 0;//VTIME和VMIN都取0，即使读取不到任何数据，函数read也会立即返回
    tcflush(this->fd, TCIFLUSH);//刷新输入缓冲区

    if (0 != tcsetattr(handle, TCSANOW, &options)) //设置串口属性
    {
        printf("UartInterface--> tcsetattr error \n");
        return -1;
    }

    return 0; 
}

int UartInterface::uart_close(int handle)
{
    printf("UartInterface--> uart_close \n");
    close(handle);
    return 0;
}

