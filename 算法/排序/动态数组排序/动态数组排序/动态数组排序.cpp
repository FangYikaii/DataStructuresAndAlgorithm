// 动态数组排序.cpp : 定义控制台应用程序的入口点。
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

	scanf("%c", &ch);         //输入链表的第一个数据
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
	if (!*list)    //如果list为空，把p置为链表首位
	{
		*list = p;
		p->next = NULL;
	}
	else     //往q节点插入p
	{
		p->next = q->next;
		q->next = p;
	}
}

void DynamicSort(LinkList q)  //动态排序
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
	for (i = 0; i < k - 1; i++)    //冒泡排序
	{
		for (j = 0; j<k - i - 1; j++)
		{
			if (p->data>p->next->data)         //如果当前链表节点数据>下一个节点数据，交换数据
			{
				t = p->data;
				p->data = p->next->data;
				p->next->data = t;
			}
			p = p->next;         //p指向下一个节点
		}
		p = q;    //指向初始位置
	}
}

 
int _tmain(int argc, _TCHAR* argv[])
{
	char ch;
	LinkList list, q;        //声明链表
	printf("动态数组排序！\n");
	printf("请输入一组字符,以0结束！\n");
	q = list = CreatLinkList();     //创建链表节点

	scanf("%c", &ch);
	while (ch != '0')
	{
		insertList(&list, q, ch);     //动态输入数据
		q = q->next;
		scanf("%c", &ch);
	}

	DynamicSort(list);   //动态输入数据
	printf("\n");
	printf("对该数组排序后，得到如下的结果：\n");  
	while (list)
	{
		printf("%c", list->data);  //遍历并打印
		list = list->next;
	}
	
	scanf("%c", &ch);
	return 0;
}

