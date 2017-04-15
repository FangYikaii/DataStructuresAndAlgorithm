// 哈希表-练习1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define DataType int
#define M 30

/*
HashTable[address].data
address:getHashAddress(key) 或者 getHashAddress(key)+1
data:key
*/
typedef struct HashNode
{
	DataType data;     //存储值
	int isNull;        //标志该位置是否已被填充
}HashTable;

HashTable hashTable[M];

void InitHashTable()
{
	int i;
	for (i = 0; i < M; i++)
	{
		hashTable[i].isNull = 1;   //初始状态为空
	}
}

int getHashAddress(DataType key)     //Hash函数
{
	return key % 29;
}

int insert(DataType key)                   //向hash表中插入元素
{
	int address = getHashAddress(key);    //插入hash表的index
	if (hashTable[address].isNull == 1)    //没有发生冲突
	{
		hashTable[address].data = key;      //key值
		hashTable[address].isNull = 0;      //初始状态不为空 
	}
	else                                  //当发生冲突的时候,插入到address+1位
	{
		while (hashTable[address].isNull == 0 && address < M)   //初始化状态不为空，且地址不为M
		{
			address++;        //采用线性探测法，不长为1
		}
		if (address == M)     //Hash表发生溢出
		{
			return -1;
		}
		hashTable[address].data = key;    //key值
		hashTable[address].isNull = 0;   //初始状态不为空
	}
	return 0;
}

/*
　1)开放定址法
 即当一个关键字和另一个关键字发生冲突时，使用某种探测技术在Hash表中形成一个探测序列，然后沿着这个探测序列依次查找下去，当碰到一个空的单元时，则插入其中。
 比较常用的探测方法有线性探测法，比如有一组关键字{12，13，25，23，38，34，6，84，91}，Hash表长为14，Hash函数为address(key)=key%11，
 当插入12，13，25时可以直接插入，而当插入23时，地址1被占用了，因此沿着地址1依次往下探测(探测步长可以根据情况而定)，直到探测到地址4，发现为空，则将23插入其中。
*/
int find(DataType key)   //进行查找
{
	int address = getHashAddress(key);
	//只要hashTable[address].isNull==0（不为空）   hashTable[address].data==key   address<M 都满足，则!(x)为0，跳出循环
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

