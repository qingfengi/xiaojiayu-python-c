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

DestroyQuene(LinkQuene *q)
{
	while (q->front)
	{
		q->rear = q->front->next;
		free(q->front);
		q->front = q->rear;
	}
}