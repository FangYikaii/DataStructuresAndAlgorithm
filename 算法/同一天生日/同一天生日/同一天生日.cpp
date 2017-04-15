// 同一天生日.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//不同生日的概率：
//P1 * P2 * P3 * ...... * Pn = (365 - 0)  /  365  *  (365 - 1)   /  365  *  (365 - 2)  /  365  *  ......  *  (365 - n + 1)  /  365 ;

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	float p = 1;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		p = p*(365 - i) / 365;
	}
	printf("%f%%", (1 - p) * 100);    //同一天生日的概率
	return 0;
}

