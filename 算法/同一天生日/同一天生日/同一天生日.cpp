// ͬһ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//��ͬ���յĸ��ʣ�
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
	printf("%f%%", (1 - p) * 100);    //ͬһ�����յĸ���
	return 0;
}

