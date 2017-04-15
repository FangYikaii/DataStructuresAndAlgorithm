// ��С������ģ��.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdio.h>

#define MaxNum 20       //ͼ����󶥵���
#define MaxValue 6535    //���ֵ������Ϊһ�����������

#define USED 0
#define NoL -1

typedef struct
{
	char Vertex[MaxNum];    //������Ϣ
	int GType;              //ͼ������ 
	int VertexNum;          //���������
	int EdgeNum;            //�ߵ�����
	int EdgeWeight[MaxNum][MaxNum];    //�ߵ�Ȩ
	int isTarv[MaxNum];           //������־
}GraphMatrix;

void CreatGraph(GraphMatrix* GM)
{
	int i, j, k;
	int weight;
	char EstartV, EendV;

	printf("����ͼ�ж������Ϣ��");
	for (i = 0; i < GM->VertexNum; i++)   //���붥��
	{
		getchar();
		printf("��%d�����㣺", i + 1);
		scanf("%c", &(GM->Vertex[i]));
	}
	printf("���빹�ɸ��ߵĶ��㼰Ȩֵ:\n");  
	for (k = 0; k < GM->EdgeNum; k++)  //����ߵ���Ϣ
	{
		getchar();
		printf("��%d���ߣ�", k + 1);
		scanf("%c %c %d", &EstartV, &EendV, &weight);
		for (i = 0; EstartV != GM->Vertex[i]; i++);      //�������ж����в���ʼ��
		for (j = 0; EendV != GM->Vertex[j]; j++);        //�����ж����в��ҽ��յ�
		GM->EdgeWeight[i][j] = weight;                   //��Ӧλ�ñ���Ȩֵ����ʾ��һ����
		if (GM->GType == 0)                              //��������ͼ
		{
			GM->EdgeWeight[j][i] = weight;               //�ڶԽ��߱���Ȩֵ
		}		
	}
}

void ClearGraph(GraphMatrix *GM)            //��վ���
{
	int i, j;

	for (i = 0; i < GM->VertexNum; i++)       //˫�����
	{
		for (j = 0; j < GM->VertexNum; j++)
		{
			GM->EdgeWeight[i][j] = MaxValue;     //���þ����и�Ԫ�ص�ֵΪMaxValue
		}
	}
}

void OutGraph(GraphMatrix *GM)         //��ʾͼ��Ҳ������ʾͼ���ڽӾ��󣬷����˽�ͼ�Ķ���ͱߵȽṹ��Ϣ
{
	int i, j;
	for (j = 0; j < GM->VertexNum; j++)
	{
		printf("\t%c", GM->Vertex[j]);  //�ڵ�1�����������Ϣ
	}
	printf("\n");
	for (i = 0; i < GM->VertexNum; i++)
	{
		printf("%c", j < GM->Vertex[i]);
		for (j = 0; j < GM->VertexNum; j++)
		{
			if (GM->EdgeWeight[i][j] == MaxValue)
			{
				printf("\tZ");                    //��Z��ʾ�����
			}
			else
			{
				printf("\t%d", GM->EdgeWeight[i][j]);  //����ߵ�Ȩֵ
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

