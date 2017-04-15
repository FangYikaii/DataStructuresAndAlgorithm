// 二叉树-练习.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define MANLEN 20  //定义最大长度






typedef char DATA;   //定义元素类型

typedef struct CBT
{
	DATA data;  //元素数据
	struct CBT* left;  //左子树节点指针
	struct CBT* right;  //右子树节点指针
}CBTType;

CBTType *InitTree();
void AddTreeNode(CBTType *);
CBTType* TreeFindNode(CBTType*, DATA);
CBTType* TreeLeftNode(CBTType*);
CBTType* TreeRightNode(CBTType*);
int TreeIsEmpty(CBTType*);
int TreeDepth(CBTType *);
void ClearTree(CBTType*);
void ClearTree(CBTType*);
void TreeNodeData(CBTType*);/*
void LevelTree(CBTType*, void(*TreeNodeData));
void DLRTree(CBTType*, void(*TreeNodeData));
void LRDTree(CBTType*, void(*TreeNodeData));
void LDRTree(CBTType*, void(*TreeNodeData));*/

CBTType *InitTree()
{
	CBTType *node;
	node = (CBTType*)malloc(sizeof(CBTType));
	if (node != NULL)
	{
		printf("请先输入一个根节点数据：");
		scanf("%s", &node->data);
		node->left = NULL;
		node->right = NULL;
		if (node != NULL)
		{
			return node;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

void AddTreeNode(CBTType *treeNode)  //添加节点
{
	CBTType *pnode, *parent;
	DATA data;
	char menusel;
	pnode = (CBTType*)malloc(sizeof(CBTType));  //分配内存
	//若不为空
	if (pnode != NULL)
	{
		printf("输入二叉树节点数据：\n");
		fflush(stdin);  //清空输入缓冲区
		scanf("%s", &pnode->data);  
		pnode->left = NULL;  //设置左右子树为空
		pnode->right = NULL;

		printf("输入该节点的父节点数据：");
		fflush(stdin);  //清空输入缓冲区
		scanf("%s", &data);
		parent = TreeFindNode(treeNode, data);  //查找指定数据的节点
		//如果没有找到
		if (!parent)
		{
			printf("未找到该父节点！\n");
			free(pnode); //释放创建的节点内存
			return;
		}
		printf("1.添加该节点到左子树\n2.添加该节点到右子树\n");
		do
		{
			menusel = _getch();
			menusel -= '0';
			if (menusel == 1 || menusel == 2)
			{
				if (parent == NULL)
				{
					printf("不存在父节点，请先设置父节点！\n");
				}
				else
				{
					switch (menusel)
					{
					case 1:   //添加到左节点
						//如果左子树不为空
						if (parent->left)  
						{
							printf("左子树节点不为空！\n");
						}
						//如果左子树为空则添加
						else
						{
							parent->left = pnode;
						}
						break;
					case 2:
						//如果右子树不为空
						if (parent->right)
						{
							printf("右子树节点不为空!");
						}
						//如果右子树为空，则添加
						else
						{
							parent->right = pnode;
						}
						break;
					default:
						printf("无效参数！\n");
						break;
					}
				}
			}
		} while (menusel!=1&&menusel!=2);
	}
}

CBTType* TreeFindNode(CBTType* treeNode, DATA data)   //查找节点
{
	CBTType *ptr;

	if (treeNode == NULL)
	{
		return NULL;
	}
	else
	{
		if (treeNode->data == data)
		{
			return treeNode;
		}
		else
		{
			if (ptr = TreeFindNode(treeNode->left, data))   //分别向左右子树递归查找
			{
				return ptr;
			}
			else if (ptr = TreeFindNode(treeNode->right, data))
			{
				return ptr;
			}
			else
			{
				return NULL;
			}
		}
	}
}

CBTType* TreeLeftNode(CBTType* treeNode)  //获取左子树
{
	if (treeNode)
	{
		return treeNode->left;
	}
	else
	{
		return NULL;
	}
}

CBTType* TreeRightNode(CBTType* treeNode)  //获取右子树
{
	if (treeNode)
	{
		return treeNode->right;
	}		
	else
	{
		return NULL;
	}
}

int TreeIsEmpty(CBTType* treeNode)  //判断是否是空树：空1，不空0
{
	if (treeNode)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int TreeDepth(CBTType *treeNode)  //计算二叉树深度
{
	int depleft, depright;  
	if (treeNode == NULL)  //对于空树，深度为0
	{
		return 0;
	}
	else
	{
		depleft = TreeDepth(treeNode->left);  //递归调用：左子树深度
		depright = TreeDepth(treeNode->right);  //递归调用：右子树深度
		if (depleft>depright)
		{
			return depleft + 1;
		}
		else
		{
			return depright + 1;
		}
	}
}

void ClearTree(CBTType* treeNode)   //清空二叉树
{
	if (treeNode)
	{
		ClearTree(treeNode->left);
		ClearTree(treeNode->right);
		free(treeNode);
		treeNode = NULL;
	}
} 

void TreeNodeData(CBTType* p)  //显示节点数据
{
	printf("%c", p->data);
}

void LevelTree(CBTType* treeNode, void(*TreeNodeData)(CBTType* p))  //按层遍历
{
	CBTType *p; 
	CBTType *q[MANLEN];      //定义一个顺序栈
	int head = 0, tail = 0;  

	if (treeNode)   //如果队首指针不为空
	{
		tail = (tail + 1) % MANLEN;  //计算循环队列队尾序号
		q[tail] = treeNode;   //将二叉树根指针进队
	}
	while (head != tail)   //队列不为空，进行循环
	{
		head = (head + 1) % MANLEN;   //计算循环队列的队首序号
		p = q[head];                  //获取队首元素
		TreeNodeData(p);              //打印元素
		if (p->left != NULL)          //如果节点存在左子树
		{
			tail = (tail + 1) % MANLEN;  //计算循环队列的队尾序号
			q[tail] = p->left;         //将左子树进入队列
		}
		if (p->right != NULL) //如果节点存在右子树
		{
			tail = (tail + 1) % MANLEN; //计算循环队列的队尾序号
			q[tail] = p->right;  //将右子树进入队列
		}
	}
}

void DLRTree(CBTType* treeNode, void(*TreeNodeData)(CBTType*p))  //先序遍历：节点-左-右
{
	if (treeNode)
	{
		TreeNodeData(treeNode);
		DLRTree(treeNode->left, TreeNodeData);
		DLRTree(treeNode->right, TreeNodeData);
	}
}

void LDRTree(CBTType* treeNode, void(*TreeNodeData)(CBTType*p))  //中序遍历：左-节点-右
{
	if (treeNode)
	{
		LDRTree(treeNode->left, TreeNodeData);
		TreeNodeData(treeNode);
		LDRTree(treeNode->right, TreeNodeData);
	}
}
  
void LRDTree(CBTType* treeNode, void(*TreeNodeData)(CBTType*p))  //后序遍历：右-左-节点
{
	if (treeNode)
	{
		LRDTree(treeNode->left, TreeNodeData);
		LRDTree(treeNode->right, TreeNodeData);
		TreeNodeData(treeNode);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CBTType *root = NULL;        //root为指向二叉树节点的指针
	char menusel;
	void(*TreeNodeData1)(CBTType* p);     //指向函数的指针
	TreeNodeData1 = TreeNodeData;  //指向具体操作的函数
	//设置根元素
	root = InitTree();
	do
	{
		printf("请选择菜单添加二叉树的节点\n");
		printf("0.退出\t");
		printf("1.添加二叉树的节点\n");
		menusel = _getch();
		switch (menusel)
		{
		case '1':
			AddTreeNode(root);
			break;
		case '0':
			break;
		default:
			break;
		}
	} while (menusel != '0');

	//遍历
	do
	{
		printf("请选择菜单遍历二叉树，输入0表示退出：\n");
		printf("1.先序遍历DLR\t");
		printf("2.中序遍历LDR\n");
		printf("3.后序遍历LRD\t");
		menusel = _getch();
		switch (menusel)
		{
		case '0':
			break;
		case '1':
			printf("\n 先序遍历DLR结果：");
			DLRTree(root, TreeNodeData1);
			printf("\n");
			break;
		case '2':
			printf("\n 中序LDR遍历的结果：");
			LDRTree(root, TreeNodeData1);
			printf("\n");
			break;
		case '3':
			printf("\n 后序LRD遍历的结果：");
			LRDTree(root, TreeNodeData1);
			printf("\n");
			break;
		case '4':
			printf("\n 按层遍历的结果：");
			LevelTree(root, TreeNodeData1);
			printf("\n");
			break;
		}
	} while (menusel != '0');
	//深度
	printf("\n 二叉树深度为：%d\n", TreeDepth(root));

	ClearTree(root);  //清空二叉树

	return 0;
}

