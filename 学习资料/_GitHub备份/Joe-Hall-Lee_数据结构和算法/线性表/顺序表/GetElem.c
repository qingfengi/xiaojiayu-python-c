#define OK 1
#define ERROR 0

#define MAXSIZE 20

typedef int ElemType;

// Status 是函数的类型，其值是函数结果状态代码，如 OK 等。
typedef int Status;

// 初始条件：顺序线性表L已存在，1 <= i <= ListLength(L)
typedef struct
{
	ElemType data[MAXSIZE];
	int length; // 线性表当前长度
} SqList;

// 操作结果：用 e 返回 L 中第 i 个数据元素的值

Status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0 || i < 1 || i > L.length)
	{
		return ERROR;
	}
	*e = L.data[i - 1];

	return OK;
}