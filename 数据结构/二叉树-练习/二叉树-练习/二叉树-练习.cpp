// ������-��ϰ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define MANLEN 20  //������󳤶�






typedef char DATA;   //����Ԫ������

typedef struct CBT
{
	DATA data;  //Ԫ������
	struct CBT* left;  //�������ڵ�ָ��
	struct CBT* right;  //�������ڵ�ָ��
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
		printf("��������һ�����ڵ����ݣ�");
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

void AddTreeNode(CBTType *treeNode)  //��ӽڵ�
{
	CBTType *pnode, *parent;
	DATA data;
	char menusel;
	pnode = (CBTType*)malloc(sizeof(CBTType));  //�����ڴ�
	//����Ϊ��
	if (pnode != NULL)
	{
		printf("����������ڵ����ݣ�\n");
		fflush(stdin);  //������뻺����
		scanf("%s", &pnode->data);  
		pnode->left = NULL;  //������������Ϊ��
		pnode->right = NULL;

		printf("����ýڵ�ĸ��ڵ����ݣ�");
		fflush(stdin);  //������뻺����
		scanf("%s", &data);
		parent = TreeFindNode(treeNode, data);  //����ָ�����ݵĽڵ�
		//���û���ҵ�
		if (!parent)
		{
			printf("δ�ҵ��ø��ڵ㣡\n");
			free(pnode); //�ͷŴ����Ľڵ��ڴ�
			return;
		}
		printf("1.��Ӹýڵ㵽������\n2.��Ӹýڵ㵽������\n");
		do
		{
			menusel = _getch();
			menusel -= '0';
			if (menusel == 1 || menusel == 2)
			{
				if (parent == NULL)
				{
					printf("�����ڸ��ڵ㣬�������ø��ڵ㣡\n");
				}
				else
				{
					switch (menusel)
					{
					case 1:   //��ӵ���ڵ�
						//�����������Ϊ��
						if (parent->left)  
						{
							printf("�������ڵ㲻Ϊ�գ�\n");
						}
						//���������Ϊ�������
						else
						{
							parent->left = pnode;
						}
						break;
					case 2:
						//�����������Ϊ��
						if (parent->right)
						{
							printf("�������ڵ㲻Ϊ��!");
						}
						//���������Ϊ�գ������
						else
						{
							parent->right = pnode;
						}
						break;
					default:
						printf("��Ч������\n");
						break;
					}
				}
			}
		} while (menusel!=1&&menusel!=2);
	}
}

CBTType* TreeFindNode(CBTType* treeNode, DATA data)   //���ҽڵ�
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
			if (ptr = TreeFindNode(treeNode->left, data))   //�ֱ������������ݹ����
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

CBTType* TreeLeftNode(CBTType* treeNode)  //��ȡ������
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

CBTType* TreeRightNode(CBTType* treeNode)  //��ȡ������
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

int TreeIsEmpty(CBTType* treeNode)  //�ж��Ƿ��ǿ�������1������0
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

int TreeDepth(CBTType *treeNode)  //������������
{
	int depleft, depright;  
	if (treeNode == NULL)  //���ڿ��������Ϊ0
	{
		return 0;
	}
	else
	{
		depleft = TreeDepth(treeNode->left);  //�ݹ���ã����������
		depright = TreeDepth(treeNode->right);  //�ݹ���ã����������
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

void ClearTree(CBTType* treeNode)   //��ն�����
{
	if (treeNode)
	{
		ClearTree(treeNode->left);
		ClearTree(treeNode->right);
		free(treeNode);
		treeNode = NULL;
	}
} 

void TreeNodeData(CBTType* p)  //��ʾ�ڵ�����
{
	printf("%c", p->data);
}

void LevelTree(CBTType* treeNode, void(*TreeNodeData)(CBTType* p))  //�������
{
	CBTType *p; 
	CBTType *q[MANLEN];      //����һ��˳��ջ
	int head = 0, tail = 0;  

	if (treeNode)   //�������ָ�벻Ϊ��
	{
		tail = (tail + 1) % MANLEN;  //����ѭ�����ж�β���
		q[tail] = treeNode;   //����������ָ�����
	}
	while (head != tail)   //���в�Ϊ�գ�����ѭ��
	{
		head = (head + 1) % MANLEN;   //����ѭ�����еĶ������
		p = q[head];                  //��ȡ����Ԫ��
		TreeNodeData(p);              //��ӡԪ��
		if (p->left != NULL)          //����ڵ����������
		{
			tail = (tail + 1) % MANLEN;  //����ѭ�����еĶ�β���
			q[tail] = p->left;         //���������������
		}
		if (p->right != NULL) //����ڵ����������
		{
			tail = (tail + 1) % MANLEN; //����ѭ�����еĶ�β���
			q[tail] = p->right;  //���������������
		}
	}
}

void DLRTree(CBTType* treeNode, void(*TreeNodeData)(CBTType*p))  //����������ڵ�-��-��
{
	if (treeNode)
	{
		TreeNodeData(treeNode);
		DLRTree(treeNode->left, TreeNodeData);
		DLRTree(treeNode->right, TreeNodeData);
	}
}

void LDRTree(CBTType* treeNode, void(*TreeNodeData)(CBTType*p))  //�����������-�ڵ�-��
{
	if (treeNode)
	{
		LDRTree(treeNode->left, TreeNodeData);
		TreeNodeData(treeNode);
		LDRTree(treeNode->right, TreeNodeData);
	}
}
  
void LRDTree(CBTType* treeNode, void(*TreeNodeData)(CBTType*p))  //�����������-��-�ڵ�
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
	CBTType *root = NULL;        //rootΪָ��������ڵ��ָ��
	char menusel;
	void(*TreeNodeData1)(CBTType* p);     //ָ������ָ��
	TreeNodeData1 = TreeNodeData;  //ָ���������ĺ���
	//���ø�Ԫ��
	root = InitTree();
	do
	{
		printf("��ѡ��˵���Ӷ������Ľڵ�\n");
		printf("0.�˳�\t");
		printf("1.��Ӷ������Ľڵ�\n");
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

	//����
	do
	{
		printf("��ѡ��˵�����������������0��ʾ�˳���\n");
		printf("1.�������DLR\t");
		printf("2.�������LDR\n");
		printf("3.�������LRD\t");
		menusel = _getch();
		switch (menusel)
		{
		case '0':
			break;
		case '1':
			printf("\n �������DLR�����");
			DLRTree(root, TreeNodeData1);
			printf("\n");
			break;
		case '2':
			printf("\n ����LDR�����Ľ����");
			LDRTree(root, TreeNodeData1);
			printf("\n");
			break;
		case '3':
			printf("\n ����LRD�����Ľ����");
			LRDTree(root, TreeNodeData1);
			printf("\n");
			break;
		case '4':
			printf("\n ��������Ľ����");
			LevelTree(root, TreeNodeData1);
			printf("\n");
			break;
		}
	} while (menusel != '0');
	//���
	printf("\n ���������Ϊ��%d\n", TreeDepth(root));

	ClearTree(root);  //��ն�����

	return 0;
}

