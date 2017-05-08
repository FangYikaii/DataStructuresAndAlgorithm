#include <stdio.h>  
#include "stdlib.h"
#include <malloc.h>  
#include <windows.h>
#include <string.h>
#define random_int(x)        (rand()%x)                          //整型随机数
#define random_double(x)      (rand()/(double)(RAND_MAX/x))       //双精度型随机数
#define MAX_LENGTH           7                                 //队列最大长度
#define TRUE                 1
#define FALSE                0
#define NULLKEY              -32768  


/*
比较两个结构体的大小：
struct ElemType;
ElemType a,b,c;

#include <string.h>

memcmp(&a,&b,sizeof(ElemType);
*/



//数据域
typedef struct Item
{
	int DigitalChannelData[2];            //数字量
	double AnalogChannelData[2];          //模拟量
	int key;                              //键值
}Item;

//Hash表
typedef struct HashTable
{
	Item* pitem;                         //用于动态分配内存，pBase用于保存指向Item的指针数组的首地址
	int count;
}HashTable;

int len = MAX_LENGTH;                                         //散列表表长
int arrKey[MAX_LENGTH] = { 13, 29, 27, 28, 26, 30, 38 };

Item initItem(Item item, int i);                                     //创建一个Item数据域结构体
int initHashTable(HashTable* hashTable);                             //创建Hash表
int HashFunction(int data);                                          //Hash函数
int insertHashTable(HashTable* hashTable, Item item);                //插入数据
int searchHashTable(HashTable* hashTable, int key);                //查找数据
void displayHashTable(HashTable* hashTable);

void main()
{
	int i, question, result;
	HashTable hashTable;
	Item item = { 0 };
	srand((unsigned)time(NULL));

	//初始化HashTable
	initHashTable(&hashTable);

	//插入数据
	for (i = 0; i < len; i++)
	{
		item = initItem(item, i);
		insertHashTable(&hashTable, item);
	}

	displayHashTable(&hashTable);        //打印hash表
	
	//查找数据
	while (1)
	{
		scanf("%d", &question);
		result = searchHashTable(&hashTable, question);
		if (result == FALSE)
		{
			printf("对不起，没有找到！\n");
		}
		else
		{
			printf("%d在哈希表中的位置是:%d\n", question, result);
			printf("值：%d %d %4.2f %4.2f\n", hashTable.pitem[result].DigitalChannelData[0], hashTable.pitem[result].DigitalChannelData[1], hashTable.pitem[result].AnalogChannelData[0], hashTable.pitem[result].AnalogChannelData[1]);
		}
		printf("\n\n");
	}
}


/*
参数
Item:
返回值
Item：
该函数用于初始化一个Item
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
哈希函数(除留余数法)
*/
int HashFunction(int data)
{
	return data % MAX_LENGTH;
}

/*
创建Hash表
*/
int initHashTable(HashTable* hashTable)
{
	int i;
	hashTable->pitem = (Item*)malloc(len*sizeof(Item));           //为指向Item的指针item申请内存(len*sizeof(Item))大小
	hashTable->count = len;
	for (i = 0; i < len; i++)
	{
		hashTable->pitem[i].key = NULLKEY;                       //置为空键值
	}
	return TRUE;
}

/*
输入：
hashTable:Hash表的指针
item:数据域

在Hash表中寻找数据
*/
int searchHashTable(HashTable* hashTable, int key)
{
	//求Hash地址
	int hashAddress = HashFunction(key);
	
	//如果发生冲突
	while (hashTable->pitem[hashAddress].key != key)
	{
		//利用开放定址的线性探测发解决冲突
		hashAddress = (++hashAddress) % MAX_LENGTH;
		//说明即使冲突了，也没有把数据域插入进去
		if (hashTable->pitem[hashAddress].key == NULLKEY || hashAddress == HashFunction(key))
		{
			return FALSE;
		}		
	}
	return hashAddress;
}

/*
输入：
hashTable:Hash表的指针
item:数据域

在Hash表中插入数据
*/
int insertHashTable(HashTable* hashTable, Item item)
{
	//求Hash地址
	int hashAddress = HashFunction(item.key);
	//如果发生冲突
	while (hashTable->pitem[hashAddress].key != NULLKEY)
	{
		//利用开放定址的线性探测发解决冲突
		hashAddress = (++hashAddress) % MAX_LENGTH;
	}
	//插入值
	hashTable->pitem[hashAddress] = item;
}

/*
输入：
hashTable:Hash表的指针

打印结果
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

