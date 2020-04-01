/**********************************************************************
 Description: uart communications
 Author: Gunder
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define  MCUUARTPORT "/dev/ttyLP3"

int main()
{

	int fd;	
	printf("main start--->\n");
	printf(" init dev start\n");
	//打开设备/dev/ttyMT1
	fd= open(MCUUARTPORT, O_RDWR | O_NDELAY | O_NOCTTY|O_NONBLOCK); 
	if (-1 == fd) 
	{
		printf("open serial port %s fail %d\n", MCUUARTPORT, fd);
		return fd;
	}

	fcntl(fd, F_SETFL, 0);//设置文件状态标志值为０,阻塞模式
	printf("set baudrate\n");

	//设置波特率
	struct termios options;	
    memset(&options, 0x00, sizeof(options));

    if (0 != tcgetattr(fd, &options))//获得串口属性
    { 
      printf("%s error\n", __FUNCTION__);
      return -1;
    }

    tcflush(fd, TCIOFLUSH);//刷新输入输出缓冲区
    cfsetispeed(&options, B115200);//设置输入速度为115200
    cfsetospeed(&options, B115200);//设置输出速度为115200
    if (0 != tcsetattr(fd, TCSANOW, &options))//设置串口属性
    {
      printf("---- tc setattr error\n");
      return -1;
    }
    tcflush(fd, TCIOFLUSH);//刷新输入输出缓冲区
	
	//串口属性配置
	printf("set properties\n");
	 memset(&options, 0x00, sizeof(options));
	if (0 != tcgetattr(fd, &options))//获得串口属性
    {
		printf("tcgetattr failed-->1\n");
		return -1;
    }

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CRTSCTS;
	options.c_iflag &= ~(IXON | IXOFF | IXANY);
	options.c_iflag &= IGNCR;
	options.c_oflag &= ~OPOST;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 0;
    tcflush(fd, TCIFLUSH);//刷新输入缓冲区

    if (0 != tcsetattr(fd, TCSANOW, &options))//设置串口属性
    {
		printf("tcgetattr failed-->2\n");
		return -1;
    }
#if 0	
	//向串口写数据
	int len;
	printf("mcu_reboot start\n");
	unsigned char write_data[] = { 1, 4, 2, 2, 1, 3, 133, 232, 0 };
	len = write(fd, &write_data[0], 9);//执行后mcu会重启，不同的平台可能对应的协议不一样，写入的值就不一样

	
	printf("mcu_open_lcd start\n");
	unsigned char write_data[] = { 7, 8, 9, 2, 2, 82, 231, 0 };
	len = write(fd, &write_data[0], 8);//执行后会打开lcd，不同的平台可能对应的协议不一样，写入的值就不一样
	if (len > 0)
	{
		printf("len = %d, mcu will reboot or lcd\n", len);
	}
	else
	{
		printf("write failed\n");
		tcflush(fd, TCOFLUSH);
	}
#endif

#if 1	
	//向串口读数据
	printf("read start-->\n");
	FILE* fp;
	fp = fopen("/data/gan.log", "a+");
	if (fp == NULL)
	{
		printf("fopen failed\n");
	}
	//freopen("/data/gunder.txt", "a", stdout); setbuf(stdout, NULL);//将标准输出重定向到/data/gunder.txt
    //freopen("/data/gunder.txt", "a", stderr); setbuf(stderr, NULL);//将标准出错重定向到/data/gunder.txt
	
	int j = 1;
	while(1){//由于不是每次都能读取到数据，所以要在循环中不断去读取
		static uint8_t recv_buf[512];
		int readLen = read(fd, recv_buf, 512);	
		if (readLen < 0)
		{
			printf("read failed\n");
			return -1;
		}
		
		 if(readLen == -1 || readLen == 0)
        {
            continue;//读取不到数据，就结束本次循环，进入下一次循环进行重新读取
        }
		printf("readLen = %d\n", readLen);
		for(int i =0; i <readLen; i++)
		{
			//fprintf(fp, "%02x ",recv_buf[i]);//将从串口端读取到的数据写入到fp指向的文件中
			printf("%02x ",recv_buf[i]);//打印从串口端读取到的数据			
		}
		j++;
		printf("\n");		
		usleep(10 * 1000);//睡眠10毫秒
		if (j > 10)break;//读取完10条数据就跳出while循环
	}
#endif	
	
	close(fd);
	printf("main end\n");
	return 0;
}
