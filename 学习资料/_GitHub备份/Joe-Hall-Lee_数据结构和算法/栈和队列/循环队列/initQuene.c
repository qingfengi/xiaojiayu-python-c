#define MAXSIZE 100

typedef int ElemType;
typedef struct
{
	ElemType *base; // 用于存放内存分配基地址，也可以用数组存放
	int front;
	int rear;
} cycleQuene;

initQuene(cycleQuene *q)
{
	q->base = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
	if (!q->base)
		exit(0);
	q->front = q->rear = 0;
}