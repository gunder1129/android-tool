#ifndef _SINGLE_LIST_
#define _SINGLE_LIST_
#include <stdio.h>
typedef int DataType; //方便后面修改数据类型，有点像C++/JAVA中的泛型
typedef struct Node 
{
	DataType data;
	struct Node *next;
}Node;

Node* getptr(Node* head, int pos);
int getSize(Node* head);
bool insert(Node** head, int position, DataType d);
void unionList(Node *a, Node *b);
void print(DataType d);
void trave(Node *head, void(*fun)(DataType));
bool erase(Node **head, int pos);
void reverse(Node **head);
void deleteAll(Node **head);
#endif
