#define ERROR 0
#define OK 1
/* 初始条件：链式线性表 L 已存在，1 <= i <= ListLength(L) */

typedef int ElemType;

typedef struct Node
{
	ElemType data;	   // 数据域
	struct Node *next; // 指针域
} Node;
typedef struct Node *LinkList;

/* 操作结果：用e返回L中第i个数据元素的值 */
typedef int Status;

Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;

	p = L->next;
	j = 1;

	while (p && j < i)
	{
		p = p->next;
		++j;
	}

	if (!p || j > i)
	{
		return ERROR;
	}

	*e = p->data;

	return OK;
}