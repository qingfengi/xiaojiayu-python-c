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

/* 操作结果：在 L 中第 i 个位置之前插入新的数据元素 e，L 的长度加 1 */
typedef int Status;
Status ListInsert(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = *L;
	j = 1;

	while (p && j < 1) // 用于寻找第 i 个结点
	{
		p = p->next;
		j++;
	}

	if (!p || j > 1)
	{
		return ERROR;
	}

	s = (LinkList)malloc(sizeof(Node));
	s->data = e;

	s->next = p->next;
	p->next = s;

	return OK;
}
