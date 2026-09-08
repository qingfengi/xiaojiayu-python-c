#include <stdio.h>
#define OK 1;

typedef int Status;
typedef int ElemType;
typedef struct Node
{
	ElemType data;	   // 数据域
	struct Node *next; // 指针域
} Node, *LinkList;

Status GetMidNode(LinkList L, ElemType *e)
{
	LinkList search, mid;
	mid = search = L;

	while (search->next != NULL)
	{
		// search 移动的速度是 mid 的两倍
		if (search->next->next != NULL)
		{
			search = search->next->next;
			mid = mid->next;
		}
		else
		{
			search = search->next;
		}
	}

	*e = mid->data;

	return OK;
}