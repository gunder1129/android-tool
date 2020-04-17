#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <inttypes.h>
#include <stdbool.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FRAME_MAX_LEN	256
#define QUEUE_MAX_LEN	512

/* macroes for list */
#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/* queue structures */
typedef struct list_head
{
	struct list_head *prev, *next;
} list_head_t;

typedef struct data_entry
{
	list_head_t list;				/* link for the entry */
	int timer_id;				/* the timer handle for resend */
	uint8_t priority;				/* the priority of this message */
	uint8_t retries;				/* how many times retried for send */
	int len;						/* data length */
	uint8_t data[FRAME_MAX_LEN];	/* the data buffer */
} data_entry_t;

typedef struct queue
{
	pthread_mutex_t mutex;
	list_head_t empty_list;
	list_head_t busy_list;
	data_entry_t entry[QUEUE_MAX_LEN];
} queue_t;

/* helpers for list */
static inline void __list_add(list_head_t *new_head, list_head_t *prev, list_head_t *next)
{
	next->prev = new_head;
	new_head->next = next;
	new_head->prev = prev;
	prev->next = new_head;
}
/*向链表中添加一个节点*/
static inline void list_add(list_head_t *new_head, list_head_t *head)
{
	__list_add(new_head, head, head->next);
}

static inline void __list_del(list_head_t *prev, list_head_t *next)
{
	next->prev = prev;
	prev->next = next;
}
/*从链表中删除一个节点*/
static inline void list_del(list_head_t *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}
/*判断链表是否是空链表，只有头节点就是空链表*/
static inline int list_empty(const list_head_t *head)
{
	return head->next == head;
}

/*向链表中添加新的节点*/
static inline void list_append(list_head_t *new_head, list_head_t *head)
{
	list_head_t *list;
	data_entry_t *entry;
	data_entry_t *new_entry = (data_entry_t *)new_head;

	if (list_empty(head))
	{
		list_add(new_head, head);
		return;
	}

	list = head->next;
	while (list != head)
	{
		entry = (data_entry_t *)list;
	//	printf("old = %d, new = %d\n", entry->priority, new_entry->priority);

		/* smaller value means higher priority */
		if (entry->priority > new_entry->priority)
		{
			list_add(new_head, list->prev);
			return;
		}

		list = list->next;
	}

	/* current entry has the lowest proirty */
	list_add(new_head, head->prev);
}

/* queue APIs */
extern int queue_init(queue_t *queue);
extern int queue_delete(queue_t *queue, data_entry_t *entry);
extern int queue_is_empty(queue_t *queue);
extern data_entry_t *queue_get_first_entry(queue_t *queue);
extern data_entry_t *queue_append(queue_t *queue,const uint8_t *buf, int len,  uint8_t priority);
extern int getSize(queue_t *queue, int flag);
extern void printData(data_entry_t* entry);

#ifdef __cplusplus
}
#endif

#endif

