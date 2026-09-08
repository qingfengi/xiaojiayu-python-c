#include <stdlib.h>
#include <stdio.h>
#define MAXVEX 9
#define OK 1
#define ERROR 0

typedef int Status;

// 边表结点声明
typedef struct EdgeNode
{
	int adjvex;
	struct EdgeNode *next;
} EdgeNode;

// 顶点表结点声明
typedef struct VertexNode
{
	int in; // 顶点入度
	int data;
	EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;

// 拓补算法排序
// 若 GL 无回路，则输出拓补排序序列并返回 OK，否则返回 ERROR
Status TopoloicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;   // 用于栈指针下标索引
	int count = 0; // 用于统计输出顶点的个数
	int *stack;	   // 用于存储入度为 0 的顶点

	stack = (int *)malloc(GL->numVertexes * sizeof(int));

	for (i = 0; i < GL->numVertexes; i++)
	{
		if (0 == GL->adjList[i].in)
			stack[top++] = i; // 将度为 0 的顶点下标入栈
	}

	while (0 != top)
	{
		gettop = stack[--top]; // 出栈
		printf("%d -> ", GL->adjList[gettop].data);
		count++;

		for (e = GL->adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			// 注意：下边这个 if 条件是分析整个程序的要点！
			// 将 k 号顶点邻接点的入度 -1，因为它的前驱已经消除
			// 接着判断 -1 后入度是否为 0，如果为 0 则也入栈
			if (!(--GL->adjList[k].in))
				stack[top++] = k;
		}
	}

	if (count < GL->numVertexes) // 如果 count 小于顶点数，说明存在环
		return ERROR;
	else
		return OK;
}
