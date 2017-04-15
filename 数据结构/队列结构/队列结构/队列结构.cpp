// 队列结构.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define QUEUELEN 15    //最大长度

typedef struct
{
	char name[10];  //名字
	int age;        //年龄
}DATA;

typedef struct
{
	DATA data[QUEUELEN];  //数据值
	int head;  //头
	int tail;  //尾
}SQType;

SQType* SQTypeInit()  //队列初始化
{
	SQType *q;
	q = (SQType*)malloc(sizeof(SQType));
	if (q != NULL)
	{
		q->head = 0;
		q->tail = 0;
		return q;
	}
	else
	{
		return NULL;
	}
}

int SQTypeIsEmpty(SQType *q)   //判断是否为空，为空返回1，不为空返回0
{
	int temp;
	temp = q->head == q->tail;
	return temp;
}

int SQTypeIsFull(SQType *q)  //判断是否为满，为满返回1，不为满返回0
{
	int temp;
	temp = q->tail == QUEUELEN;
	return temp;
}

void SQTypeClear(SQType *q)  //清空队列
{
	q->head = 0;  //设置队头
	q->tail = 0;  //设置队尾
}

void SQTypeFree(SQType *q)   //释放队列
{
	if (q != NULL)
	{
		free(q);
	}
}

int InSQType(SQType *q, DATA data)  //入队列
{
	if (q->tail == QUEUELEN)
	{
		printf("队列已满！操作失败！\n");
		return 0;
	}
	else
	{
		q->data[q->tail++] = data;  //将元素入队列
		return 1;
	}
}
 
DATA* OutSQType(SQType *q)  //出队列
{
	if (q->head == q->tail)
	{
		printf("\n 队列已空，操作失败！\n");
		exit(0);
	}
	else
	{
		return &(q->data[q->head++]);  //先取出队列元素的头地址，再对head++【插入、取出相当于整体数据结构往index大的方向移动】
	}
}

DATA *PeekSQType(SQType *q)
{
	if (SQTypeIsEmpty(q))
	{
		printf("\n 空队列！\n");
		return NULL;
	}
	else
	{
		return &(q->data[q->head]);  //先取出队列元素的头地址（出来的）
	}
}

int SQTypeLen(SQType *q)
{
	int temp;
	temp = q->tail - q->head;  //长度=尾-头
	return temp;
}


int _tmain(int argc, _TCHAR* argv[])
{
	SQType *stack;
	DATA data;
	DATA *data1;

	stack = SQTypeInit();  //初始化队列
	printf("入队列操作：\n");
	printf("输入姓名 年龄  进入队列操作：");
	do
	{
		scanf("%s%d", data.name, &data.age);
		if (strcmp(data.name, "0") == 0)
		{
			break;       //若输入0，则退出
		}
		else
		{
			InSQType(stack, data); //进入队列
		}
	} while (1);

	do
	{
		printf("出队列操作：按任意键进行出栈操作：\n");
		getchar();
		data1 = OutSQType(stack);
		printf("出队列的数据是（%s，%d）\n", data1->name, data1->age);

	} while (1);

	SQTypeFree(stack);  //释放队列所占用空间




	return 0;
}

  