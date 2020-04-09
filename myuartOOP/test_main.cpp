#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "UartInterface.h"

//向串口写数据
static void mcu_reboot() {
    printf("mcu_reboot start\n");
    unsigned char write_data[] = { 1, 4, 2, 2, 1, 3, 133, 232, 0 };
    UartInterface *u = new UartInterface();
    int tx = u->txdata(write_data, 9);
    sleep(3);
    printf("mcu_reboot tx = %d\n", tx);
}
//向串口读数据
static void mcu_read_data() {
    printf("mcu_read_data start\n");
    static uint8_t recv_buf[512];
    UartInterface *u = new UartInterface();
    int j = 1;
    while(1){//由于不是每次都能读取到数据，所以要在循环中不断去读取
        int readLen = u->rxdata(recv_buf, 512);	
        if (readLen < 0)
        {
            printf("read failed\n");
            return ;
        }      
        if(readLen == -1 || readLen == 0)
        {
            continue;//读取不到数据，就结束本次循环，进入下一次循环进行重新读取
        }
        printf("readLen = %d\n", readLen);
        for(int i =0; i <readLen; i++)
        {
            printf("%02x ",recv_buf[i]);//打印从串口端读取到的数据			
        }
        j++;
        printf("\n");		
        usleep(10 * 1000);//睡眠10毫秒
        if (j > 10)break;//读取完10条数据就跳出while循环
    }
    printf("mcu_read_data tr\n");
}

int main(int argc, char **argv)
{
    printf("main start ---> \n");
    if (argc > 1)
    {       
        printf("argv[1] = %s\n", argv[1]);
        if (strncmp(argv[1], "w", 1) ==  0)
        {
            printf("main write data\n");
            mcu_reboot();//执行后mcu会重启
        }               
        else if (strncmp(argv[1], "r", 1) == 0)
        {
            printf("main read data\n");
            mcu_read_data();//执行后会打印接收到的数据
        }                      
     
        printf("\n");
    }
    printf("main start ---> \n");
    return 0;
}