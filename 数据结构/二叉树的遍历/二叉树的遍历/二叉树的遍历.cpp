// �������ı���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

//���������ṹ
typedef struct BiTNode{
	char ch;            //�������
	struct BiTNode *lchild;        //����
	struct BiTNode *rchild;        //�Һ���
}BiTNode, *BiTree;


void AddBiTree(BiTree, BiTree);//����������
void PreOrderTraverse(BiTNode *); //ǰ�����
void InOrderTraverse(BiTNode *);   //�������
void PostOrderTraverse(BiTNode *);  //�������


void main()
{
	char ch;//�������
	BiTree T, p;//��T������ʱ��p
	printf("������������(�Կո�Ϊ������ʶ):");
	scanf("%c", &ch);//�����û�����
	T = NULL;

	while (ch != ' ')
	{	
		//�ж�����
		//�����½��-��ʱ��p
		if (p = (BiTNode *)malloc(sizeof(BiTNode)))      //p = (BiTNode *)malloc(sizeof(BiTNode))  �����ڴ�
		{
			p->ch = ch;
			p->lchild = NULL; 
			p->rchild = NULL;
		}
		else
		{
			printf("�ڴ�������.\n");
			exit(0);
		}
		//�����ʱ��p����T
		if (T == NULL)   //���Ϊ���ڵ� 
			T = p;
		else
			AddBiTree(T, p);   //���������
		scanf("%c", &ch);       //�����û�����
	}
	//����������
	printf("ǰ�������\n");
	PreOrderTraverse(T);
	printf("\n���������\n");
	InOrderTraverse(T);
	printf("\n���������\n");
	PostOrderTraverse(T);
	int x;
	cin >> x;
}


//���������
//p�ڵ����T�ڵ�
void AddBiTree(BiTree T, BiTree p)
{
	//p�ڵ��ֵС��T�ڵ��ֵ&&T�ڵ���������ΪNULL
	//��T�ڵ�������Ϊ�ڵ㣬���²��Ҳ���
	if ((p->ch <= T->ch) && (T->lchild != NULL))
		AddBiTree(T->lchild, p);
	//p�ڵ��ֵС��T�ڵ��ֵ&&T�ڵ�������ΪNULL
	//����T�ڵ�������
	else if ((p->ch <= T->ch) && (T->lchild == NULL))
		T->lchild = p;
	//p�ڵ��ֵ����T�ڵ��ֵ&&T�ڵ���������ΪNULL
	//��T�ڵ�������Ϊ�ڵ㣬���²��Ҳ���
	else if (T->rchild != NULL)
		AddBiTree(T->rchild, p);
	//p�ڵ��ֵ����T�ڵ��ֵ&&T�ڵ�������ΪNULL
	//����T�ڵ�������
	else T->rchild = p;
}


//ǰ�����
//�ڵ�-������-������
void PreOrderTraverse(BiTree T)
{
	//T!=NULL
	if (T)
	{
		printf("%c ", T->ch);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

//�������
//������-�ڵ�-������
void InOrderTraverse(BiTree T)
{
	//T!=NULL
	if (T)
	{
		InOrderTraverse(T->lchild);
		printf("%c ", T->ch);
		InOrderTraverse(T->rchild);
	}
}

//�������
//������-������-�ڵ�
void PostOrderTraverse(BiTree T)
{
	//T!=NULL
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ", T->ch);
	}
}

