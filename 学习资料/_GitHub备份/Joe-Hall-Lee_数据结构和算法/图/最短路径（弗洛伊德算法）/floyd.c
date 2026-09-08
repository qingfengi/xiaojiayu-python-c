#include <stdbool.h>
#include <stdio.h>
#define MaxInt 65535 // 表示极大值，即 ∞
#define MVNum 9		 // 最大顶点数
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

typedef int Pathmatrix[MVNum][MVNum];
typedef int ShortPathTable[MVNum][MVNum];

void ShortestPath_Floyd(MGraph G, Pathmatrix *P, ShortPathTable *D)
{
	int v, w, k;

	// 初始化 D 和 P
	for (v = 0; v < G.vexnum; v++)
	{
		for (w = 0; w < G.vexnum; w++)
		{
			(*D)[v][w] = G.arcs[v][w];
			(*P)[v][w] = w;
		}
	}

	// 优美的弗洛伊德算法
	for (k = 0; k < G.vexnum; k++)
	{
		for (v = 0; v < G.vexnum; v++)
		{
			for (w = 0; w < G.vexnum; w++)
			{
				if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w])
				{
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					(*P)[v][w] = (*P)[v][k];
				}
			}
		}
	}
}
