// n 个人围圈报数，报 m 出列，最后剩下的是几号？
#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
typedef struct node
{
	int data;
	struct node *next;
} node;

node *create(int n)
{
	node *p = NULL;
	node *head = NULL;
	head = (node *)malloc(sizeof(node));
	p = head;
	node *s = NULL;
	int i = 1;

	if (0 != n)
	{
		while (i <= n)
		{
			s = (node *)malloc(sizeof(node));
			s->data = i++; // 为循环链表初始化，第一个结点为 1，第二个结点为 2。
			p->next = s;
			p = s;
		}
		s->next = head->next;
	}

	free(head);

	return s->next;
}

int main()
{
	int n = 41;
	int m = 3;
	int i;
	node *p = create(n);
	node *temp;

	m %= n; // m 在这里是等于 3

	while (p != p->next)
	{
		for (i = 1; i < m - 1; i++)
		{
			p = p->next;
		}

		printf("%d->", p->next->data);
		temp = p->next; // 删除第 m 个结点
		p->next = temp->next;

		free(temp);

		p = p->next;
	}

	printf("%d\n", p->data);

	return 0;
}