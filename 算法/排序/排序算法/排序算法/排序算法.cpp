// �����㷨.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>

#define SIZE 8



/*
ð������
40 8 15 18 12 �����н�ϸ���˵�һ�˵ıȽϹ��̣�
��1��: 8 15 18 12 40
��2��: 8 15 12 18 40
��3��: 8 12 15 18 40
��4��: 8 12 15 18 40
���αȽ����ڵ����ݣ���С���ݷ���ǰ�������ݷ��ں�
����һ���ȱȽϵ�1���͵�2�����������ں�С����ǰ��
�ٱȽϵ�2�������3�����������ں�С����ǰ��
�Դ�������������"����"�����һ��λ�ã�
�ڶ����򽫴δ���������������ڶ���λ��......��n-1(nΪ�������ݵĸ���)�˼����������
*/



/********************************************************
*�������ƣ�BubbleSort
*����˵����pDataArray �������飻
*          iDataNumΪ�������ݸ���
*˵����    ð������
*********************************************************/
void BubbleSort(int* pDataArray, int iDataNum)
{
	for (int i = 0; i < iDataNum - 1; i++)        //��iDataNum-1��
	{
		for (int j = 0; j < iDataNum - i - 1; j++)
		{
			if (pDataArray[j]>pDataArray[j + 1])    //���Dataǰ>Data�󣬽���ֵ
			{
				int temp = pDataArray[j];
				pDataArray[j] = pDataArray[j + 1];
				pDataArray[j + 1] = temp;
			}
		}
	}
}

/********************************************************
*�������ƣ�BubbleSort_Optimize
*����˵����pDataArray �������飻
*          iDataNumΪ�������ݸ���
*˵����    ð�������Ż�
*********************************************************/
void BubbleSort_Optimize(int* pDataArray, int iDataNum)
{
	bool flag = false;         //��¼�Ƿ���ڽ���
	for (int i = 0; i < iDataNum - 1; i++)   //��iDataNum-1��
	{
		flag = false;
		for (int j = 0; j < iDataNum - i - 1; j++)
		{
			if (pDataArray[j]>pDataArray[j + 1])        //���Dataǰ>Data�󣬽���ֵ
			{
				flag = true;
				int temp = pDataArray[j];
				pDataArray[j] = pDataArray[j + 1];
				pDataArray[j + 1] = temp;
			}
		}

		/*
		8 40 15 18 12  
		8 15 40 18 12  flag��true
		8 15 18 40 12   
		8 15 18 12 40              ��һ��

		8 15 18 12 40  flag��flase
		8 15 12 18 40  flag��true
		8 15 12 18 40              �ڶ���

		8 15 12 18 40 
		8 12 15 18 40  flag:true   ������

		8 12 15 18 40  flag:false  �����ˣ�break�����ǽ�����
		*/
		if (!flag)    //��һ�˱Ƚ��в����ڽ��������˳�����  
		{
			break;
		}
	}
}


/*
ѡ������
��1������Ϊ����1���͵�2���ȣ���1���͵�3���ȣ�������1���͵�n���ȣ�
��С�����������˵�һλ��
��2������Ϊ����2���͵�3���ȣ���2���͵�4���ȣ�������2���͵�n���ȣ�
�����ڶ�С�����������˵ڶ�λ��
���������������������� ����������������������������n-1���͵�n���ȣ�
�����������������һλ��
*/

/********************************************************
*�������ƣ�BubbleSort_Optimize
*����˵����pDataArray �������飻
*          iDataNumΪ�������ݸ���
*˵����    ð�������Ż�
*********************************************************/
void SelectionSort(int* pDataArray, int iDataNum)
{
	int i, j, k;
	int temp;
	for (i = 0; i < iDataNum - 1; i++)  //���iDataNum-1��
	{
		k = i;    //Ҫ���滻���Ǹ�index
		for (j = i + 1; j < iDataNum; j++)   //k֮������飬���������pDataArray[j]С�����滻
		{
			if (pDataArray[j] < pDataArray[k])  
			{
				k = j;      //kΪ��С���Ǹ�
			}
		}
		if (k != j)     //������ȣ�˵����������,����Ҫ���滻��������Сֵ��λ��
		{
			temp = pDataArray[i];
			pDataArray[i] = pDataArray[k];
			pDataArray[k] = temp;
		}
	}
}

/*
��������ԭ��ܼ򵥣���һ�����ݷֳ����飬�ҷֱ����Ϊ��������������顣
ÿ�δӴ���������ȡ��һ��Ԫ�أ����������Ԫ�ؽ��бȽϣ����ҵ����ʵ�λ�ã�����Ԫ�ز嵽�����鵱�С�
��������ÿ�β���һ��Ԫ�أ����������ӣ�����������١�ֱ����������Ԫ�ظ���Ϊ0��
��Ȼ������������漰����Ԫ�ص��ƶ���
*/

/********************************************************
*�������ƣ�InsertionSort
*����˵����num �������飻
*          lenΪ�������ݸ���
*˵����    ��������
*********************************************************/
void InsertionSort(int* num, int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)   //����n-1��
	{
		temp = num[i];  //�Ӵ���������ȡ����һ��Ԫ�� 
		j = i - 1;      //i-1Ϊ����������һ��Ԫ�ص��±�
		while (j>=0 && temp < num[j])  //�ж�������j>=0�Ա߽�������ƣ�temp<num[j]Ϊ�����ж����������num[i]<num[j],num[j]����ƶ�һλ
		{
			num[j + 1] = num[j];     //�����Ǻ��ʵ�λ�ã�������Ԫ������ƶ�
			j--;          //��ǰ�ж�
		}
		num[j + 1] = temp;   //�ҵ�����λ�ã�����Ԫ��
	}
}


