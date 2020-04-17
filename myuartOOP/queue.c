#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
/* init a queue */
int queue_init(queue_t *queue)
{
	int i;

	/* init the mutex */
	pthread_mutex_init(&queue->mutex, NULL);
	
	/* lock the queue */
	pthread_mutex_lock(&queue->mutex);

	/* init the list entry */
	INIT_LIST_HEAD(&queue->empty_list);
	INIT_LIST_HEAD(&queue->busy_list);

	/* insert all the entry in to the empty list */
	for (i = 0; i < QUEUE_MAX_LEN; i++)
		list_add(&queue->entry[i].list, &queue->empty_list);

	/* unlock the queue */
	pthread_mutex_unlock(&queue->mutex);

	return 0;
}

/* append one frame to the queue */
data_entry_t  *queue_append(queue_t *queue,const uint8_t *buf, int len,  uint8_t priority)
{
	list_head_t *list;
	data_entry_t *entry;

	/* check the data length */
	if (len > FRAME_MAX_LEN)
	{
		printf("%s: buffer too large, %d(max is %d).", __func__, len, FRAME_MAX_LEN);
		return NULL;
	}	

	/* lock the queue */
	pthread_mutex_lock(&queue->mutex);

	if (list_empty(&queue->empty_list))
	{
		printf("%s: no empty entry", __func__);
		pthread_mutex_unlock(&queue->mutex);
		return NULL;
	}

	/* get an empty entry */
	list = queue->empty_list.next;
	list_del(list);//从empty_list链表删掉当前的节点
	entry = (data_entry_t *)list;

	/* fill the entry */
	entry->priority = priority;
	entry->retries = 0;
	entry->len = len;
	memcpy(entry->data, buf, len);

	/* append the list to the tail of the busy list */
	list_append(list, &queue->busy_list);

	/* unlock the queue */
	pthread_mutex_unlock(&queue->mutex);

	return entry;
}

/* remove one frame from the queue */
int queue_delete(queue_t *queue, data_entry_t *entry)
{
	list_head_t *list;

	/* lock the queue */
	pthread_mutex_lock(&queue->mutex);

	list = &entry->list;
	list_del(list);
	list_add(list, &queue->empty_list);
	
	/* unlock the queue */
	pthread_mutex_unlock(&queue->mutex);

	return 0;
}

/* check if queue is empty */
int queue_is_empty(queue_t *queue)
{
	return list_empty(&queue->busy_list);
}

/* get the first entry from the busy list */
data_entry_t *queue_get_first_entry(queue_t *queue)
{
	data_entry_t *entry = NULL;

	if (queue_is_empty(queue))
		return NULL;

	/* lock the queue */
	pthread_mutex_lock(&queue->mutex);

	entry = (data_entry_t *)queue->busy_list.next;

	/* unlock the queue */
	pthread_mutex_unlock(&queue->mutex);

	return entry;
}

/* 获取对应链表的长度，即节点个数*/
int getSize(queue_t *queue, int flag){
	list_head_t  *head, *tmp;
	int size = 0;
	if (flag == 0)//empty_list
	{
		head = &queue->empty_list;
	}else
	{
		head = &queue->busy_list;
	}
		
	pthread_mutex_lock(&queue->mutex);
	if (list_empty(head))
	{
		printf("size is 0\n");
		return size;
	}
	
	for (tmp = head->next; tmp != head; tmp = tmp->next)
	{
		size++;
	}
	pthread_mutex_unlock(&queue->mutex);
	return size;
	
}

void printData(data_entry_t* entry){
	 if (entry)
    {
        printf("len = %d\n", entry->len);
        int i = 0;
        if(entry->len > 0)printf("data: ");
        for (; i < entry->len; i++)
        {
            printf(" %u\t", entry->data[i]);
        }
        printf("\n");
    }
}

