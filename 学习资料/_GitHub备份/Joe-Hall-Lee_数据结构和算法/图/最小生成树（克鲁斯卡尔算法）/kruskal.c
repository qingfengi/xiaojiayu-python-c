#include <stdbool.h>
#include <stdio.h>
#define MaxInt 32767 // 表示极大值，即 ∞
#define MVNum 100	 // 最大顶点数
#define MAGEDGE 4950
#define OK 1

typedef int ArcType;	 // 假设边的权值类型为整型
typedef char VerTexType; // 设顶点的数据类型为字符型
typedef int Status;

typedef struct
{
	VerTexType vexs[MVNum]; // 顶点表
	int arcs[MVNum][MVNum]; // 邻接矩阵
	int vexnum, arcnum;		// 图的当前点数和边数
} MGraph;

int LocateVex(MGraph G, VerTexType u)
{
	// 图 G 中查找顶点 u，存在则返回顶点表中的下标；否则返回 -1
	int i;
	for (i = 0; i < G.vexnum; ++i)
	{
		if (u == G.vexs[i])
			return i;
	}
	return -1;
}

Status CreateUDN(MGraph *G) // 采用邻接矩阵表示法，创建无向网 G
{
	scanf("%d%d", &(G->vexnum), &(G->arcnum)); // 输入总顶点数、总边数

	for (int i = 0; i < G->vexnum; ++i)
		scanf("%c", &(G->vexs[i])); // 依次输入点的信息

	for (int i = 0; i < G->vexnum; ++i) // 初始化邻接矩阵
	{
		for (int j = 0; j < G->vexnum; ++j)
			G->arcs[i][j] = MaxInt; // 边的权值均置为极大值
	}

	for (int k = 0; k < G->arcnum; ++k) // 构造邻接矩阵
	{
		int v1, v2;
		ArcType w;
		scanf("%d%d%d", &v1, &v2, &w); // 输入一条边所依附的顶点及边的权值
		int i = LocateVex(*G, v1);
		int j = LocateVex(*G, v2);	   // 确定 v1 和 v2 在 G 中的位置
		G->arcs[i][j] = w;			   // 边 <v1, v2> 的权值置为 w
		G->arcs[j][i] = G->arcs[i][j]; // 置 <v1, v2> 的对称边 <v2, v1> 的权值为 w
	}								   // for
	return OK;
} // CreateUDN

// Kruskal 算法生成最小生成树
int Find(int *parent, int f)
{
	while (parent[f] > 0)
		f = parent[f];
	return f;
}

typedef struct
{
	int begin;	// 边的起始顶点
	int end;	// 边的终止顶点
	int weight; // 边的权值
} Edge;

void MiniSpanTree_Kurskal(MGraph G)
{
	int i, n, m;
	Edge edges[MAGEDGE]; // 定义边集数组
	int parent[MVNum];	 // 定义 parent 数组用来判断边与边是否形成环路

	for (i = 0; i < G.vexnum; i++)
		parent[i] = 0;

	for (i = 0; i < G.arcnum; i++)
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);

		if (n != m) // 如果 n == m，则形成环路，不满足！
		{
			parent[n] = m; // 将此边的结尾顶点放入下标为起点的 parent 数组中，表示此顶点已经在生成树集合中
			printf("(%d, %d) %d", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}
