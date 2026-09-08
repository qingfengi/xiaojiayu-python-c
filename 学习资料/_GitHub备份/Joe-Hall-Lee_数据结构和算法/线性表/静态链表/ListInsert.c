#define MAX_SIZE 1000
#define ERROR 0
/* 在静态链表 L 中第 i 个元素之前插入新的数据元素 */
typedef int Status;
typedef int ElemType;

typedef struct
{
	ElemType data; // 数据
	int cur;	   // 游标（Cursor）
} Component, StaticLinkList[MAX_SIZE];

int Malloc_SLL(StaticLinkList space)
{
	int i = space[0].cur;
	if (space[0].cur)
	{
		space[0].cur = space[i].cur;
		// 把它的一个分量用来作为备用。
	}
	return i;
}
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
	int j, k, l;

	k = MAX_SIZE - 1; // 数组的最后一个元素

	if (i < 1 || i > ListLength(L) + 1)
	{
		return ERROR;
	}

	j = Malloc_SLL(L);
	if (j)
	{
		L[j].data = e;
		for (l = 1; l <= i - 1; l++)
		{
			k = L[k].cur;
		}
		L[j].cur = L[k].cur;
		L[k].cur = j;
	}
}