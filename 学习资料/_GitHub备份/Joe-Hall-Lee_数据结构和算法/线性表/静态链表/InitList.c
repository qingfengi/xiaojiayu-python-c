#define MAXSIZE 1000
#define OK 1
/* 在静态链表L中第i个元素之前插入新的数据元素 */
typedef int Status;
typedef int ElemType;

typedef struct
{
	ElemType data;  // 数据
	int cur;  //游标(Cursor)
}Component, StaticLinkList[MAXSIZE];

Status InitList(StaticLinkList space)
{
	int i;
	for (i = 0; i < MAXSIZE - 1; i++)
	{
		space[i].cur = i + 1;
	}
	space[MAXSIZE - 1].cur = 0;

	return OK;
}