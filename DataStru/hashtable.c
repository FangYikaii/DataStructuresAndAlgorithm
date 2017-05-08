#include <stdio.h>  
#include "stdlib.h"
#include <malloc.h>  
#include <windows.h>
#include <string.h>
#define random_int(x)        (rand()%x)                          //���������
#define random_double(x)      (rand()/(double)(RAND_MAX/x))       //˫�����������
#define MAX_LENGTH           7                                 //������󳤶�
#define TRUE                 1
#define FALSE                0
#define NULLKEY              -32768  


/*
�Ƚ������ṹ��Ĵ�С��
struct ElemType;
ElemType a,b,c;

#include <string.h>

memcmp(&a,&b,sizeof(ElemType);
*/



//������
typedef struct Item
{
	int DigitalChannelData[2];            //������
	double AnalogChannelData[2];          //ģ����
	int key;                              //��ֵ
}Item;

//Hash��
typedef struct HashTable
{
	Item* pitem;                         //���ڶ�̬�����ڴ棬pBase���ڱ���ָ��Item��ָ��������׵�ַ
	int count;
}HashTable;

int len = MAX_LENGTH;                                         //ɢ�б��
int arrKey[MAX_LENGTH] = { 13, 29, 27, 28, 26, 30, 38 };

Item initItem(Item item, int i);                                     //����һ��Item������ṹ��
int initHashTable(HashTable* hashTable);                             //����Hash��
int HashFunction(int data);                                          //Hash����
int insertHashTable(HashTable* hashTable, Item item);                //��������
int searchHashTable(HashTable* hashTable, int key);                //��������
void displayHashTable(HashTable* hashTable);

void main()
{
	int i, question, result;
	HashTable hashTable;
	Item item = { 0 };
	srand((unsigned)time(NULL));

	//��ʼ��HashTable
	initHashTable(&hashTable);

	//��������
	for (i = 0; i < len; i++)
	{
		item = initItem(item, i);
		insertHashTable(&hashTable, item);
	}

	displayHashTable(&hashTable);        //��ӡhash��
	
	//��������
	while (1)
	{
		scanf("%d", &question);
		result = searchHashTable(&hashTable, question);
		if (result == FALSE)
		{
			printf("�Բ���û���ҵ���\n");
		}
		else
		{
			printf("%d�ڹ�ϣ���е�λ����:%d\n", question, result);
			printf("ֵ��%d %d %4.2f %4.2f\n", hashTable.pitem[result].DigitalChannelData[0], hashTable.pitem[result].DigitalChannelData[1], hashTable.pitem[result].AnalogChannelData[0], hashTable.pitem[result].AnalogChannelData[1]);
		}
		printf("\n\n");
	}
}


/*
����
Item:
����ֵ
Item��
�ú������ڳ�ʼ��һ��Item
*/
Item initItem(Item item,int i)
{
	item.DigitalChannelData[0] = random_int(10);
	item.DigitalChannelData[1] = random_int(10);
	item.AnalogChannelData[0] = random_double(10);
	item.AnalogChannelData[1] = random_double(10);
	item.key = arrKey[i];
	return item;
}


/*
��ϣ����(����������)
*/
int HashFunction(int data)
{
	return data % MAX_LENGTH;
}

/*
����Hash��
*/
int initHashTable(HashTable* hashTable)
{
	int i;
	hashTable->pitem = (Item*)malloc(len*sizeof(Item));           //Ϊָ��Item��ָ��item�����ڴ�(len*sizeof(Item))��С
	hashTable->count = len;
	for (i = 0; i < len; i++)
	{
		hashTable->pitem[i].key = NULLKEY;                       //��Ϊ�ռ�ֵ
	}
	return TRUE;
}

/*
���룺
hashTable:Hash���ָ��
item:������

��Hash����Ѱ������
*/
int searchHashTable(HashTable* hashTable, int key)
{
	//��Hash��ַ
	int hashAddress = HashFunction(key);
	
	//���������ͻ
	while (hashTable->pitem[hashAddress].key != key)
	{
		//���ÿ��Ŷ�ַ������̽�ⷢ�����ͻ
		hashAddress = (++hashAddress) % MAX_LENGTH;
		//˵����ʹ��ͻ�ˣ�Ҳû�а�����������ȥ
		if (hashTable->pitem[hashAddress].key == NULLKEY || hashAddress == HashFunction(key))
		{
			return FALSE;
		}		
	}
	return hashAddress;
}

/*
���룺
hashTable:Hash���ָ��
item:������

��Hash���в�������
*/
int insertHashTable(HashTable* hashTable, Item item)
{
	//��Hash��ַ
	int hashAddress = HashFunction(item.key);
	//���������ͻ
	while (hashTable->pitem[hashAddress].key != NULLKEY)
	{
		//���ÿ��Ŷ�ַ������̽�ⷢ�����ͻ
		hashAddress = (++hashAddress) % MAX_LENGTH;
	}
	//����ֵ
	hashTable->pitem[hashAddress] = item;
}

/*
���룺
hashTable:Hash���ָ��

��ӡ���
*/
void displayHashTable(HashTable* hashTable)
{
	int i;
	printf("\n==========================================================\n");
	for (i = 0; i < hashTable->count; i++)
	{
		printf("data:%d %d %4.2f %4.2f,key:%d\n", hashTable->pitem[i].DigitalChannelData[0], hashTable->pitem[i].DigitalChannelData[1], hashTable->pitem[i].AnalogChannelData[0], hashTable->pitem[i].AnalogChannelData[1], hashTable->pitem[i].key);
	}
	printf("\n==========================================================\n");
}

