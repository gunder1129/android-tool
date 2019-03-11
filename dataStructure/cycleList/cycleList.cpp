#include "cycleList.h"

int getSize(Node *rear)
{
	int size = 0;
	if (rear)
	{
		Node *p = rear->next;
		while (p != rear)
		{
			size++;
			p = p->next;
		}
		size++;
	}
	return size;
}

Node *getptr(Node *rear, int pos)
{
	if (rear == NULL)
	{
		return rear;
	}
	if (pos >= getSize(rear))
	{
		return NULL;	
	}
	Node *p = rear->next;
	for(int i = 0; i < pos; i++)
	{
		p = p->next;
	}
	return p;
}

bool insert(Node **rear, int position, DataType d)
{
	if (position < 0 || position > getSize(*rear))
	{
		return false;
	}
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = d;
	node->next = NULL;
	if (position == 0)
	{
		if (*rear == NULL)
		{
			node->next = node;
			*rear = node;
		}
		else
		{
			node->next = (*rear)->next;
			(*rear)->next = node;
		}
		return true;
	}	
	Node *p = getptr(*rear, position - 1);
	Node *r = p->next;
	node->next = r;
	p->next = node;
	if (*rear == p)
	{
		*rear = node;	
	}
	return true;
}

bool erase(Node **rear, int pos)
{
	if (*rear == NULL || pos < 0 || pos >= getSize(*rear))
	{
		return false;
	}
	Node *p = (*rear)->next;
	if (pos == 0)
	{
		(*rear)->next = p->next;
		free(p);
		p = NULL;
		return true;
	}

	p = getptr(*rear, pos - 1);
	Node *q = p->next;
	p->next = q->next;
	if (q == *rear)
	{
		*rear = p;
	}
	free(q);
	q = NULL;
	return true;
}

void print(DataType d)
{
	printf("%d\t", d);
}

void trave(Node *rear, void(*fun)(DataType))
{
	if (rear == NULL)
		return;
	Node *p = rear->next;
	while(p != rear)
	{
		fun(p->data);
		p = p->next;
	}
	fun(p->data);
}


