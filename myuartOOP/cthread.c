#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *test_print(void *arg)//线程创建成功后会执行这个方法
{
    int i;
    for ( i = 0; i < 10; i++)
    {
         printf("cthread: test_print start--->i =  %d\n", i);
    }
    
    return arg;
}

int main()
{
    pthread_t main_tid;
	int err = pthread_create(&main_tid, NULL, test_print, NULL); //创建线程
    if(err < 0)
    {
        printf("cthread: pthread_create-->error\n");
        return -1;
    }
    //不会等test_print方法执行完，因为main方法跟test_print方法不在同一个线程
    printf("cthread:it's main process.\n");
    sleep(2);
    
    return 0;
}