#include <stdlib.h>
#define OK 1

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
Status Push(LinkStack *s, ElemType e)
{
	LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode));
	p->data = e;
	p->next = s->top;
	s->top = p;
	s->count++;
	return OK;
}