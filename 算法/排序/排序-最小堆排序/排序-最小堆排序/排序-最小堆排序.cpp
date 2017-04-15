// ����-��С������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
int n;
int heap[10];
#define K 10

void create_heap();
void UpToDown(int);


int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	int tmp;
	while (scanf("%d", &n) != EOF)
	{
		for (i = 1; i < K; i++)
		{
			scanf("%d", &heap[i]);
		}
		create_heap();
		for (i = K+1; i <=n; i++)
		{
			scanf("%d", &tmp);
			if (tmp>heap[1])
			{
				heap[1] = tmp;     
				UpToDown(1);       //���µ�����
			}
		}
		return 1;
	}
	return 1;
}

void create_heap()
{
	int i;
	int pos = K / 2;
	for (i = pos; i >= 1; i--)
	{
		UpToDown(i);
	}
}

void UpToDown(int i)
{
	int t1, t2, tmp, pos;
	t1 = 2 * i; ///����(���ڵĻ�)
	t2 = t1 + 1;    ///�Һ���(���ڵĻ�)
	if (t1>K)    ///�޺��ӽڵ�
		return;
	else
	{
		if (t2>K)  ///ֻ������
			pos = t1;
		else
			pos = heap[t1]>heap[t2] ? t2 : t1;

		if (heap[i]>heap[pos]) ///pos�������Ӻ����У���ֵ��С�ߵ�λ��
		{
			tmp = heap[i]; heap[i] = heap[pos]; heap[pos] = tmp;
			UpToDown(pos);
		}
	}
}