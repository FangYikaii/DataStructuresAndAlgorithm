#include <stdio.h>  
#include "stdlib.h"
#include <malloc.h>  
#include <windows.h>
/*
队列：
“先进先出”的存储结构。
①链式队列（由链表实现，跟链表差不多）。
②静态队列（由数组实现），静态队列通常都必须是循环队列。

循环队列的两个参数：
①front,front指向队列的第一个元素。
②rear,rear指向队列的最后一个有效元素的下一元素。
队列的两个基本操作：出队和入队。
========================================================
入队（尾部入队）
①将值存入rear所代表的位置。
②rear = (rear+1)%数组的长度。

出队（头部出队）
front = (front+1)%数组的长度。

队列是否为空
front和rear的值相等，则该队列就一定为空。

队列是否已满
注意：循环队列中，有n个位置，通常放n-1个值，空1个
在循环队列中，front和rear指向的值不相关，无规律。front可能比rear指向的值大，也可能比rear指向的值小，也可能两者相等。

算法：
①多增加一个标识参数。
②少用一个元素，rear和front指向的值紧挨着，则队列已满。
*/

/*
#include <stdlib.h>
int rand(void);
返回一个伪随机数，范围是0-RAND_MAX(尽管实现不同，但至少是32767)
void srand(unsigned int seed);
设置伪随机数算法的种子，如果seed相同，生成的伪随机数会每次相同


随机数：
(1)rand()%n   范围：0~n-1
(2)n+rand()%(m-n+1)   范围：0~n-1
(3)rand()%(double)(RAND_MAX/x)   范围：0~n double
(4)
*/
#define random_int(x)        (rand()%x)                          //整型随机数
#define random_double(x)      (rand()/(double)(RAND_MAX/x))       //双精度型随机数
#define MAX_LENGTH           100                                 //队列最大长度
#define TRUE                 1
#define FALSE                0
//数据域
typedef struct Item
{
	int DigitalChannelData[2];            //数字量
	double AnalogChannelData[2];          //模拟量
}Item;

//队列结构
typedef struct QueueStatic
{
	Item* pBase;           //用于动态分配内存，pBase用于保存指向Item的指针数组的首地址
	int front;             //指向头结点
	int rear;              //指向尾节点
}QS;

//函数声明  
Item initItem(Item item);               //初始化一个Item结构

void initQueue(QS* pQs);                //队列初始化的函数  
int enQueue(QS* pQs, Item item);        //入队的函数   
int outQueue(QS* pQs, Item* pItem);     //出队的函数,同时保存出队的元素 
int isEmpty(QS* pQs);                   //判断队列是否为空的函数  
int isFull(QS* pQs);                    //判断队列是否满的函数   
void traverseQueue(QS* pQs);            //遍历队列的函数  

void main()
{
	QS qs;                      //创建队列对象的指针
	Item item = { 0, 0, 0, 0 };                   //用于保存出队列元素的地址
	srand((unsigned)time(NULL));         //设置伪随机数算法的种子
	initQueue(&qs);
	while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			item = initItem(item);
			enQueue(&qs, item);
		}
		printf("(1)入队列：\n");
		traverseQueue(&qs);
		Sleep(3000);

		printf("(2)出队列：\n");
		while (!isEmpty(&qs))
		{
			if (outQueue(&qs, &item))
			{
				printf("出队：%d %d %6.2f %6.2f\n", item.DigitalChannelData[0], item.DigitalChannelData[0], item.AnalogChannelData[0], item.AnalogChannelData[1]);
			}
		}
		Sleep(3000);

		printf("(3)清空队列，此刻队列:\n");
		traverseQueue(&qs);

		Sleep(3000);
	}
	
}



/*
参数
Item:
返回值
Item：

该函数用于初始化一个Item
*/
Item initItem(Item item)
{
	item.DigitalChannelData[0] = random_int(10);
	item.DigitalChannelData[1] = random_int(10);
	item.AnalogChannelData[0] = random_double(100);
	item.AnalogChannelData[1] = random_double(1000);
	return item;
}

/*
输入：
pQs:输入队列结构的指针

初始化队列
*/
void initQueue(QS* pQs)
{
	pQs->pBase = (Item*)malloc(sizeof(Item)*MAX_LENGTH);   //动态分配MAX_LENGTH个Item型数据所占空间 
	pQs->front = 0;                                        //初始化，front和rear值为0
	pQs->rear = 0;
}

/*
输入：
pQs:输入队列结构的头指针
item：数据域

入队列函数的实现
*/
int enQueue(QS* pQs, Item item)
{
	if (isFull(pQs))
	{
		printf("队列已满，入队列失败！\n");
		return FALSE;
	}
	else
	{
		//向队列中添加新的元素
		pQs->pBase[pQs->rear] = item;
		pQs->rear = (pQs->rear + 1) % MAX_LENGTH;       //余数，令rear取值范围：0-MAX_LENGTH
		return TRUE;
	}
}

/*
输入：
pQs：输入队列结构的头指针
pItem:出队列的节点的数据域的指针

出队的函数,同时保存出队的元素
*/
int outQueue(QS* pQs, Item* pItem)
{
	//如果队列为空，返回false
	if (isEmpty(pQs))
	{
		printf("队列为空，出队列失败！\n");
		return FALSE;
	}
	else
	{
		*pItem = pQs->pBase[pQs->front];
		pQs->front = (pQs->front + 1) % MAX_LENGTH;
		return TRUE;
	}
}

/*
输入：
pQs：输入队列结构的头指针

遍历队列函数的实现
*/
void traverseQueue(QS* pQs)
{
	int i = pQs->front;             //从队列头开始
	printf("遍历队列：\n");
	while (i != pQs->rear)             //如果没有达到rear位置，就开始循环
	{
		printf("%d %d %6.2f %6.2f\n", pQs->pBase[i].DigitalChannelData[0], pQs->pBase[i].DigitalChannelData[0], pQs->pBase[i].AnalogChannelData[0], pQs->pBase[i].AnalogChannelData[1]);
		i = (i + 1) % MAX_LENGTH;              //移动到下一个位置
	}
	printf("\n");
}

/*
输入：
pQs：输入队列结构的头指针

判断队列是否已满的函数实现
*/
int isFull(QS* pQs)
{
	if ((pQs->rear + 1) % MAX_LENGTH == pQs->front)       //队列满
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
输入：
pQs：输入队列结构的头指针

判断队列是否为空的函数实现
*/
int isEmpty(QS* pQs)
{
	if (pQs->rear == pQs->front)       //队列满
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}