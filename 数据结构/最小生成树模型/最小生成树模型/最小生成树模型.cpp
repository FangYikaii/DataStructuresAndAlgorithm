// 最小生成树模型.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>

#define MaxNum 20       //图的最大顶点数
#define MaxValue 6535    //最大值（可设为一个最大整数）

#define USED 0
#define NoL -1

typedef struct
{
	char Vertex[MaxNum];    //顶点信息
	int GType;              //图的类型 
	int VertexNum;          //顶点的数量
	int EdgeNum;            //边的数量
	int EdgeWeight[MaxNum][MaxNum];    //边的权
	int isTarv[MaxNum];           //遍历标志
}GraphMatrix;

void CreatGraph(GraphMatrix* GM)
{
	int i, j, k;
	int weight;
	char EstartV, EendV;

	printf("输入图中顶点的信息：");
	for (i = 0; i < GM->VertexNum; i++)   //输入顶点
	{
		getchar();
		printf("第%d个顶点：", i + 1);
		scanf("%c", &(GM->Vertex[i]));
	}
	printf("输入构成各边的顶点及权值:\n");  
	for (k = 0; k < GM->EdgeNum; k++)  //输入边的信息
	{
		getchar();
		printf("第%d条边：", k + 1);
		scanf("%c %c %d", &EstartV, &EendV, &weight);
		for (i = 0; EstartV != GM->Vertex[i]; i++);      //若在已有顶点中查找始点
		for (j = 0; EendV != GM->Vertex[j]; j++);        //在已有顶点中查找结终点
		GM->EdgeWeight[i][j] = weight;                   //对应位置保存权值，表示有一条边
		if (GM->GType == 0)                              //若是无向图
		{
			GM->EdgeWeight[j][i] = weight;               //在对角线保存权值
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
			GM->EdgeWeight[i][j] = MaxValue;     //设置矩阵中各元素的值为MaxValue
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
			if (GM->EdgeWeight[i][j] == MaxValue)
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

void PrimGraph(GraphMatrix GM)
{
	int i, j, k, min, sum;
	int weight[MaxNum];

}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

