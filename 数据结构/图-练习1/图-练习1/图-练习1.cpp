// ͼ-��ϰ1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>

#define MaxNum 20            //ͼ����󶥵���
#define MaxVaule 65535       //Ȩ�����ֵ������Ϊһ������������

typedef struct
{
	char Vertex[MaxNum];      //���涥����Ϣ����Ż���ĸ��
	int GType;                //ͼ�����ͣ�0������ͼ��1������ͼ��
	int VertexNum;            //���������
	int EdgeNum;              //�ߵ�����
	int EdgeWeight[MaxNum][MaxNum];   //����ߵ�Ȩ
	int isTrav[MaxNum];      //������־
}GraphMatrix;                //�����ڽӾ����ͼ�ṹ

void CreateGraph(GraphMatrix *GM)    //�����ڽӾ���ͼ
{
	int i, j, k;                     //��������
	int weight;                      //Ȩ
	char EstartV, EendV;             //�ߵ���ʼ����

	printf("����ͼ�и����������Ϣ\n"); 
	for (i = 0; i < GM->VertexNum; i++)  //���붥��
	{
		getchar();
		printf("��%d�����㣺", i + 1);
		scanf("%c", &(GM->Vertex[i]));
	}
	printf("���빹�ɸ��ߵĶ��㼰Ȩֵ:\n");
	for (k = 0; k < GM->EdgeNum; k++)  
	{
		getchar();
		printf("��%d���ߣ�",k + 1);
		scanf("%c %c %d", &EstartV, &EendV, &weight);  //���뿪ʼ���㡢�������㡢Ȩ
		for (i = 0; EstartV != GM->Vertex[i]; i++);  //�����ж����в��ҿ�ʼ����
		for (j = 0; EendV != GM->Vertex[j]; j++);    //�����ж����в��ҽ�������
		GM->EdgeWeight[i][j] = weight;               //��Ӧλ�ñ���Ȩֵ����ʾ��һ����
		if (GM->GType == 0)                          //��������ͼ
		{
			GM->EdgeWeight[j][i] = weight;          //�ڶԽ�λ�ñ���Ȩֵ
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
			GM->EdgeWeight[i][j] = MaxVaule;     //���þ����и�Ԫ�ص�ֵΪMaxValue
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
			if (GM->EdgeWeight[i][j] == MaxVaule)
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

/*
�������:
1�����ȴ�����isTraV��ѡ��һ��δ�����ʵĶ���Vi��������Ϊ1����ʾ�Ѿ����ʣ�
2.  ���ţ���Vi��һ��δ�����ʹ����ڽӵ��������������ȵı�����
3.  �ظ�����2��ֱ��ͼ�����к�Vi��·����ͨ�Ķ��㶼�����ʹ���
4.  �ظ�1-3�Ĳ�����ֱ��ͼ�����еĶ��㶼�����ʹ���
*/
void DeepTraOne(GraphMatrix *GM, int n)   //�ӵ�n���ڵ㿪ʼ����ȱ���ͼ
{
	int i;
	GM->isTrav[n] = 1;                 //��Ǹö����Ѿ��������
	printf("->%c", GM->Vertex[n]);     //����ڵ�����

	//��Ӵ���ڵ�Ĳ���
	for (i = 0; i < GM->VertexNum; i++)
	{
		if (GM->EdgeWeight[n][i] != MaxVaule&&!GM->isTrav[i])  //GM->EdgeWeight[n][i]��ȨֵС�����ֵ���ң�i��û�б�������
		{
			DeepTraOne(GM, i);
		}
	}
}

void DeepTracGraph(GraphMatrix *GM)  //��ȱ���
{
	int i;
	for (i = 0; i < GM->VertexNum; i++)     //�����������ı�־
	{
		GM->isTrav[i] = 0;
	}
	printf("������ȱ����ڵ㣺");
	for (i = 0; i < GM->VertexNum; i++)
	{
		if (!GM->isTrav[i])              //�õ�δ����
		{
			DeepTraOne(GM, i);           //���ú�������
		}
	}
	printf("\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	GraphMatrix GM;                      //���屣���ڽӱ�ṹ��ͼ
	 
	printf("��������ͼ�����ͣ�");       //����ͼ������
	scanf("%d", &GM.GType);
	printf("����ͼ�Ķ���������");       //����ͼ�Ķ�����
	scanf("%d", &GM.VertexNum);
	printf("����ͼ�ıߵ�������");       //����ͼ�ı�
	scanf("%d", &GM.EdgeNum);

	ClearGraph(&GM);                  //���ͼ
	CreateGraph(&GM);                 //�����ڽӱ�ṹ��ͼ
	printf("��ͼ���ڽӾ����������£�\n");
	OutGraph(&GM);                    //����ڽӾ���
	DeepTracGraph(&GM);	               //���������������ͼ
	
	
	scanf("%d", &GM.GType);
	return 0;
}

