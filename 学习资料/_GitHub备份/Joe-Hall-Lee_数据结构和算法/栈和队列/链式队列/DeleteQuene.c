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

DeleteQuene(LinkQuene *q, ElemType *e)
{
	QuenePtr p;
	if (q->front == q->rear)
		return;
	p = q->front->next;
	*e = p->data;
	q->front->next = p->next;
	if (q->rear == p)
		q->rear = q->front;
	free(p);
}