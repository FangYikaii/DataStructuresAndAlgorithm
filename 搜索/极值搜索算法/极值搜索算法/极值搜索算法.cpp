// ��ֵ�����㷨.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>

/*
��������
*/
int find_max_num(int*arr, int begin, int end)
{
	int mid, midmid, max;

	/*mid������ֵ�㣬�������Ҳ��֣�midmid������ֵ�㣬�������󲿷�*/
	while (begin < end)
	{
		//���ֻʣ��begin��end�� begin end
		if (begin + 1 == end)   
		{
			//���ش��
			max = arr[begin] > arr[end] ? arr[begin] : arr[end];
			return max;
		}
		mid = (begin + end) / 2;          //mid�м�ֵ
		//���mid�����end��begin mid end
		if (mid+1==end)                  
		{
			midmid = (mid + end) / 2 + 1;        //midmid=end
		}
		else
		{
			midmid = (mid + end) / 2;
		}
		//���mid�����end��begin mid end
		if (midmid == end)          
		{
			max = arr[begin] > arr[mid] ? arr[begin] : arr[mid];  //�Ƚ�begin��mid��end
			max = max > arr[end] ? max : arr[end];
			return max;
		}
		//���򣺱Ƚ�mid��midmid�Ĵ�С�����mid�����ֵ�ȽϽ�������midmid���沿��
		//���midmid�����ֵ�ȽϽ�������midǰ�沿��
		if (arr[mid] >= arr[midmid])
		{
			end = midmid;
		}
		else
		{
			begin = mid;
		}
	}
	return arr[mid];
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i, n, max, *arr;
	while (scanf("%d", &n) != EOF)
	{
		arr = (int*)malloc(sizeof(int)*n);
		for (i = 0; i < n; i++)
		{
			scanf("%d", arr + i);
		}
		if (n == 1)
		{
			printf("%d\n", arr[0]);
		}
		else
		{
			max = find_max_num(arr, 0, n - 1);
			printf("���ֵΪ%d\n", max);
		}
		free(arr);
	}
	scanf("%d", &n);
	return 0;
}

