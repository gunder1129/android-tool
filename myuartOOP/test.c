#include <stdio.h>
#include "queue.h"
#define IS_EMPTY_LIST 0
#define IS_BUSY_LIST 1
/*打印empty_list跟busy_list链表的长度，即节点个数，总数为512*/
void print_all_list_size(queue_t *queue, int index){
    printf("busy_list size%d = %d\n", index, getSize(queue, IS_BUSY_LIST));
    printf("empty_list size%d = %d\n", index, getSize(queue, IS_EMPTY_LIST));
    printf("\n");
}

int main()
{
    queue_t g_queue_send_data;
    queue_init(&g_queue_send_data);//初始化的时候empty_list链表会添加512个节点
    uint8_t data[FRAME_MAX_LEN];
    int i = 0, len = 8;
    uint8_t p = 48, tmp = 100;
    print_all_list_size(&g_queue_send_data, 0);
    for ( i ; i < 8; i++)
    {
        data[i] = i * 2;
    }
    //调用queue_append会从empty_list链表中删除一个节点，在busy_list链表中添加一个节点，节点总数还是512
    if (NULL == queue_append(&g_queue_send_data, data, len, p)) {//在busy_list链表中添加第一个节点
         printf("insert data error!\n");
        return -1;
    }

    data_entry_t* entry;
    entry = queue_get_first_entry(&g_queue_send_data);
    printData(entry);//打印busy_list链表的第一个节点数据

    print_all_list_size(&g_queue_send_data, 1);

    for ( i = 0; i < len + 1; i++)
    {
        data[i] = i * 2 + 1;
    }

    if (NULL == queue_append(&g_queue_send_data, data, len + 1, p + 1)) {//在busy_list链表中添加第二个节点
         printf("insert data error2!\n");
        return -1;
    }

    entry = queue_get_first_entry(&g_queue_send_data);
    printData(entry);//还是打印busy_list链表的第一个节点数据

    print_all_list_size(&g_queue_send_data, 2);
    
    printf("delete first data\n");

    //删掉第一个节点信息，其实是删除一个busy_list链表中的first节点，并且在empty_list中添加一个节点
    queue_delete(&g_queue_send_data, entry);

    entry = queue_get_first_entry(&g_queue_send_data);//获取第一个节点，因为之前删掉了第一个节点，所以这里获取的其实是第二个节点
    printData(entry);//打印busy_list链表的第一个节点数据，就是删除节点前的第二个节点数据
    print_all_list_size(&g_queue_send_data, 3);
    
    return 0;
}