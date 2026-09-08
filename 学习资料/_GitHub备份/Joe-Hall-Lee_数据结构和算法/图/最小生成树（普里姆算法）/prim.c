#include <stdbool.h>
#include <stdio.h>
#define MaxInt 32767 // 表示极大值，即 ∞
#define MVNum 100	 // 最大顶点数
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
		scanf("%c", &(G->vexs[i]));		// 依次输入点的信息
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
		int j = LocateVex(*G, v2);	   // 确定 v1 和 v2 在G中的位置
		G->arcs[i][j] = w;			   // 边 <v1, v2> 的权值置为 w
		G->arcs[j][i] = G->arcs[i][j]; // 置 <v1, v2> 的对称边 <v2, v1> 的权值为 w
	}								   // for
	return OK;
} // CreateUDN

// Prim 算法生成最小生成树
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MVNum];	// 保存相关顶点下标
	int lowcost[MVNum]; // 保存相关顶点间边的权值

	lowcost[0] = 0; // v0 作为最小生成树的根开始遍历，权值为 0
	adjvex[0] = 0;	// v0 第一个加入

	// 初始化操作
	for (i = 1; i < G.vexnum; i++)
	{
		lowcost[i] = G.arcs[0][i]; // 将邻接矩阵第 0 行所有权值先加入数组
		adjvex[i] = 0;			   // 初始化全部先为 v0 的下标
	}

	// 真正构造最小生成树的过程
	for (i = 1; i < G.vexnum; i++)
	{
		min = MaxInt; // 初始化最小权值为不可能数值
		j = 1;
		k = 0;

		// 遍历全部顶点
		while (j < G.vexnum)
		{
			// 找出 lowcost 数组已存储的最小权值
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j; // 将发现的最小权值的下标存入 k，以待使用。
			}
			j++;
		}

		// 打印当前顶点边中权值最小的边
		printf("(%d, %d)", adjvex[k], k);
		lowcost[k] = 0; // 将当前顶点的权值设置为 0，表示此顶点已经完成任务，进行下一个顶点的遍历

		// 邻接矩阵k行逐个遍历全部顶点
		for (j = 1; j < G.vexnum; j++)
		{
			if (lowcost[j] != 0 && G.arcs[k][j] < lowcost[j])
			{
				lowcost[j] = G.arcs[k][j];
				adjvex[j] = k;
			}
		}
	}
}
