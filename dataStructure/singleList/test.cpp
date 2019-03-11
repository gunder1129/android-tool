#include "SingleList.h"
#include <stdio.h>

int main()
{
	Node *head = NULL;
	insert(&head, 0, 9);	
	insert(&head, 0, 8);
	insert(&head, 0, 3);
	insert(&head, 0, 11);
	printf("init------------>\n");
	trave(head, print);
	int len = getSize(head);
	printf("\n getSize = %d\n", len);
	bool b = erase(&head, 2);
	if (b)
	{
		printf("erase--------->\n");
		trave(head, print);
	}
	printf("\n reverse------------->\n");
	reverse(&head);
	trave(head, print);
	
	printf("\n head2-------init-->\n");
	
	Node *head2 = NULL;
	insert(&head2, 0, 20);	
	insert(&head2, 0, 22);
	insert(&head2, 0, 14);
	insert(&head2, 0, 19);
	trave(head2, print);
	printf("\n unionList--------->\n");
	unionList(head, head2);
	trave(head, print);
	printf("\n deleteAll--------->\n");
	deleteAll(&head);
	trave(head, print);
	printf("\n----main end -----\n");
	
	return 0;
}


