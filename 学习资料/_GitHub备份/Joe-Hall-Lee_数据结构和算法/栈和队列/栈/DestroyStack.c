#include <stdlib.h>

typedef int ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
} sqStack;

DestroyStack(sqStack *s)
{
	int i, len;
	len = s->stackSize;
	for (i = 0; i < len; i++)
	{
		free(s->base);
		s->base++;
	}
	s->base = s->top = NULL;
	s->stackSize = 0;
}
