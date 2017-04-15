// ���Ա�-������ϰ.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct    //��������Ԫ������
{
	char key[10];     //�ؼ���
	char name[20];    //����
	int age;          //����
}Data;

typedef struct Node     //�������ݽṹ
{
	Data nodeData;           //���������
	struct Node* nextNode;   //�������ݽṹָ��
}CLType;

/*
1�����ȷ����ڴ�ռ䣬���������Ľڵ�
2����ͷָ��head��ʼ�����飬ֱ���ҵ����һ���ڵ� 
3������β�Ľڵ��ַ����Ϊ�����ڵ�ĵ�ַ
4���������ڵ�ĵ�ַ��������ΪNULL,�������ڵ�Ϊ��β
���룺������ͷָ�룬����ڵ�����
������õ����ͷָ��
*/
CLType* CLAddEnd(CLType*head, Data nodedata)      //׷�ӽڵ�
{
	CLType *node, *htemp;  //���������������ݽṹ�������ڵ㣬��ʱ�ڵ�(���ڲ��ұ�β)
	node = (CLType*)malloc(sizeof(CLType));
	if (node == NULL)
	{
		printf("�����ڴ�ʧ�ܣ�\n");
		return NULL;
	}
	else
	{
		node->nodeData = nodedata;   //��������
		node->nextNode = NULL;      //���ýڵ�ָ��Ϊ�գ�����β
		//������������Ϊ��
		if (head == NULL)
		{
			head = node;   //���ñ�ͷΪnode
			return head;
		}
		htemp = head;
		//���������ĩβ
		while (htemp->nextNode != NULL)
		{
			htemp = htemp->nextNode;
		}
		//��β�ڵ���Ϊnode
		htemp->nextNode = node;
		return head;
	}
}

/*
1�����ȷ����ڴ�ռ䣬���������Ľڵ�
2�������ڵ�ָ��ͷָ��head��ָ��Ľڵ�
3��ͷָ��headָ�������ڵ�
���룺������ͷָ�룬����ڵ�����
������õ����ͷָ��
*/
CLType* CLAddFirst(CLType* head, Data nodeData)   //����ͷָ��
{
	CLType* node;  //�����������ṹ��ַ
	node = (CLType*)malloc(sizeof(CLType));
	if (node == NULL)
	{
		printf("�����ڴ�ʧ�ܣ�\n");
		return NULL;
	}
	else
	{
		node->nodeData = nodeData;      //��������
		node->nextNode = head;          //ָ��ԭ��ͷָ��headָ��Ľڵ�
		head = node;                    //ͷָ��ָ�������ڵ�
		return head;
	}
}

//���ҽڵ�
CLType* CLFindNode(CLType* head, char* key)
{
	CLType *htemp;   //����һ������ṹָ��
	htemp = head;    //��������ͷָ��
	//���ڵ���Ч
	while (htemp)
	{
		if (strcmp(htemp->nodeData.key, key) == 0)  //���ҵ��ڵ�
		{
			return htemp;  //��������ָ��
		}
		htemp = htemp->nextNode;  //����ָ����һ���ڵ�
	}
	return NULL;    //���ؿ�ָ��
}

/*
1�����ȷ����ڴ�ռ䣬���������Ľڵ�
2���ҵ�Ҫ������߼�λ��
3���޸Ĳ���λ�ýڵ��ָ�룬ʹ��ָ�������ڵ㣬��ʹ�����ڵ�ָ��ԭ����λ����ָ��Ľڵ�
���룺������ͷָ�룬����Ĺؼ�ֵ������ڵ�����
������õ����ͷָ��
*/ 
CLType* CLInsertNode(CLType* head, char* findkey, Data nodeData)       //����ڵ�
{
	CLType *node, *nodetemp;
	node = (CLType*)malloc(sizeof(CLType));
	if (node == NULL)
	{
		printf("�����ڴ�ʧ�ܣ�\n");
		return NULL;
	}
	node->nodeData = nodeData;
	//����Ҫ����Ľڵ㣺���룺ͷָ�롢�ؼ�ֵ�������Ҫ����ڵ�ĵ�ַ
	nodetemp = CLFindNode(head, findkey); 
	//���ز�Ϊ��
	if (nodetemp)
	{
		//�����ڵ�ָ��ԭ����λ����ָ��Ľڵ�
		node->nextNode = nodetemp->nextNode;
		//�޸Ĳ���λ�ýڵ��ָ�룬ʹ��ָ�������ڵ�
		nodetemp->nextNode = node;
	}
	else
	{
		printf("δ�ҵ���ȷ�Ĳ���λ�ã�\n");
		free(node);  //�ͷ��ڴ�
	}
	return head;    //����ͷָ��
}


