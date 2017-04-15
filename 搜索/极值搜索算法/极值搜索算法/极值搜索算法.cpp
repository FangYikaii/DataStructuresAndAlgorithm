// 极值搜索算法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>

/*
三分搜索
*/
int find_max_num(int*arr, int begin, int end)
{
	int mid, midmid, max;

	/*mid靠近极值点，舍弃最右部分，midmid靠近极值点，舍弃最左部分*/
	while (begin < end)
	{
		//如果只剩下begin和end： begin end
		if (begin + 1 == end)   
		{
			//返回大的
			max = arr[begin] > arr[end] ? arr[begin] : arr[end];
			return max;
		}
		mid = (begin + end) / 2;          //mid中间值
		//如果mid后就是end：begin mid end
		if (mid+1==end)                  
		{
			midmid = (mid + end) / 2 + 1;        //midmid=end
		}
		else
		{
			midmid = (mid + end) / 2;
		}
		//如果mid后就是end：begin mid end
		if (midmid == end)          
		{
			max = arr[begin] > arr[mid] ? arr[begin] : arr[mid];  //比较begin，mid，end
			max = max > arr[end] ? max : arr[end];
			return max;
		}
		//否则：比较mid和midmid的大小，如果mid离最大值比较近，舍弃midmid后面部分
		//如果midmid离最大值比较近，舍弃mid前面部分
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
			printf("最大值为%d\n", max);
		}
		free(arr);
	}
	scanf("%d", &n);
	return 0;
}

