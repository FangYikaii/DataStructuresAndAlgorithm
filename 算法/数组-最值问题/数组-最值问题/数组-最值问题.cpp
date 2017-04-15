// 数组-最值问题.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include<iostream>
#include<ctime>
using namespace std;

//寻找第二大的值--方法1
//int *a --  数组的指针a -- int *a=num;  //num[]={};
int Find2ndMaxValue(int *a, int size)
{

	int i, max, s_max;
	//初始化最大值a[0]
	max = a[0];
	//初始化次大值a[1]
	s_max = a[1];
	//遍历数组
	for (i = 0; i < size; i++)
	{
		//如果值>最大值
		if (a[i]>max)
		{
			s_max = max;   //更新最大值和次大值
			max = a[i];
		}
		//如果值<最大值，但是值>次大值
		else if (a[i] < max&&a[i]>s_max)
		{
			s_max = a[i];
		}
	}
	return s_max;	
}

//寻找第二大的值——方法2
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
	//最大值和次大值相等（数组的第一个元素为最大值的时候）
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
	int i = -1;      //i表示最后一个小于p[n-1]元素的位置
	int j = 0;       //j用于扫描数组
	for (j = 0; j < n; j++)
	{
		//将小于p[n-1]的数交换到前半部分
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
	mid = random_partion(p, n);   //对原数组进行一次划分  
	if (mid == n - k)      //如果mid==n-k，那么返回该值，这就是第k大的数  
		return p[mid];
	else if (mid<n - k)
		return getMaxK(p + mid + 1, n - mid - 1, k);  //如果mid<n-k，那么第k大的数在右半数组，而且仍然是第k大数  
	else
		return getMaxK(p, mid, k - (n - mid));   //如果mid>n-k，那么第k大的数在左半数组，且在左半数组中是第k-(n-mid)大的数  
}


int _tmain(int argc, _TCHAR* argv[])
{
	clock_t start, finish;
	start = clock();

	int second, a[] = { 111, 2, 23, 5, 652, 42, 34 };
	second = Find2ndMaxValue(a, sizeof(a) / sizeof(a[0]));
	printf("这个数组中的次大值：%d\n", second);

	second = Find2ndMaxValue_x(a, sizeof(a) / sizeof(a[0]));
	printf("这个数组中的次大值：%d\n", second);


	int num, numa[] = { 12012, 3, 945, 965, 66, 232, 65, 7, 8, 898, 56, 878, 170, 13, 5 };
	num = getMaxK(a, 15, 4);
	printf("%d\n", num);


	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << " (s) " << endl;
	system("pause");
	return 0;
}

