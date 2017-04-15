// 排序算法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>

#define SIZE 8



/*
冒泡排序：
40 8 15 18 12 （文中仅细化了第一趟的比较过程）
第1趟: 8 15 18 12 40
第2趟: 8 15 12 18 40
第3趟: 8 12 15 18 40
第4趟: 8 12 15 18 40
依次比较相邻的数据，将小数据放在前，大数据放在后；
即第一趟先比较第1个和第2个数，大数在后，小数在前，
再比较第2个数与第3个数，大数在后，小数在前，
以此类推则将最大的数"滚动"到最后一个位置；
第二趟则将次大的数滚动到倒数第二个位置......第n-1(n为无序数据的个数)趟即能完成排序。
*/



/********************************************************
*函数名称：BubbleSort
*参数说明：pDataArray 无序数组；
*          iDataNum为无序数据个数
*说明：    冒泡排序
*********************************************************/
void BubbleSort(int* pDataArray, int iDataNum)
{
	for (int i = 0; i < iDataNum - 1; i++)        //走iDataNum-1趟
	{
		for (int j = 0; j < iDataNum - i - 1; j++)
		{
			if (pDataArray[j]>pDataArray[j + 1])    //如果Data前>Data后，交换值
			{
				int temp = pDataArray[j];
				pDataArray[j] = pDataArray[j + 1];
				pDataArray[j + 1] = temp;
			}
		}
	}
}

/********************************************************
*函数名称：BubbleSort_Optimize
*参数说明：pDataArray 无序数组；
*          iDataNum为无序数据个数
*说明：    冒泡排序优化
*********************************************************/
void BubbleSort_Optimize(int* pDataArray, int iDataNum)
{
	bool flag = false;         //记录是否存在交换
	for (int i = 0; i < iDataNum - 1; i++)   //走iDataNum-1趟
	{
		flag = false;
		for (int j = 0; j < iDataNum - i - 1; j++)
		{
			if (pDataArray[j]>pDataArray[j + 1])        //如果Data前>Data后，交换值
			{
				flag = true;
				int temp = pDataArray[j];
				pDataArray[j] = pDataArray[j + 1];
				pDataArray[j + 1] = temp;
			}
		}

		/*
		8 40 15 18 12  
		8 15 40 18 12  flag：true
		8 15 18 40 12   
		8 15 18 12 40              第一趟

		8 15 18 12 40  flag：flase
		8 15 12 18 40  flag：true
		8 15 12 18 40              第二趟

		8 15 12 18 40 
		8 12 15 18 40  flag:true   第三趟

		8 12 15 18 40  flag:false  第四趟，break，但是结束了
		*/
		if (!flag)    //上一趟比较中不存在交换，则退出排序  
		{
			break;
		}
	}
}


/*
选择排序：
第1个周期为：第1个和第2个比，第1个和第3个比，……第1个和第n个比；
最小的数被放在了第一位；
第2个周期为：第2个和第3个比，第2个和第4个比，……第2个和第n个比；
倒数第二小的数被放在了第二位；
…………………………… …………………………………第n-1个和第n个比；
最大的数被放在了最后一位。
*/

/********************************************************
*函数名称：BubbleSort_Optimize
*参数说明：pDataArray 无序数组；
*          iDataNum为无序数据个数
*说明：    冒泡排序优化
*********************************************************/
void SelectionSort(int* pDataArray, int iDataNum)
{
	int i, j, k;
	int temp;
	for (i = 0; i < iDataNum - 1; i++)  //外层iDataNum-1次
	{
		k = i;    //要被替换的那个index
		for (j = i + 1; j < iDataNum; j++)   //k之后的数组，如果有数比pDataArray[j]小，则替换
		{
			if (pDataArray[j] < pDataArray[k])  
			{
				k = j;      //k为最小的那个
			}
		}
		if (k != j)     //如果不等，说明被交换了,交换要被替换的数与最小值的位置
		{
			temp = pDataArray[i];
			pDataArray[i] = pDataArray[k];
			pDataArray[k] = temp;
		}
	}
}

/*
插入排序原理很简单，讲一组数据分成两组，我分别将其称为有序组与待插入组。
每次从待插入组中取出一个元素，与有序组的元素进行比较，并找到合适的位置，将该元素插到有序组当中。
就这样，每次插入一个元素，有序组增加，待插入组减少。直到待插入组元素个数为0。
当然，插入过程中涉及到了元素的移动。
*/

/********************************************************
*函数名称：InsertionSort
*参数说明：num 无序数组；
*          len为无序数据个数
*说明：    插入排序
*********************************************************/
void InsertionSort(int* num, int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)   //遍历n-1次
	{
		temp = num[i];  //从待插入组中取出第一个元素 
		j = i - 1;      //i-1为有续租的最后一个元素的下标
		while (j>=0 && temp < num[j])  //判断条件：j>=0对边界进行限制；temp<num[j]为插入判断条件，如果num[i]<num[j],num[j]向后移动一位
		{
			num[j + 1] = num[j];     //若不是合适的位置，有序组元素向后移动
			j--;          //向前判断
		}
		num[j + 1] = temp;   //找到合适位置，插入元素
	}
}


