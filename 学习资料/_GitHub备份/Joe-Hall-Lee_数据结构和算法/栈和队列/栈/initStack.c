#include <stdlib.h>
#define STACK_INIT_SIZE 100

typedef int ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
} sqStack;

void initStack(sqStack *s)
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!s->base)
		exit(0);
	s->top = s->base; // 最开始，栈顶就是栈底
	s->stackSize = STACK_INIT_SIZE;
}
