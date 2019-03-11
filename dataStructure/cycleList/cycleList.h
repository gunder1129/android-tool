#ifndef _CYCLE_LIST_
#define _CYCLE_LIST_
#include <stdlib.h>
#include <stdio.h>

typedef int DataType;
typedef struct Node{
	DataType data;
	struct Node *next;
}Node;

int getSize(Node *rear);
Node *getptr(Node *rear, int pos);
bool insert(Node **rear, int position, DataType d);
bool erase(Node **rear, int pos);
void print(DataType d);
void trave(Node *rear, void(*fun)(DataType));



#endif
