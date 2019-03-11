#include <stdlib.h>
#include "SingleList.h"

Node* getptr(Node* head, int pos)
{
	Node *p = head;
	if (p == NULL || pos == 0)
	{
		return head;
	}
	for (int i = 0; p && i < pos; i++)
	{
		p = p->next;
	}
	return p;
}

int getSize(Node* head)
{
	int size = 0;
	Node *p = head;
	while(p)
	{
		size++;
		p = p->next;
	}
	return size;
}

bool insert(Node** head, int position, DataType d)
{
	if (position < 0 || position > getSize(*head))
	{
		return false;
	}

	Node *node = (Node*)malloc(sizeof(Node));
	node->data = d;
	node->next = NULL;
	if (position == 0)
	{
		node->next = *head;
		*head = node;
		return true;
	}
	Node *p = getptr(*head, position - 1);
	Node *r = p->next;
	node->next = r;
	p->next = node;
	return true;
}

void unionList(Node *a, Node *b)
{
	Node *p = a;
	while(p->next)
		p = p->next;
	p->next = b;
}

void print(DataType d)
{
	printf("%d\t", d);
}

void trave(Node *head, void(*fun)(DataType))
{
	Node *p = head;
	while(p)
	{
		fun(p->data);
		p = p->next;
	}
}

bool erase(Node **head, int pos)
{
	if (pos < 0 || pos >= getSize(*head))
	{
		return false;
	}
	Node *p = *head;
	if (pos == 0)
	{
		*head = (*head)->next;
		free(p);
		p = NULL;
		return true;
	}
	p = getptr(*head, pos - 1);
	Node *q = p->next;
	p->next = q->next;
	free(q);
	q = NULL;
	return true;
}

void reverse(Node **head)
{
	Node *p = *head;
	Node *q = p->next;
	if (q == NULL)
		return;
	Node *r = q->next;
	if (p == *head)
		p->next = NULL;
	while(true)
	{
		q->next = p;
		if (r == NULL)
		{
			*head = q;
			break;
		}
		else
		{
			p = q;
			q = r;
			r = r->next;
		}
	}
}

void deleteAll(Node **head)
{
	Node *tmp, *n, *h;
	if (head == NULL)
		return;
	h = *head;
	for (tmp = h->next; tmp != NULL; tmp = n)
	{
		n = tmp->next;
		free(tmp);		
	}
	free(h);
	*head = NULL;
}





