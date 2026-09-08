#define MAXVEX 9
#define INFINITY 65535
#include <stdbool.h>
#include <stdio.h>
#define MAGEDGE 4950
#define OK 1

typedef int ArcType;	 // 假设边的权值类型为整型
typedef char VerTexType; // 设顶点的数据类型为字符型
typedef int Status;

typedef struct
{
	VerTexType vexs[MAXVEX];  // 顶点表
	int arcs[MAXVEX][MAXVEX]; // 邻接矩阵
	int vexnum, arcnum;		  // 图的当前点数和边数
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
			G->arcs[i][j] = INFINITY; // 边的权值均置为极大值
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

typedef int Patharc[MAXVEX];		// 用于存储最短路径下标的数组
typedef int ShortPathTable[MAXVEX]; // 用于存储到各点路径的权值和

void ShortestPath_Dijkstar(MGraph G, int V0, Patharc *P, ShortPathTable *D)
{
	int V, w, k, min;
	int final[MAXVEX]; // final[w] = 1 表示已经求得顶点 V0 到 Vw 的最短路径

	// 初始化数据
	for (V = 0; V < G.vexnum; V++)
	{
		final[V] = 0;			 // 全部顶点初始化为未找到最短路径
		(*D)[V] = G.arcs[V0][V]; // 将与 V0 有连线的顶点加上权值
		(*P)[V] = 0;			 // 初始化路径数组 P 为 0
	}

	(*D)[V0] = 0;  // V0 至 V0 的路径为 0
	final[V0] = 1; // V0 至 V0 不需要求路径

	// 开始主循环，每次求得 V0 到某个 V 顶点的最短路径
	for (V = 1; V < G.vexnum; V++)
	{
		min = INFINITY;
		for (w = 0; w < G.vexnum; w++)
		{
			if (!final[w] && (*D)[w] < min)
			{
				k = w;
				min = (*D)[w];
			}
			final[k] = 1; // 将目前找到的最近的顶点置 1
		}

		// 修正当前最短路径及距离
		for (w = 0; w < G.vexnum; w++)
		{
			// 如果经过V顶点的路径比现在这条路径长度短的话，更新！
			if (!final[w] && (min + G.arcs[k][w] < (*D)[w])) // 修改当前路径长度
			{
				(*D)[w] = min + G.arcs[k][w]; // 修改当前路径长度
				(*P)[w] = k;				  // 存放前驱顶点
			}
		}
	}
}