/*
Shell排序
*/

/********************************************************
*函数名称：ShellSort
*参数说明：a 无序数组；
*          len为无序数据个数
*说明：    Shell排序
*********************************************************/
void ShellSort(int* a, int len)
{
	int i, j, h;
	int r, temp;
	int x = 0;
	for (r = len / 2; r >= 1; r /= 2)     //划组排序的趟数:r为增量步长；每增加一次迭代r除于2；r>=1时迭代结束
	{
		for (i = r; i < len; i++)     //执行小循环的趟数：
		{
			temp = a[i];
			j = i - r;
			while (j >= 0 && temp < a[j])   //插入排序的实现
			{
				a[j+r] = a[j];
				j -= r;
			}
			a[j + r] = temp;
		}
		x++;
		printf("\n第%d步排序结果：", x);
		for (h = 0; h < len; h++)
		{
			printf("%d ", a[h]);
		}
		printf("\n");
	}
}

/*
快速排序
*/
/*
1．i =L; j = R; 将基准数挖出形成第一个坑a[i]。
2．j--由后向前找比它小的数，找到后挖出此数填前一个坑a[i]中。
3．i++由前向后找比它大的数，找到后也挖出此数填到前一个坑a[j]中。
4．再重复执行2，3二步，直到i==j，将基准数填入a[i]中。
*/
void quick_sort(int*s, int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];   //第一步：x为基准数
		while (i < j)                 //第二步，第三步
		{
			//从右向左找第一个小于x的数
			while (i < j&&s[j] >= x)     //如果i<j,且后面的数大于基准数，后面index--；直到小于基准数
			{
				j--;
			}
			if (i < j)
			{
				s[i++] = s[j];        //把小于基准数的s[j]填到第一个坑，i++
			}

			while (i < j&&s[i] < x)     //如果i<j,且前面的数大于基准数，前面index++；直到小于基准数
			{
				i++;
			}

			if (i < j)
			{
				s[j--] = s[i];          //把大于基准数的s[i]填到后面一个坑，j--
			}
		}

		s[i] = x;             //第四步：将基准数填入s[i]中	
		
		//分治
		/*
		分治，字面上的解释是“分而治之”，就是把一个复杂的问题分成两个或更多的相同或相似的子问题，再把子问题分成更小的子问题……
		直到最后子问题可以简单的直接求解，原问题的解即子问题的解的合并。在计算机科学中，分治法就是运用分治思想的一种很重要的算法。
		分治法是很多高效算法的基础，如排序算法（快速排序，归并排序），傅立叶变换（快速傅立叶变换）等等。
		*/
		quick_sort(s, l, i - 1);   //递归调用，分为[l,i-1],[i+1,r],因为s[i]前面的数据都小于s[i],s[i]后面的数都大于s[i]
		quick_sort(s, i + 1, r);		
	}
}


int _tmain(int argc, _TCHAR* argv[])
{

	int shuzu[SIZE];
	
	srand(time(NULL));   //随机种子
	for (int i = 0; i < SIZE; i++)
	{
		shuzu[i] = rand() / 1000 + 100;  //初始化数组
	}
	printf("排序前的数组为：\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu[i]);
	}

	int shuzu_bubbleopt[SIZE];     //数组赋值-shuzu_opt
	int shuzu_selection[SIZE];     //数组赋值-shuzu_selection
	int shuzu_insertion[SIZE];     //数组赋值-shuzu_insertion
	int shuzu_quick[SIZE];     //数组赋值-shuzu_quick
	int shuzu_shell[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 04 };         //数组赋值-shuzu_shell
	memcpy(shuzu_bubbleopt, shuzu, sizeof(shuzu));
	memcpy(shuzu_selection, shuzu, sizeof(shuzu));
	memcpy(shuzu_insertion, shuzu, sizeof(shuzu));
	//memcpy(shuzu_shell, shuzu, sizeof(shuzu));
	memcpy(shuzu_quick, shuzu, sizeof(shuzu));

	BubbleSort(shuzu, SIZE);   //冒泡排序
	BubbleSort_Optimize(shuzu_bubbleopt, SIZE);     //优化的冒泡排序
	SelectionSort(shuzu_selection, SIZE);  //选择排序
	InsertionSort(shuzu_insertion, SIZE);  //选择排序
	ShellSort(shuzu_shell, 10);  //shell排序
	quick_sort(shuzu_quick, 0, SIZE-1);  //快速排序
	
	printf("\nBubbleSort排序后的数组:\n");     //输出冒泡
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu[i]);
	}

	printf("\nBubbleSort排序后的数组:\n");     //输出冒泡优化
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_bubbleopt[i]);
	}

	printf("\nSelectionSort排序后的数组:\n");     //输出选择
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_selection[i]);
	}

	printf("\nInsertionSort排序后的数组:\n");     //输出插入
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_insertion[i]);
	}
	
	printf("\nQuickSort排序后的数组:\n");     //输出快速
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", shuzu_quick[i]);
	}

	scanf("%d", &shuzu[0]);

	return 0;
}

