// ����-��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>  

#define N 3         //��Ʒ������  
#define C 16        //����������  

int w[N] = { 10, 8, 5 };  //ÿ����Ʒ������  
int v[N] = { 5, 4, 1 };   //ÿ����Ʒ�ļ�ֵ  
int x[N] = { 0, 0, 0 };   //x[i]=1������Ʒi���뱳����0��������  

int CurWeight = 0;  //��ǰ���뱳������Ʒ������  
int CurValue = 0;   //��ǰ���뱳������Ʒ�ܼ�ֵ  

int BestValue = 0;  //����ֵ����ǰ������ֵ����ʼ��Ϊ0  
int BestX[N];       //���Ž⣻BestX[i]=1������Ʒi���뱳����0��������  

//t = 0 to N-1  
void backtrack(int t)
{
	//Ҷ�ӽڵ㣬������  
	if (t>N - 1)
	{
		//����ҵ���һ�����ŵĽ�  
		if (CurValue>BestValue)
		{
			//������ŵ�ֵ�ͽ�  
			BestValue = CurValue;
			for (int i = 0; i<N; ++i) BestX[i] = x[i];
		}
	}
	else
	{
		//������ǰ�ڵ���ӽڵ㣺0 �����뱳����1���뱳��  
		for (int i = 0; i <= 1; ++i)
		{
			x[t] = i;

			if (i == 0) //�����뱳��  
			{
				backtrack(t + 1);
			}
			else //���뱳��  
			{

				if ((CurWeight + w[t]) <= C)
				{
					CurWeight += w[t];
					CurValue += v[t];
					backtrack(t + 1);
					CurWeight -= w[t];
					CurValue -= v[t];
				}
			}
		}
		//PS:��������Ϊ�˸����ϵݹ���ݵķ�ʽ�����������  
	}
}

int main(int argc, char* argv[])
{
	backtrack(0);

	printf("����ֵ��%d\n", BestValue);

	for (int i = 0; i<N; i++)
	{
		printf("���Ž⣺%-3d", BestX[i]);
	}
	return 0;
}