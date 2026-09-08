#define MAXSIZE 100

typedef int ElemType;
typedef struct
{
	ElemType *base; // 用于存放内存分配基地址，也可以用数组存放
	int front;
	int rear;
} cycleQuene;

DeleteQuene(cycleQuene *q, ElemType *e)
{
	if (q->front == q->rear)
		return; // 队列为空
	*e = q->base[q->front];
	q->front = (q->front + 1) % MAXSIZE;
}