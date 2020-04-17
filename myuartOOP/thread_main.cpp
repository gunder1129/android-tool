#include <stdio.h>
#include "SendThread.h"

int main()
{
    printf("main --->start--->\n");
    sp<SendThread> mSendThread;
    mSendThread = new SendThread;
    mSendThread->run("sendThread");
    int i;
    for (i = 1; i < 5; i++)
    {
        /* code */
        sleep(1);
        printf("main --->thread unblock\n");       
        mSendThread->unblock();//解除锁，才会进行SendThread::threadLoop--->send data打印
        printf("main --->i = %d\n\n", i);
    }
    
    return 0;
}