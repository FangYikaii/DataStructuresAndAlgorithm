// 栈-练习.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 50

typedef struct
{
	char name[10];     //名字
	int age;           //年龄
}DATA;

typedef struct stack   
{
	DATA data[MAXLEN + 1];     //数据元素
	int top;                    //栈顶
}StackType; 

StackType* STInit()
{
	StackType* p;  //定义栈的变量
	p = (StackType*)malloc(sizeof(StackType));  //申请栈内存
	if (p != NULL)
	{
		p->top = 0;   //设置栈顶为0
		return p;    //返回指向栈的指针
	}
	else
	{
		return NULL;
	}
}

int STIsEmpty(StackType *s)  //判断栈是否为空
{
	int t;
	t = (s->top == 0);   //如果为空，返回1，；如果不为空，返回0
	return t;
}

int STIsFull(StackType *s)  //判断栈是否为满
{
	int t;
	t = (s->top == MAXLEN);  //如果满，返回1；如果不为满，返回0
	return t;
}

void STClear(StackType *s)   //清空栈
{
	s->top = 0;
}

void STFree(StackType *s)  //释放栈所占的空间
{
	if (s)
	{
		free(s);
	}
}

//输入：栈指针，数据值
int PushST(StackType *s, DATA data)  //入栈操作
{
	if ((s->top + 1) > MAXLEN)  
	{
		printf("栈溢出!\n");
		return 0;
	}
	s->data[++s->top] = data;     //将元素入栈：先top+1,再入栈
	return 1;
}

DATA PopST(StackType *s)  //出栈
{
	if (s->top == 0)
	{
		printf("栈为空!\n");
		exit(0);
	}
	return(s->data[s->top--]);  //将元素出栈：先出栈，再top-1
}

DATA PeekST(StackType *s)  //读栈顶元素
{
	if (s->top == 0)
	{
		printf("栈为空!\n");
		exit(0);
	}
	return(s->data[s->top]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	StackType *stack;  //定义栈指针 
	DATA data, data1;  //定义数据1，数据2

	stack = STInit();  //初始化栈
	printf("入栈操作：\n");
	printf("输入姓名 年龄进行入栈操作：");
	do
	{
		scanf("%s%d", data.name, &data.age);
		if (strcmp(data.name, "0") == 0)  //如果名字为0
		{
			break;
		}
		//如果名字不为0
		else
		{
			//压入栈
			PushST(stack, data);
		}
	} while (1);

	do
	{
		printf("\n 出栈操作：按任意键进行出栈操作：");
		getchar();
		//出栈
		data1 = PopST(stack);
		//显示数据
		printf("出栈的数据是（%s，%d）\n", data1.name, data1.age);
	} while (1);

	STFree(stack);         
	getchar();

	return 0;
}