/*
1.������Ҫɾ���Ľڵ�
2.ʹǰһ�ڵ�ָ��ǰ�ڵ����һ�ڵ�
3.ɾ���ڵ�
*/
CLType* CLDeleteNode(CLType* head, char *key)  //ɾ���ڵ�
{
	CLType* node, *htemp;         //node����ɾ���ڵ��ǰһ�ڵ�
	//���ɾ�������ױ�ͷ��
	htemp = head;
	if (strcmp(head->nodeData.key, key) == 0)
	{
		head = htemp->nextNode;
		free(htemp);
		return head;
	}
	//���ɾ���Ĳ��Ǳ�ͷ            
	node = head;
	while (htemp)
	{
		if (strcmp(htemp->nodeData.key, key) == 0)
		{
			node->nextNode = htemp->nextNode;   //ʹǰһ���ڵ�ָ��ǰ�ڵ����һ���ڵ㣨�Թ�htemp)
			free(htemp);    //�ͷ��ڴ�
			return head;      //�Ѿ�ɾ��
		}
		else
		{
			node = htemp;             //nodeָ��ǰ�ڵ�
			htemp = htemp->nextNode;  //htempָ����һ���ڵ�
		}
	}
	return head;        //δɾ��
}

int CLLength(CLType* head)    //��������ĳ���
{
	CLType *htemp;
	int Len = 0;   //����
	htemp = head;
	while (htemp)  //������������
	{
		Len++;   //�ۼӽڵ㳤��
		htemp = htemp->nextNode;   //������һ���ڵ�
	}
	return Len;  //���ؽڵ�����
}


void CLAllNode(CLType* head)         //��������
{
	CLType *htemp;
	Data nodeData;
	htemp = head;
	printf("��ǰ������%d���ڵ㡣���������������£�\n", CLLength(head));
	while (htemp)
	{
		nodeData = htemp->nodeData;
		printf("�ڵ㣨%s,%s,%d��\n", nodeData.key, nodeData.name, nodeData.age);
		htemp = htemp->nextNode;                    //������һ���ڵ�
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CLType *node, *head = NULL;
	Data nodeData;   //����ڵ�����
	char key[10], findkey[10];

	printf("������ԡ������������е����ݣ���ʽΪ�� �ؼ��� ���� ����\n");
	do
	{
		fflush(stdin);   //�������
		scanf("%s", nodeData.key);  //����key
		//strcmp:���str1==str2������0
		if (strcmp(nodeData.key, "0")==0)   //���keyΪ0
		{
			break;
		}
		else
		{
			scanf("%s%d", nodeData.name, &nodeData.age);   //�������� ����
			head = CLAddEnd(head, nodeData);   //��ӽڵ�
		}
	} while (1);
	printf("\n ��ʾ����ڵ㣬�������λ�õĹؼ��֣�");
	scanf("%s", &findkey);     
	printf("�������ڵ�����ݣ��ؼ��� ���� ���䣩��");
	scanf("%s%s%d", nodeData.key, nodeData.name, &nodeData.age);
	head = CLInsertNode(head, findkey, nodeData);   //����ڵ�
	CLAllNode(head);  //��ʾ

	printf("\n ��ʾɾ���ڵ㣬����Ҫɾ���Ĺؼ��֣�");
	fflush(stdin);  //��սڵ�
	scanf("%s", key);   //����ɾ���Ĺؼ���
	head=CLDeleteNode(head, key);  //ɾ���ؼ��ֽڵ�
	CLAllNode(head);  //��ʾ

	printf("\n ��ʾ�������в��ң�������ҹؼ��֣�");
	fflush(stdin);  //�������
	scanf("%s", key);  //������ҵĹؼ���
	node = CLFindNode(head, key);   //���ҹؼ��ֽڵ�
	if (node)  //����ҵ��ؼ��ֽڵ�
	{
		nodeData = node->nodeData;
		printf("�ؼ���%s��Ӧ�Ľڵ�Ϊ��%s,%s,%d��\n", key, nodeData.key, nodeData.name, nodeData.age);	  //��ӡ
	}
	else  //����Ҳ����ؼ��ֽڵ�
	{
		printf("������Ϊ�ҵ��ؼ���Ϊ%s�Ľڵ㣡\n", key);
	}
	scanf("%s", key);
	return 0;
}

