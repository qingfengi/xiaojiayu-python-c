#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef int Status;

// 二叉树的二叉链表结点结构定义
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 递归查找二叉排序树T中是否存在 key
// 指针 f 指向 T 的双亲，其初始值调用值为 NULL
// 若查找成功，则指针 p 指向该数据元素结点，并返回 TRUE
// 否则指针 p 指向查找路径上访问的最后一个结点，并返回 FALSE
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
	if (!T) // 查找不成功
	{
		*p = f;
		return FALSE;
	}

	else if (key == T->data) // 查找成功
	{
		*p = T;
		return TRUE;
	}

	else if (key < T->data)
		return SearchBST(T->lchild, key, T, p); // 在左子树继续查找

	else
		return SearchBST(T->rchild, key, T, p); // 在右子树继续查找
}

// 当二叉排序树 T 中不存在关键字等于 key 的数据元素时，插入 key 并返回 TRUE，否则返回 FALSE
Status InsertBST(BiTree *T, int key)
{
	BiTree p, s;
	if (!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;

		if (!p)		// 查找不到
			*T = s; // 插入 s 为新的根结点
		else if (key < p->data)
			p->lchild = s; // 插入 s 为左孩子
		else
			p->rchild = s; // 插入 s 为右孩子
		return TRUE;
	}

	else
		return FALSE; // 树中已有关键字相同的结点，不再插入
}
