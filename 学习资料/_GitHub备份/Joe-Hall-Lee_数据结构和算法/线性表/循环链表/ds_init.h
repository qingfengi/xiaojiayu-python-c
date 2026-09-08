#pragma once
#include <stdio.h>
#include <stdlib.h>
/* 链表存储结构的定义 */
typedef struct CLinkList
{
	int data; // 数据域
	struct CLinkList *next;
} node;

/* 初始化循环链表 */
void ds_init(node **pNode);
