#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int ElemType;

typedef struct StackNode
{
	ElemType data; // 存放栈的数据
	struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct LinkStack
{
	LinkStackPtr top; // top 指针
	int count;		  // 栈元素计数器

} LinkStack;

typedef int Status;
Status Pop(LinkStack *s, ElemType *e)
{
	LinkStackPtr p;
	if (StackEmpty(*s)) // 判断是否为空栈
	{
		return ERROR;
	}

	*e = s->top->data;
	p = s->top;
	s->top = s->top->next;
	free(p);
	s->count--;
	return OK;
}