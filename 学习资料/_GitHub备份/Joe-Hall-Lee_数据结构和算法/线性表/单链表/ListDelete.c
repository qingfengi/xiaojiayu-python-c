#define ERROR 0
#define OK 1
/* 初始条件：链式线性表L已存在，1 <= i <= ListLength(L) */

typedef int ElemType;

typedef struct Node
{
	ElemType data;	   // 数据域
	struct Node *next; // 指针域
} Node;
typedef struct Node *LinkList;

/* 操作结果：删除 L 的第 i 个数据元素，并用 e 返回其值，L 的长度 -1 */
typedef int Status;

Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p, q;

	p = *L;
	j = 1;

	while (p->next && j < i)
	{
		p = p->next;
		++j;
	}

	if (!(p->next) || j > i)
		return ERROR;

	q = p->next;
	p->next = q->next;

	*e = q->data;
	free(q);

	return OK;
}
