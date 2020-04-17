#include <stdio.h>
#include <unistd.h>
#include "SendThread.h"

pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * 阻塞当前线程
 */
void SendThread::block() {
    printf("SendThread::block------>\n");
    pthread_mutex_lock(&clifd_mutex);
}

/**
 * 唤醒当前线程
 */
void SendThread::unblock() {
    printf("SendThread::unblock------>\n");
    pthread_mutex_unlock(&clifd_mutex);
}

/**
 * 发送数据的线程队列
 */
bool SendThread::threadLoop() {
    printf("SendThread::threadLoop--->\n\n");
    int i = 0;
    while (1)
    {
        if (i > 10)
        {
            break;
        }
        printf("SendThread::threadLoop--->before send data---->\n");
        block();
        i++;
        printf("SendThread::threadLoop--->send data = %d\n", i);
        sleep(1);
    }

    return false;
}