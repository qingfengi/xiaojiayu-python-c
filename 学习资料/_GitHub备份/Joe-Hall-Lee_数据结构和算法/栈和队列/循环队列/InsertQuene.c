#define MAXSIZE 100

typedef int ElemType;
typedef struct
{
	ElemType *base; // 用于存放内存分配基地址，也可以用数组存放
	int front;
	int rear;
} cycleQuene;

InsertQuene(cycleQuene *q, ElemType e)
{
	if ((q->rear + 1) % MAXSIZE == q->front)
		return; // 队列已满
	q->base[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
}