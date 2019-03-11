#include "cycleList.h"

int main()
{
	Node *rear = NULL;
	insert(&rear, 0, 8);
	insert(&rear, 0, 3);
	insert(&rear, 0, 19);
	insert(&rear, 0, 6);
	printf("\n==============main init=============\n");
	trave(rear, print);
	printf("\n==============erase init=============\n");
	erase(&rear, 1);
	trave(rear, print);
	printf("\n==============main end=============\n");
	return 0;
}
