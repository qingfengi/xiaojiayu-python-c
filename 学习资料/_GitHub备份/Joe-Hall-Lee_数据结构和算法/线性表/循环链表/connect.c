// 假设 A、B 为非空循环链表的尾指针

typedef struct LinkList
{
	int data; // 数据域
	struct LinkList *next;
} *LinkList;

LinkList Connect(LinkList A, LinkList B)
{
	LinkList p = A->next; // 保存 A 表的头节点位置。

	A->next = B->next->next; // B 表的开始结点链接到 A 表尾

	free(B->next); // 释放 B 表的头结点，初学者容易忘记

	B->next = p;

	return B; // 返回新循环链表的尾指针
}