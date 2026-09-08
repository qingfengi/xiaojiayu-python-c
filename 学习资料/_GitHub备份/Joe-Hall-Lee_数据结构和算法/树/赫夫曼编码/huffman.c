#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "queue.h"

void traverseTree(htNode *treeNode, hlTable **table, int k, char code[256])
{
	if (treeNode->left == NULL && treeNode->right == NULL)
	{
		code[k] = '\0';
		hlNode *aux = (hlNode *)malloc(sizeof(hlNode));
		aux->code = (char *)malloc(sizeof(char) * (strlen(code) + 1));
		strcpy(aux->code, code);
		aux->symbol = treeNode->symbol;
		aux->next = NULL;

		if ((*table)->first == NULL)
		{
			(*table)->first = aux;
			(*table)->last = aux;
		}
		else
		{
			(*table)->last->next = aux;
			(*table)->last = aux;
		}
	}

	if (treeNode->left != NULL)
	{
		code[k] = '0';
		traverseTree(treeNode->left, table, k + 1, code);
	}
	if (treeNode->right != NULL)
	{
		code[k] = '1';
		traverseTree(treeNode->right, table, k + 1, code);
	}
}

hlTable *buildTable(htTree *huffmanTree)
{
	hlTable *table = (hlTable *)malloc(sizeof(hlTable));
	table->first = NULL;
	table->last = NULL;

	char code[256];
	int k = 0;

	traverseTree(huffmanTree->root, &table, k, code);
	return table;
}

htTree *buildTree(char *inputString) // 建立 Huffman 树
{
	// 初始化
	int *probability = (int *)malloc(sizeof(int) * 256); // 整数数组
	for (int i = 0; i < 256; i++)
		probability[i] = 0; // 整数数组初始化
	// 统计待编码的字符串各个字符出现的次数
	for (int j = 0; inputString[j] != '\0'; j++)
		probability[(unsigned char)inputString[j]]++; // 当读入的字符串不结束时，一直循环，对应ASCII编码的整数下标的数组元素+1

	pQueue *huffmanqueue;
	initPQueue(&huffmanqueue); // 生成并初始化 Huffman 树队列

	// 填充队列
	for (int k = 0; k < 256; k++)
	{
		if (probability[k] != 0) // probablity[k] != 0 说明 k 整数对应的 ASCII 码存在于字符串中
		{
			htNode *aux = (htNode *)malloc(sizeof(htNode));
			aux->left = NULL;
			aux->right = NULL;
			aux->symbol = (char)k; // 将整数转换为字符

			addPQueue(&huffmanqueue, aux, probability[k]); // Huffman 树结点入队，数组元素的值即为权值，插入时就排序了
		}
	}

	free(probability); // 释放数组

	// 生成Huffman树
	while (huffmanqueue->size != 1) // 当队列只有一个结点时，那就是根结点
	{
		// 两个结点合并
		int priority = huffmanqueue->first->priority;
		priority += huffmanqueue->first->next->priority;
		htNode *left = getPQueue(&huffmanqueue); // 前两个链表结点出来
		htNode *right = getPQueue(&huffmanqueue);
		htNode *newNode = (htNode *)malloc(sizeof(htNode)); // 将两个结点权值相加，形成新的 Huffman 树结点
		newNode->left = left;								// 左右孩子赋值，左孩子权值小于右孩子
		newNode->right = right;
		addPQueue(&huffmanqueue, newNode, priority); // 新结点加入链表，并排序
	}
	htTree *tree = (htTree *)malloc(sizeof(htTree)); // 创建 Huffman 树根节点
	tree->root = getPQueue(&huffmanqueue);			 // 复制为 Huffman 树的根节点

	return tree; // 返回根结点
}

void encode(hlTable *table, char *stringToEncode)
{
	hlNode *traversal;

	printf("Encoding......\n\nInput string : \n%s\n\nEncoded string : ", stringToEncode);

	for (int i = 0; stringToEncode[i] != '\0'; i++)
	{
		traversal = table->first;
		while (traversal->symbol != stringToEncode[i])
			traversal = traversal->next;
		printf("%s", traversal->code);
	}

	printf("\n");
}

void decode(htTree *tree, char *stringToDecode)
{
	int index = 0;
	htNode *traversal = tree->root;

	printf("\n\nDecoding...\n\nInput string : \n%s\nDecoded string : \n", stringToDecode);

	for (int i = 0; stringToDecode[i] != '\0'; i++)
	{
		if (traversal->left == NULL && traversal->right == NULL)
		{
			printf("%c", traversal->symbol);
			traversal = tree->root;
		}

		if (stringToDecode[i] == '0')
			traversal = traversal->left;

		if (stringToDecode[i] == '1')
			traversal = traversal->right;

		if (stringToDecode[i] != '0' && stringToDecode[i] != '1')
		{
			printf("The input string is not coded correctly!\n");
			return;
		}
		if (traversal->left == NULL && traversal->right == NULL) // 如果已经到了叶结点，则输出叶结点的字符
		{
			printf("%c", traversal->symbol);
			traversal = tree->root; // 重新从根结点开始走
			index = i;
		}
	}
}
