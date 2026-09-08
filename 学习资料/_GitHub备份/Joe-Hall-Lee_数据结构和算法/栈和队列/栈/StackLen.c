typedef int ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
} sqStack;

int StackLen(sqStack s)
{
	return (s.top - s.base);
}
