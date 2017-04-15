// 线性表-链表练习.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct    //链表数据元素类型
{
	char key[10];     //关键字
	char name[20];    //名字
	int age;          //年龄
}Data;

typedef struct Node     //链表数据结构
{
	Data nodeData;           //链表的数据
	struct Node* nextNode;   //链表数据结构指针
}CLType;

/*
1、首先分配内存空间，保存新增的节点
2、从头指针head开始逐个检查，直到找到最后一个节点 
3、将表尾的节点地址设置为新增节点的地址
4、将新增节点的地址部分设置为NULL,即新增节点为表尾
输入：插入表的头指针，插入节点数据
输出：得到表的头指针
*/
CLType* CLAddEnd(CLType*head, Data nodedata)      //追加节点
{
	CLType *node, *htemp;  //定义两个链表数据结构：新增节点，临时节点(用于查找表尾)
	node = (CLType*)malloc(sizeof(CLType));
	if (node == NULL)
	{
		printf("申请内存失败！\n");
		return NULL;
	}
	else
	{
		node->nodeData = nodedata;   //保存数据
		node->nextNode = NULL;      //设置节点指针为空，即表尾
		//如果插入的链表为空
		if (head == NULL)
		{
			head = node;   //设置表头为node
			return head;
		}
		htemp = head;
		//查找链表的末尾
		while (htemp->nextNode != NULL)
		{
			htemp = htemp->nextNode;
		}
		//表尾节点置为node
		htemp->nextNode = node;
		return head;
	}
}

/*
1、首先分配内存空间，保存新增的节点
2、新增节点指向头指针head所指向的节点
3、头指针head指向新增节点
输入：插入表的头指针，插入节点数据
输出：得到表的头指针
*/
CLType* CLAddFirst(CLType* head, Data nodeData)   //插入头指针
{
	CLType* node;  //定义插入链表结构地址
	node = (CLType*)malloc(sizeof(CLType));
	if (node == NULL)
	{
		printf("申请内存失败！\n");
		return NULL;
	}
	else
	{
		node->nodeData = nodeData;      //保存数据
		node->nextNode = head;          //指向原本头指针head指向的节点
		head = node;                    //头指针指向新增节点
		return head;
	}
}

//查找节点
CLType* CLFindNode(CLType* head, char* key)
{
	CLType *htemp;   //定义一个链表结构指针
	htemp = head;    //保存链表头指针
	//若节点有效
	while (htemp)
	{
		if (strcmp(htemp->nodeData.key, key) == 0)  //若找到节点
		{
			return htemp;  //返回链表指针
		}
		htemp = htemp->nextNode;  //否则指向下一个节点
	}
	return NULL;    //返回空指针
}

/*
1、首先分配内存空间，保存新增的节点
2、找到要插入的逻辑位置
3、修改插入位置节点的指针，使其指向新增节点，而使新增节点指向原插入位置所指向的节点
输入：插入表的头指针，插入的关键值，插入节点数据
输出：得到表的头指针
*/ 
CLType* CLInsertNode(CLType* head, char* findkey, Data nodeData)       //插入节点
{
	CLType *node, *nodetemp;
	node = (CLType*)malloc(sizeof(CLType));
	if (node == NULL)
	{
		printf("申请内存失败！\n");
		return NULL;
	}
	node->nodeData = nodeData;
	//查找要插入的节点：输入：头指针、关键值；输出：要插入节点的地址
	nodetemp = CLFindNode(head, findkey); 
	//返回不为空
	if (nodetemp)
	{
		//新增节点指向原插入位置所指向的节点
		node->nextNode = nodetemp->nextNode;
		//修改插入位置节点的指针，使其指向新增节点
		nodetemp->nextNode = node;
	}
	else
	{
		printf("未找到正确的插入位置！\n");
		free(node);  //释放内存
	}
	return head;    //返回头指针
}


/*
1.查找需要删除的节点
2.使前一节点指向当前节点的下一节点
3.删除节点
*/
CLType* CLDeleteNode(CLType* head, char *key)  //删除节点
{
	CLType* node, *htemp;         //node保存删除节点的前一节点
	//如果删除的是首表头：
	htemp = head;
	if (strcmp(head->nodeData.key, key) == 0)
	{
		head = htemp->nextNode;
		free(htemp);
		return head;
	}
	//如果删除的不是表头            
	node = head;
	while (htemp)
	{
		if (strcmp(htemp->nodeData.key, key) == 0)
		{
			node->nextNode = htemp->nextNode;   //使前一个节点指向当前节点的下一个节点（略过htemp)
			free(htemp);    //释放内存
			return head;      //已经删除
		}
		else
		{
			node = htemp;             //node指向当前节点
			htemp = htemp->nextNode;  //htemp指向下一个节点
		}
	}
	return head;        //未删除
}

int CLLength(CLType* head)    //计算链表的长度
{
	CLType *htemp;
	int Len = 0;   //长度
	htemp = head;
	while (htemp)  //遍历整个链表
	{
		Len++;   //累加节点长度
		htemp = htemp->nextNode;   //处理下一个节点
	}
	return Len;  //返回节点数量
}


void CLAllNode(CLType* head)         //遍历链表
{
	CLType *htemp;
	Data nodeData;
	htemp = head;
	printf("当前链表共有%d个节点。链表所有数据如下：\n", CLLength(head));
	while (htemp)
	{
		nodeData = htemp->nodeData;
		printf("节点（%s,%s,%d）\n", nodeData.key, nodeData.name, nodeData.age);
		htemp = htemp->nextNode;                    //处理下一个节点
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CLType *node, *head = NULL;
	Data nodeData;   //定义节点数据
	char key[10], findkey[10];

	printf("链表测试。先输入链表中的数据，格式为： 关键字 姓名 年龄\n");
	do
	{
		fflush(stdin);   //清空输入
		scanf("%s", nodeData.key);  //输入key
		//strcmp:如果str1==str2，返回0
		if (strcmp(nodeData.key, "0")==0)   //如果key为0
		{
			break;
		}
		else
		{
			scanf("%s%d", nodeData.name, &nodeData.age);   //输入名字 年龄
			head = CLAddEnd(head, nodeData);   //添加节点
		}
	} while (1);
	printf("\n 演示插入节点，输入插入位置的关键字：");
	scanf("%s", &findkey);     
	printf("输入插入节点的数据（关键字 姓名 年龄）：");
	scanf("%s%s%d", nodeData.key, nodeData.name, &nodeData.age);
	head = CLInsertNode(head, findkey, nodeData);   //插入节点
	CLAllNode(head);  //显示

	printf("\n 演示删除节点，输入要删除的关键字：");
	fflush(stdin);  //清空节点
	scanf("%s", key);   //输入删除的关键字
	head=CLDeleteNode(head, key);  //删除关键字节点
	CLAllNode(head);  //显示

	printf("\n 演示在链表中查找，输入查找关键字：");
	fflush(stdin);  //清空输入
	scanf("%s", key);  //输入查找的关键字
	node = CLFindNode(head, key);   //查找关键字节点
	if (node)  //如果找到关键字节点
	{
		nodeData = node->nodeData;
		printf("关键字%s对应的节点为（%s,%s,%d）\n", key, nodeData.key, nodeData.name, nodeData.age);	  //打印
	}
	else  //如果找不到关键字节点
	{
		printf("在链表为找到关键字为%s的节点！\n", key);
	}
	scanf("%s", key);
	return 0;
}

