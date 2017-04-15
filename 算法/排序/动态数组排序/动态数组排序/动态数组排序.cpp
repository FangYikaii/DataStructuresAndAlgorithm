// ��̬��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	char data;
	struct node* next;
}LNode,*LinkList;

LinkList CreatLinkList()
{
	char ch;
	LinkList list = NULL;

	scanf("%c", &ch);         //��������ĵ�һ������
	list = (LinkList)malloc(sizeof(LNode));
	list->data = ch;
	list->next = NULL;
	return list;
}

void insertList(LinkList* list, LinkList q, char e)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = e;
	if (!*list)    //���listΪ�գ���p��Ϊ������λ
	{
		*list = p;
		p->next = NULL;
	}
	else     //��q�ڵ����p
	{
		p->next = q->next;
		q->next = p;
	}
}

void DynamicSort(LinkList q)  //��̬����
{
	LNode *p = q;
	int i, j, k = 0;
	char t;
	while (p)
	{
		k++;
		p = p->next;
	}
	p = q;
	for (i = 0; i < k - 1; i++)    //ð������
	{
		for (j = 0; j<k - i - 1; j++)
		{
			if (p->data>p->next->data)         //�����ǰ����ڵ�����>��һ���ڵ����ݣ���������
			{
				t = p->data;
				p->data = p->next->data;
				p->next->data = t;
			}
			p = p->next;         //pָ����һ���ڵ�
		}
		p = q;    //ָ���ʼλ��
	}
}

 
int _tmain(int argc, _TCHAR* argv[])
{
	char ch;
	LinkList list, q;        //��������
	printf("��̬��������\n");
	printf("������һ���ַ�,��0������\n");
	q = list = CreatLinkList();     //��������ڵ�

	scanf("%c", &ch);
	while (ch != '0')
	{
		insertList(&list, q, ch);     //��̬��������
		q = q->next;
		scanf("%c", &ch);
	}

	DynamicSort(list);   //��̬��������
	printf("\n");
	printf("�Ը���������󣬵õ����µĽ����\n");  
	while (list)
	{
		printf("%c", list->data);  //��������ӡ
		list = list->next;
	}
	
	scanf("%c", &ch);
	return 0;
}

