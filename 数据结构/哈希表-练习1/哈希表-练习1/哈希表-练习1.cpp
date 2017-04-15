// ��ϣ��-��ϰ1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define DataType int
#define M 30

/*
HashTable[address].data
address:getHashAddress(key) ���� getHashAddress(key)+1
data:key
*/
typedef struct HashNode
{
	DataType data;     //�洢ֵ
	int isNull;        //��־��λ���Ƿ��ѱ����
}HashTable;

HashTable hashTable[M];

void InitHashTable()
{
	int i;
	for (i = 0; i < M; i++)
	{
		hashTable[i].isNull = 1;   //��ʼ״̬Ϊ��
	}
}

int getHashAddress(DataType key)     //Hash����
{
	return key % 29;
}

int insert(DataType key)                   //��hash���в���Ԫ��
{
	int address = getHashAddress(key);    //����hash���index
	if (hashTable[address].isNull == 1)    //û�з�����ͻ
	{
		hashTable[address].data = key;      //keyֵ
		hashTable[address].isNull = 0;      //��ʼ״̬��Ϊ�� 
	}
	else                                  //��������ͻ��ʱ��,���뵽address+1λ
	{
		while (hashTable[address].isNull == 0 && address < M)   //��ʼ��״̬��Ϊ�գ��ҵ�ַ��ΪM
		{
			address++;        //��������̽�ⷨ������Ϊ1
		}
		if (address == M)     //Hash�������
		{
			return -1;
		}
		hashTable[address].data = key;    //keyֵ
		hashTable[address].isNull = 0;   //��ʼ״̬��Ϊ��
	}
	return 0;
}

/*
��1)���Ŷ�ַ��
 ����һ���ؼ��ֺ���һ���ؼ��ַ�����ͻʱ��ʹ��ĳ��̽�⼼����Hash�����γ�һ��̽�����У�Ȼ���������̽���������β�����ȥ��������һ���յĵ�Ԫʱ����������С�
 �Ƚϳ��õ�̽�ⷽ��������̽�ⷨ��������һ��ؼ���{12��13��25��23��38��34��6��84��91}��Hash��Ϊ14��Hash����Ϊaddress(key)=key%11��
 ������12��13��25ʱ����ֱ�Ӳ��룬��������23ʱ����ַ1��ռ���ˣ�������ŵ�ַ1��������̽��(̽�ⲽ�����Ը����������)��ֱ��̽�⵽��ַ4������Ϊ�գ���23�������С�
*/
int find(DataType key)   //���в���
{
	int address = getHashAddress(key);
	//ֻҪhashTable[address].isNull==0����Ϊ�գ�   hashTable[address].data==key   address<M �����㣬��!(x)Ϊ0������ѭ��
	while (!(hashTable[address].isNull == 0 && hashTable[address].data == key&&address < M))
	{
		address++;
	}
	if (address == M)
	{
		address = -1;
	}
	return address;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int key[] = { 123, 456, 8, 7000, 1, 13, 11, 555, 426, 39, 393, 212, 564, 2, 99, 196 };
	int i;
	InitHashTable();
	for (i = 0; i < 15; i++)
	{
		insert(key[i]);
	}
	for (i = 0; i < 15; i++)
	{
		int address;
		address = find(key[i]);
		printf("%d %d\n", key[i], address);
	}
	scanf("%s", &key[1]);
	return 0;
}

