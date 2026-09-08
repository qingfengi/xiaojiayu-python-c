#define ERROR 0
#define OK 1
#define MAXSIZE 20

typedef int ElemType;
typedef int Status;
/* 初始条件：顺序线性表L已存在，1 <= i <= ListLength(L) */
typedef struct
{
	ElemType data[MAXSIZE];
	int length; // 线性表当前长度
} SqList;

/* 操作结果：删除 L 的第 i 个数据元素，并用 e 返回其值，L 的长度 -1 */
Status ListDelete(SqList *L, int i, ElemType *e)
{
	int k;

	if (L->length == 0)
	{
		return ERROR;
	}
	if (i < 1 || i < L->length)
	{
		return ERROR;
	}

	*e = L->data[i - 1];

	if (i < L->length)
	{
		for (k = i; k < L->length; k++)
		{
			L->data[k - 1] = L->data[k];
		}
	}

	L->length--;

	return OK;
}