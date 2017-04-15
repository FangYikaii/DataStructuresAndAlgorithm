// 二叉树的遍历.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

//二叉树结点结构
typedef struct BiTNode{
	char ch;            //结点数据
	struct BiTNode *lchild;        //左孩子
	struct BiTNode *rchild;        //右孩子
}BiTNode, *BiTree;


void AddBiTree(BiTree, BiTree);//创建二叉树
void PreOrderTraverse(BiTNode *); //前序遍历
void InOrderTraverse(BiTNode *);   //中序遍历
void PostOrderTraverse(BiTNode *);  //后序遍历


void main()
{
	char ch;//结点数据
	BiTree T, p;//树T，和临时树p
	printf("请输入结点内容(以空格为结束标识):");
	scanf("%c", &ch);//读入用户输入
	T = NULL;

	while (ch != ' ')
	{	
		//判断输入
		//创建新结点-临时树p
		if (p = (BiTNode *)malloc(sizeof(BiTNode)))      //p = (BiTNode *)malloc(sizeof(BiTNode))  分配内存
		{
			p->ch = ch;
			p->lchild = NULL; 
			p->rchild = NULL;
		}
		else
		{
			printf("内存分配出错.\n");
			exit(0);
		}
		//添加临时树p进入T
		if (T == NULL)   //如果为根节点 
			T = p;
		else
			AddBiTree(T, p);   //创造二叉树
		scanf("%c", &ch);       //读入用户输入
	}
	//输出遍历结果
	printf("前序遍历：\n");
	PreOrderTraverse(T);
	printf("\n中序遍历：\n");
	InOrderTraverse(T);
	printf("\n后序遍历：\n");
	PostOrderTraverse(T);
	int x;
	cin >> x;
}


//创造二叉树
//p节点插入T节点
void AddBiTree(BiTree T, BiTree p)
{
	//p节点的值小于T节点的值&&T节点左子树不为NULL
	//以T节点左子树为节点，重新查找插入
	if ((p->ch <= T->ch) && (T->lchild != NULL))
		AddBiTree(T->lchild, p);
	//p节点的值小于T节点的值&&T节点右子树为NULL
	//插入T节点左子树
	else if ((p->ch <= T->ch) && (T->lchild == NULL))
		T->lchild = p;
	//p节点的值大于T节点的值&&T节点右子树不为NULL
	//以T节点右子树为节点，重新查找插入
	else if (T->rchild != NULL)
		AddBiTree(T->rchild, p);
	//p节点的值大于T节点的值&&T节点右子树为NULL
	//插入T节点右子树
	else T->rchild = p;
}


//前序遍历
//节点-左子树-右子树
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

//中序遍历
//左子树-节点-右子树
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

//后序遍历
//左子树-右子树-节点
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

