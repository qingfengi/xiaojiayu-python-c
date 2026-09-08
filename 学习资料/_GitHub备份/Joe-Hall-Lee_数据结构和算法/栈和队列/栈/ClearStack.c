typedef int ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
} sqStack;

ClearStack(sqStack *s)
{
	s->top = s->base;
}