/*
Shell����
*/

/********************************************************
*�������ƣ�ShellSort
*����˵����a �������飻
*          lenΪ�������ݸ���
*˵����    Shell����
*********************************************************/
void ShellSort(int* a, int len)
{
	int i, j, h;
	int r, temp;
	int x = 0;
	for (r = len / 2; r >= 1; r /= 2)     //�������������:rΪ����������ÿ����һ�ε���r����2��r>=1ʱ��������
	{
		for (i = r; i < len; i++)     //ִ��Сѭ����������
		{
			temp = a[i];
			j = i - r;
			while (j >= 0 && temp < a[j])   //���������ʵ��
			{
				a[j+r] = a[j];
				j -= r;
			}
			a[j + r] = temp;
		}
		x++;
		printf("\n��%d����������", x);
		for (h = 0; h < len; h++)
		{
			printf("%d ", a[h]);
		}
		printf("\n");
	}
}

/*
��������
*/
/*
1��i =L; j = R; ����׼���ڳ��γɵ�һ����a[i]��
2��j--�ɺ���ǰ�ұ���С�������ҵ����ڳ�������ǰһ����a[i]�С�
3��i++��ǰ����ұ�����������ҵ���Ҳ�ڳ������ǰһ����a[j]�С�
4�����ظ�ִ��2��3������ֱ��i==j������׼������a[i]�С�
*/
void quick_sort(int*s, int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];   //��һ����xΪ��׼��
		while (i < j)                 //�ڶ�����������
		{
			//���������ҵ�һ��С��x����
			while (i < j&&s[j] >= x)     //���i<j,�Һ���������ڻ�׼��������index--��ֱ��С�ڻ�׼��
			{
				j--;
			}
			if (i < j)
			{
				s[i++] = s[j];        //��С�ڻ�׼����s[j]���һ���ӣ�i++
			}

			while (i < j&&s[i] < x)     //���i<j,��ǰ��������ڻ�׼����ǰ��index++��ֱ��С�ڻ�׼��
			{
				i++;
			}

			if (i < j)
			{
				s[j--] = s[i];          //�Ѵ��ڻ�׼����s[i]�����һ���ӣ�j--
			}
		}

		s[i] = x;             //���Ĳ�������׼������s[i]��	
		
		//����
		/*
		���Σ������ϵĽ����ǡ��ֶ���֮�������ǰ�һ�����ӵ�����ֳ�������������ͬ�����Ƶ������⣬�ٰ�������ֳɸ�С�������⡭��
		ֱ�������������Լ򵥵�ֱ����⣬ԭ����Ľ⼴������Ľ�ĺϲ����ڼ������ѧ�У����η��������÷���˼���һ�ֺ���Ҫ���㷨��
		���η��Ǻܶ��Ч�㷨�Ļ������������㷨���������򣬹鲢���򣩣�����Ҷ�任�����ٸ���Ҷ�任���ȵȡ�
		*/
		quick_sort(s, l, i - 1);   //�ݹ���ã���Ϊ[l,i-1],[i+1,r],��Ϊs[i]ǰ������ݶ�С��s[i],s[i]�������������s[i]
		quick_sort(s, i + 1, r);		
	}
}


int _tmain(int argc, _TCHAR* argv[])
{

	int shuzu[SIZE];
	
	srand(time(NULL));   //�������
	for (int i = 0; i < SIZE; i++)
	{
		shuzu[i] = rand() / 1000 + 100;  //��ʼ������
	}
	printf("����ǰ������Ϊ��\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu[i]);
	}

	int shuzu_bubbleopt[SIZE];     //���鸳ֵ-shuzu_opt
	int shuzu_selection[SIZE];     //���鸳ֵ-shuzu_selection
	int shuzu_insertion[SIZE];     //���鸳ֵ-shuzu_insertion
	int shuzu_quick[SIZE];     //���鸳ֵ-shuzu_quick
	int shuzu_shell[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 04 };         //���鸳ֵ-shuzu_shell
	memcpy(shuzu_bubbleopt, shuzu, sizeof(shuzu));
	memcpy(shuzu_selection, shuzu, sizeof(shuzu));
	memcpy(shuzu_insertion, shuzu, sizeof(shuzu));
	//memcpy(shuzu_shell, shuzu, sizeof(shuzu));
	memcpy(shuzu_quick, shuzu, sizeof(shuzu));

	BubbleSort(shuzu, SIZE);   //ð������
	BubbleSort_Optimize(shuzu_bubbleopt, SIZE);     //�Ż���ð������
	SelectionSort(shuzu_selection, SIZE);  //ѡ������
	InsertionSort(shuzu_insertion, SIZE);  //ѡ������
	ShellSort(shuzu_shell, 10);  //shell����
	quick_sort(shuzu_quick, 0, SIZE-1);  //��������
	
	printf("\nBubbleSort����������:\n");     //���ð��
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu[i]);
	}

	printf("\nBubbleSort����������:\n");     //���ð���Ż�
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_bubbleopt[i]);
	}

	printf("\nSelectionSort����������:\n");     //���ѡ��
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_selection[i]);
	}

	printf("\nInsertionSort����������:\n");     //�������
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_insertion[i]);
	}
	
	printf("\nQuickSort����������:\n");     //�������
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_quick[i]);
	}

	scanf("%d", &shuzu[0]);

	return 0;
}

