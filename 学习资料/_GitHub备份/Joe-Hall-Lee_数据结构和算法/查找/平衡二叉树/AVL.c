#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define LH 1
#define EH 0
#define RH -1

typedef int Status;

// 二叉树的二叉链表结点结构定义
typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 右旋转操作
void R_Rotate(BiTree *p)
{
	BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
}

// 左旋转操作
void L_Rotate(BiTree *p)
{
	BiTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}

// 左平衡操作
void LeftBalance(BiTree *T)
{
	BiTree L, Lr;
	L = (*T)->lchild;

	switch (L->bf)
	{
	case LH:
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		Lr = L->rchild;
		switch (Lr->bf)
		{
		case LH:
			(*T)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*T)->bf = L->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);
	}
}

// 右平衡操作
void RightBalance(BiTree *T)
{
	BiTree R, Rl;
	R = (*T)->rchild;

	switch (R->bf)
	{
	case RH:
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		Rl = R->lchild;
		switch (Rl->bf)
		{
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		case EH:
			(*T)->bf = R->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
	}
}

int InsertAVL(BiTree *T, int e, int *taller)
{
	// taller 变量存放，增加一个结点后，这棵树是否长高，长高了就不平衡了。
	if (!*T)
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE; // 默认长高
	}
	else
	{
		if (e == (*T)->data)
		{
			*taller = FALSE;
			return FALSE;
		}
		if (e < (*T)->data)
		{
			if (!InsertAVL(&(*T)->lchild, e, taller))
				return FALSE;
			if (*taller)
			{
				switch ((*T)->bf)
				{
				case LH:
					LeftBalance(T);
					*taller = FALSE;
					break;
				case EH:
					(*T)->bf = LH;
					*taller = TRUE;
					break;
				case RH:
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				}
			}
		}
		else
		{
			if (!InsertAVL(&(*T)->rchild, e, taller))
				return FALSE;
			if (*taller)
			{
				switch ((*T)->bf)
				{
				case LH:
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				case EH:
					(*T)->bf = RH;
					*taller = TRUE;
					break;
				case RH:
					RightBalance(T);
					*taller = FALSE;
					break;
				}
			}
		}
	}
}
