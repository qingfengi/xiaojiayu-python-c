#define ERROR 0
#define OK 1
#define MAX_SIZE 1000

/* 删除在 L 中的第 i 个数据元素 */
typedef int Status;
typedef int ElemType;
typedef struct
{
	ElemType data; // 数据
	int cur;	   // 游标（Cursor）
} Component, StaticLinkList[MAX_SIZE];

Status ListDelete(StaticLinkList L, int i)
{
	int j, k;

	if (i < 1 || i > ListLength(L))
	{
		return ERROR;
	}

	k = MAX_SIZE - 1;

	for (j = 1; j <= i - 1; j++)
	{
		k = L[k].cur; // k1 = 1; k2 = 5
	}

	j = L[k].cur; // j = 2
	L[k].cur = L[j].cur;

	Free_SLL(L, j);

	return OK;
}

/* 将下标为 k 的空闲结点回收到备用链表 */
void Free_SLL(StaticLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

/* 返回 L 中数据元素个数 */
int ListLength(StaticLinkList L)
{
	int j = 0;
	int i = L[MAX_SIZE - 1].cur;

	while (i)
	{
		i = L[i].cur;
		j++;
	}

	return j;
}