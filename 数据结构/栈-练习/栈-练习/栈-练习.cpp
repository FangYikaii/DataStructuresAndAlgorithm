// ջ-��ϰ.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 50

typedef struct
{
	char name[10];     //����
	int age;           //����
}DATA;

typedef struct stack   
{
	DATA data[MAXLEN + 1];     //����Ԫ��
	int top;                    //ջ��
}StackType; 

StackType* STInit()
{
	StackType* p;  //����ջ�ı���
	p = (StackType*)malloc(sizeof(StackType));  //����ջ�ڴ�
	if (p != NULL)
	{
		p->top = 0;   //����ջ��Ϊ0
		return p;    //����ָ��ջ��ָ��
	}
	else
	{
		return NULL;
	}
}

int STIsEmpty(StackType *s)  //�ж�ջ�Ƿ�Ϊ��
{
	int t;
	t = (s->top == 0);   //���Ϊ�գ�����1���������Ϊ�գ�����0
	return t;
}

int STIsFull(StackType *s)  //�ж�ջ�Ƿ�Ϊ��
{
	int t;
	t = (s->top == MAXLEN);  //�����������1�������Ϊ��������0
	return t;
}

void STClear(StackType *s)   //���ջ
{
	s->top = 0;
}

void STFree(StackType *s)  //�ͷ�ջ��ռ�Ŀռ�
{
	if (s)
	{
		free(s);
	}
}

//���룺ջָ�룬����ֵ
int PushST(StackType *s, DATA data)  //��ջ����
{
	if ((s->top + 1) > MAXLEN)  
	{
		printf("ջ���!\n");
		return 0;
	}
	s->data[++s->top] = data;     //��Ԫ����ջ����top+1,����ջ
	return 1;
}

DATA PopST(StackType *s)  //��ջ
{
	if (s->top == 0)
	{
		printf("ջΪ��!\n");
		exit(0);
	}
	return(s->data[s->top--]);  //��Ԫ�س�ջ���ȳ�ջ����top-1
}

DATA PeekST(StackType *s)  //��ջ��Ԫ��
{
	if (s->top == 0)
	{
		printf("ջΪ��!\n");
		exit(0);
	}
	return(s->data[s->top]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	StackType *stack;  //����ջָ�� 
	DATA data, data1;  //��������1������2

	stack = STInit();  //��ʼ��ջ
	printf("��ջ������\n");
	printf("�������� ���������ջ������");
	do
	{
		scanf("%s%d", data.name, &data.age);
		if (strcmp(data.name, "0") == 0)  //�������Ϊ0
		{
			break;
		}
		//������ֲ�Ϊ0
		else
		{
			//ѹ��ջ
			PushST(stack, data);
		}
	} while (1);

	do
	{
		printf("\n ��ջ����������������г�ջ������");
		getchar();
		//��ջ
		data1 = PopST(stack);
		//��ʾ����
		printf("��ջ�������ǣ�%s��%d��\n", data1.name, data1.age);
	} while (1);

	STFree(stack);         
	getchar();

	return 0;
}

