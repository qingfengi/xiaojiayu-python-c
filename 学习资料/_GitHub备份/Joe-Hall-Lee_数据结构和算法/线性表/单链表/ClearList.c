#include <stdio.h>
#define OK 1;

typedef int Status;
typedef int ElemType;
typedef struct Node
{
	ElemType data;	   // Êý¾ÝÓò
	struct Node *next; // Ö¸ÕëÓò
} Node, *LinkList;

Status ClearList(LinkList *L)
{
	LinkList p, q;

	p = (*L)->next;

	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	(*L)->next = NULL;

	return OK;
}