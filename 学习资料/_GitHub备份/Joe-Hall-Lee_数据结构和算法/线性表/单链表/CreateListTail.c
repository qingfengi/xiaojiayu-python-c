/* 尾插法建立单链表演示 */
#include <stdio.h>

/* 头插法建立单链表示例 */
typedef int ElemType;
typedef struct Node
{
	ElemType data;	   // 数据域
	struct Node *next; // 指针域
} Node, *LinkList;

void CreateListTail(LinkList *L, int n)
{
	LinkList p, r;
	int i;

	srand(time(0));

	*L = (LinkList)malloc(sizeof(Node));
	r = *L;

	for (i = 0; i < n; i++)
	{
		p = (Node *)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;

		r->next = NULL;
	}
}