#include <stdio.h>

typedef int ElemType;

typedef struct QNode
{
	ElemType data;
	struct QNode *next;
} QNode, *QuenePtr;

typedef struct
{
	QuenePtr front, rear; // ¶ÓÍ·¡¢Î²Ö¸Õë
} LinkQuene;

InsertQuene(LinkQuene *q, ElemType e)
{
	QuenePtr p;
	p = (QuenePtr)malloc(sizeof(QNode));
	if (p == NULL)
		exit(0);
	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}