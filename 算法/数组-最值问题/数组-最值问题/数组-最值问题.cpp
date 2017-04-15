// ����-��ֵ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include<iostream>
#include<ctime>
using namespace std;

//Ѱ�ҵڶ����ֵ--����1
//int *a --  �����ָ��a -- int *a=num;  //num[]={};
int Find2ndMaxValue(int *a, int size)
{

	int i, max, s_max;
	//��ʼ�����ֵa[0]
	max = a[0];
	//��ʼ���δ�ֵa[1]
	s_max = a[1];
	//��������
	for (i = 0; i < size; i++)
	{
		//���ֵ>���ֵ
		if (a[i]>max)
		{
			s_max = max;   //�������ֵ�ʹδ�ֵ
			max = a[i];
		}
		//���ֵ<���ֵ������ֵ>�δ�ֵ
		else if (a[i] < max&&a[i]>s_max)
		{
			s_max = a[i];
		}
	}
	return s_max;	
}

//Ѱ�ҵڶ����ֵ��������2
int Find2ndMaxValue_x(int *a, int size)
{
	int i, first, second;
	first = second = a[0];
	
	for (i = 1; i < size; i++)
	{
		if (a[i]>first)
		{
			second = first;
			first = a[i];
		}
		else if (a[i]<first&&a[i]>second)
		{
			second = a[i];
		}
	}
	//���ֵ�ʹδ�ֵ��ȣ�����ĵ�һ��Ԫ��Ϊ���ֵ��ʱ��
	if (first == second)
	{
		for (i = 1; i < size; i++)
		{
			if (a[i]>second)
			{
				second = a[i];
			}
		}
	}
	return second;
}


int random_partion(int *p, int n)
{
	int idx = rand() % n;
	swap(p[idx], p[n - 1]);
	int i = -1;      //i��ʾ���һ��С��p[n-1]Ԫ�ص�λ��
	int j = 0;       //j����ɨ������
	for (j = 0; j < n; j++)
	{
		//��С��p[n-1]����������ǰ�벿��
		if (p[j] < p[n - 1])
		{
			swap(p[++i], p[j]);
		}
	}
	swap(p[++i], p[n - 1]);
	return i;
}


int getMaxK(int *p, int n, int k)
{
	int mid;
	if (k <= 0)
		return -1;
	if (n<k)
		return -1;
	mid = random_partion(p, n);   //��ԭ�������һ�λ���  
	if (mid == n - k)      //���mid==n-k����ô���ظ�ֵ������ǵ�k�����  
		return p[mid];
	else if (mid<n - k)
		return getMaxK(p + mid + 1, n - mid - 1, k);  //���mid<n-k����ô��k��������Ұ����飬������Ȼ�ǵ�k����  
	else
		return getMaxK(p, mid, k - (n - mid));   //���mid>n-k����ô��k�������������飬��������������ǵ�k-(n-mid)�����  
}


int _tmain(int argc, _TCHAR* argv[])
{
	clock_t start, finish;
	start = clock();

	int second, a[] = { 111, 2, 23, 5, 652, 42, 34 };
	second = Find2ndMaxValue(a, sizeof(a) / sizeof(a[0]));
	printf("��������еĴδ�ֵ��%d\n", second);

	second = Find2ndMaxValue_x(a, sizeof(a) / sizeof(a[0]));
	printf("��������еĴδ�ֵ��%d\n", second);


	int num, numa[] = { 12012, 3, 945, 965, 66, 232, 65, 7, 8, 898, 56, 878, 170, 13, 5 };
	num = getMaxK(a, 15, 4);
	printf("%d\n", num);


	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << " (s) " << endl;
	system("pause");
	return 0;
}

