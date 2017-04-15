// ���нṹ.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define QUEUELEN 15    //��󳤶�

typedef struct
{
	char name[10];  //����
	int age;        //����
}DATA;

typedef struct
{
	DATA data[QUEUELEN];  //����ֵ
	int head;  //ͷ
	int tail;  //β
}SQType;

SQType* SQTypeInit()  //���г�ʼ��
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

int SQTypeIsEmpty(SQType *q)   //�ж��Ƿ�Ϊ�գ�Ϊ�շ���1����Ϊ�շ���0
{
	int temp;
	temp = q->head == q->tail;
	return temp;
}

int SQTypeIsFull(SQType *q)  //�ж��Ƿ�Ϊ����Ϊ������1����Ϊ������0
{
	int temp;
	temp = q->tail == QUEUELEN;
	return temp;
}

void SQTypeClear(SQType *q)  //��ն���
{
	q->head = 0;  //���ö�ͷ
	q->tail = 0;  //���ö�β
}

void SQTypeFree(SQType *q)   //�ͷŶ���
{
	if (q != NULL)
	{
		free(q);
	}
}

int InSQType(SQType *q, DATA data)  //�����
{
	if (q->tail == QUEUELEN)
	{
		printf("��������������ʧ�ܣ�\n");
		return 0;
	}
	else
	{
		q->data[q->tail++] = data;  //��Ԫ�������
		return 1;
	}
}
 
DATA* OutSQType(SQType *q)  //������
{
	if (q->head == q->tail)
	{
		printf("\n �����ѿգ�����ʧ�ܣ�\n");
		exit(0);
	}
	else
	{
		return &(q->data[q->head++]);  //��ȡ������Ԫ�ص�ͷ��ַ���ٶ�head++�����롢ȡ���൱���������ݽṹ��index��ķ����ƶ���
	}
}

DATA *PeekSQType(SQType *q)
{
	if (SQTypeIsEmpty(q))
	{
		printf("\n �ն��У�\n");
		return NULL;
	}
	else
	{
		return &(q->data[q->head]);  //��ȡ������Ԫ�ص�ͷ��ַ�������ģ�
	}
}

int SQTypeLen(SQType *q)
{
	int temp;
	temp = q->tail - q->head;  //����=β-ͷ
	return temp;
}


int _tmain(int argc, _TCHAR* argv[])
{
	SQType *stack;
	DATA data;
	DATA *data1;

	stack = SQTypeInit();  //��ʼ������
	printf("����в�����\n");
	printf("�������� ����  ������в�����");
	do
	{
		scanf("%s%d", data.name, &data.age);
		if (strcmp(data.name, "0") == 0)
		{
			break;       //������0�����˳�
		}
		else
		{
			InSQType(stack, data); //�������
		}
	} while (1);

	do
	{
		printf("�����в���������������г�ջ������\n");
		getchar();
		data1 = OutSQType(stack);
		printf("�����е������ǣ�%s��%d��\n", data1->name, data1->age);

	} while (1);

	SQTypeFree(stack);  //�ͷŶ�����ռ�ÿռ�




	return 0;
}

  