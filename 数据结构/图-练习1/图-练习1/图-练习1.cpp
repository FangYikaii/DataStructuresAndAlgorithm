// 图-练习1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>

#define MaxNum 20            //图的最大顶点数
#define MaxVaule 65535       //权：最大值（可设为一个最大的整数）

typedef struct
{
	char Vertex[MaxNum];      //保存顶点信息（序号或字母）
	int GType;                //图的类型（0：无向图，1：有向图）
	int VertexNum;            //顶点的数量
	int EdgeNum;              //边的数量
	int EdgeWeight[MaxNum][MaxNum];   //保存边的权
	int isTrav[MaxNum];      //遍历标志
}GraphMatrix;                //定义邻接矩阵的图结构

void CreateGraph(GraphMatrix *GM)    //创建邻接矩阵图
{
	int i, j, k;                     //遍历索引
	int weight;                      //权
	char EstartV, EendV;             //边的起始顶点

	printf("输入图中各个顶点的信息\n"); 
	for (i = 0; i < GM->VertexNum; i++)  //输入顶点
	{
		getchar();
		printf("第%d个顶点：", i + 1);
		scanf("%c", &(GM->Vertex[i]));
	}
	printf("输入构成各边的顶点及权值:\n");
	for (k = 0; k < GM->EdgeNum; k++)  
	{
		getchar();
		printf("第%d条边：",k + 1);
		scanf("%c %c %d", &EstartV, &EendV, &weight);  //输入开始顶点、结束顶点、权
		for (i = 0; EstartV != GM->Vertex[i]; i++);  //在已有顶点中查找开始顶点
		for (j = 0; EendV != GM->Vertex[j]; j++);    //在已有顶点中查找结束顶点
		GM->EdgeWeight[i][j] = weight;               //对应位置保存权值，表示有一条边
		if (GM->GType == 0)                          //若是无向图
		{
			GM->EdgeWeight[j][i] = weight;          //在对角位置保存权值
		}
	}
}

void ClearGraph(GraphMatrix *GM)            //清空矩阵
{
	int i, j;

	for (i = 0; i < GM->VertexNum; i++)       //双层遍历
	{
		for (j = 0; j < GM->VertexNum; j++)
		{
			GM->EdgeWeight[i][j] = MaxVaule;     //设置矩阵中各元素的值为MaxValue
		}
	}
}

void OutGraph(GraphMatrix *GM)         //显示图：也就是显示图的邻接矩阵，方便了解图的顶点和边等结构信息
{
	int i, j;
	for (j = 0; j < GM->VertexNum; j++)
	{
		printf("\t%c", GM->Vertex[j]);  //在第1行输出顶点信息
	}
	printf("\n");
	for (i = 0; i < GM->VertexNum; i++)
	{
		printf("%c", j < GM->Vertex[i]);
		for (j = 0; j < GM->VertexNum; j++)
		{
			if (GM->EdgeWeight[i][j] == MaxVaule)
			{
				printf("\tZ");                    //以Z表示无穷大
			}
			else
			{
				printf("\t%d", GM->EdgeWeight[i][j]);  //输出边的权值
			}
		}
		printf("\n");
	}
}

/*
深度优先:
1．首先从数组isTraV中选择一个未被访问的顶点Vi，将其标记为1，表示已经访问；
2.  接着，从Vi的一个未被访问过的邻接点出发进行深度优先的遍历；
3.  重复步骤2，直到图中所有和Vi有路径相通的顶点都被访问过；
4.  重复1-3的操作，直到图中所有的顶点都被访问过。
*/
void DeepTraOne(GraphMatrix *GM, int n)   //从第n个节点开始，深度遍历图
{
	int i;
	GM->isTrav[n] = 1;                 //标记该顶点已经被处理过
	printf("->%c", GM->Vertex[n]);     //输出节点数据

	//添加处理节点的操作
	for (i = 0; i < GM->VertexNum; i++)
	{
		if (GM->EdgeWeight[n][i] != MaxVaule&&!GM->isTrav[i])  //GM->EdgeWeight[n][i]的权值小于最大值，且，i点没有被遍历过
		{
			DeepTraOne(GM, i);
		}
	}
}

void DeepTracGraph(GraphMatrix *GM)  //深度遍历
{
	int i;
	for (i = 0; i < GM->VertexNum; i++)     //清除各遍历点的标志
	{
		GM->isTrav[i] = 0;
	}
	printf("深度优先遍历节点：");
	for (i = 0; i < GM->VertexNum; i++)
	{
		if (!GM->isTrav[i])              //该点未遍历
		{
			DeepTraOne(GM, i);           //调用函数遍历
		}
	}
	printf("\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	GraphMatrix GM;                      //定义保存邻接表结构的图
	 
	printf("输入生成图的类型：");       //输入图的类型
	scanf("%d", &GM.GType);
	printf("输入图的顶点数量：");       //输入图的顶点数
	scanf("%d", &GM.VertexNum);
	printf("输入图的边的数量：");       //输入图的边
	scanf("%d", &GM.EdgeNum);

	ClearGraph(&GM);                  //清空图
	CreateGraph(&GM);                 //生成邻接表结构的图
	printf("该图的邻接矩阵数据如下：\n");
	OutGraph(&GM);                    //输出邻接矩阵
	DeepTracGraph(&GM);	               //深度优先搜索遍历图
	
	
	scanf("%d", &GM.GType);
	return 0;
}

