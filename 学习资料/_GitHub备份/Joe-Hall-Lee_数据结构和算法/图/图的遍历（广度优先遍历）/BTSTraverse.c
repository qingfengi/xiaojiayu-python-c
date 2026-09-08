#include <stdbool.h>
#include <stdio.h>
#define MaxInt 32767 // 表示极大值，即 ∞
#define MVNum 100	 // 最大定点数
#define OK 1
#define ERROR 0
#define MAXQSIZE 100 // 最大队列长度
#define OVERFLOW -2

typedef char VerTexType; // 设顶点的数据类型为字符型
typedef int Status;

typedef struct
{
	int *base; // 动态分配存储空间
	int front; // 头指针，若队列不空，指向队列头元素
	int rear;  // 尾指针，若队列不空，指向队列尾元素的下一个位置
} Queue;

Status InitQueue(Queue *Q)
{
	Q->base = (VerTexType *)malloc(MAXQSIZE * sizeof(VerTexType)); // 分配数组空间

	if (!Q->base)
		exit(OVERFLOW); // 存储分配失败

	Q->front = Q->rear = 0; // 头指针、尾指针置为 0，队列为空
	return OK;
}

int QueueLength(Queue Q)
{
	return ((Q.rear - Q.front + MAXQSIZE) % MAXQSIZE);
}
Status EnQueue(Queue *Q, int i)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return ERROR;
	Q->base[Q->rear] = i;				// 新元素加入队尾
	Q->rear = (Q->rear + 1) % MAXQSIZE; // 队尾指针 + 1
	return OK;
}

Status DeQueue(Queue *Q, int *i)
{
	if (Q->front == Q->rear)
		return ERROR;					  // 队空
	*i = Q->base[Q->front];				  // 保存队头元素
	Q->front = (Q->front + 1) % MAXQSIZE; // 队头指针 + 1
	return OK;
}

typedef struct
{
	VerTexType vexs[MVNum]; // 顶点表
	int arcs[MVNum][MVNum]; // 邻接矩阵
	int vexnum, arcnum;		// 图的当前点数和边数
} MGraph;

VerTexType GetHead(Queue Q)
{
	if (Q.front != Q.rear)		// 队列不为空
		return Q.base[Q.front]; // 返回队头指针元素的值，队头指针不变
}

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
		VerTexType v1, v2;
		int w;
		scanf("%c%c%d", &v1, &v2, &w);
		int i = LocateVex(*G, v1);
		int j = LocateVex(*G, v2); // 确定 v1 和 v2 在 G 中的位置
		G->arcs[i][j] = w;
		G->arcs[j][i] = G->arcs[i][j];
	}
	return OK;
}

// 邻接矩阵的广度优先算法

void BFSTraverse(MGraph G)
{
	int i, j;
	Queue Q;
	bool *visited = (bool *)malloc(sizeof(bool) * G.vexnum);
	for (i = 0; i < G.vexnum; i++)
		visited[i] = false;

	InitQueue(&Q);

	for (i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			printf("%c", G.vexs[i]);
			visited[i] = true;
			EnQueue(&Q, i);

			while (!(Q.front == Q.rear))
			{
				DeQueue(&Q, &i);
				for (j = 0; j < G.vexnum; j++)
				{
					if (G.arcs[i][j] == 1 && !visited[j])
					{
						printf("%c", G.vexs[j]);
						visited[i] = true;
						EnQueue(&Q, i);
					}
				}
			}
		}
	}
}
