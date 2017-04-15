#include "stdafx.h"
#include <stdio.h>
#include <string.h>

#define MAXLEN 100        //定义顺序表的最大长度

typedef struct
{
	char key[10];        //节点关键字
	char name[20];
	int age;
}DATA;                  //定义节点类型


//从下标1开始记录节点
typedef struct
{
	DATA ListData[MAXLEN + 1];      //保存顺序表的结构数组,定义了101个数据长度
	int ListLen;                    //顺序表已存节点的数量
}SLType;             //定义顺序表结构


void SLInit(SLType* SL)  //初始化顺序表，如果原来的顺序表已经有了数据，也会被覆盖，不影响操作
{
	SL->ListLen = 0;
}

int SLLength(SLType* SL)
{
	return (SL->ListLen);     //返回顺序表的元素数量
}

int SLInsert(SLType* SL, int n, DATA data)    //插入元素
{
	int i;
	//如果顺序表节点数量已经超过最大的数量
	if (SL->ListLen >= MAXLEN)
	{
		printf("顺序表已满，不能插入节点！\n");
		return 0;
	}
	//插入节点序号不正确
	if (n<1 || n>SL->ListLen - 1)
	{
		printf("插入元素序号错误，不能插入元素！\n");
		return 0;
	}
	//将顺序表的数据向后移动
	for (i = SL->ListLen; i >= n; i--)
	{
		SL->ListData[i + 1] = SL->ListData[i];
	}
	//插入节点
	SL->ListData[n] = data;
	//顺序表节点数量+1
	SL->ListLen++;
	return 1;   //成功插入，返回1
}


int SLAdd(SLType* SL, DATA data)   //追加节点
{
	if (SL->ListLen >= MAXLEN)
	{
		printf("顺序表已满，不能再添加节点了！\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}

int SLDelete(SLType* SL, int n)  //删除节点
{
	int i;
	if (n<1 || n>SL->ListLen + 1)
	{
		printf("删除节点序号错误，不能删除节点！");
		return 0;   //删除不成功，返回0
	}
	//将顺序表中的数据向前移动，覆盖
	for (i = n; i < SL->ListLen; i++)
	{
		SL->ListData[i] = SL->ListData[i + 1];
	}
	SL->ListLen--;      //顺序表元素减一
	return 1;
}

DATA* SLFindByNumber(SLType* SL, int n)  //根据序号返回数据元素
{
	if (n<1 || n>SL->ListLen + 1)
	{
		printf("节点序号错误，不能返回节点！\n");
		return NULL;
	}
	return &(SL->ListData[n]);    //返回数组对应元素的地址
}

int SLFindByCont(SLType* SL, char* key)  //按关键字节点查询数据
{
	int i;
	for (i = 1; i <= SL->ListLen; i++)
	{
		if (strcmp(SL->ListData[i].key, key) == 0)
		{
			return i;
		}
	}
	return 0;
}

int SLAll(SLType* SL)   //显示所有节点
{
	int i;
	for (i = 1; i <= SL->ListLen; i++)
	{
		printf("(%s,%s,%d)\n", SL->ListData[i].key, SL->ListData[i].name, SL->ListData[i].age);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	SLType SL;    //定义顺序表变量
	DATA data;    //定义节点保存数据类型变量
	DATA *pdata;  //定义节点保存指针变量
	char  key[10];

	printf("顺序表操作演示！\n");
	SLInit(&SL);    //初始化顺序表，顺序表变量的地址作为参数传递
	printf("初始化顺序表完成！\n");
	do
	{
		printf("输入添加的节点（学号 姓名 年龄）：");
		fflush(stdin);  //清空输入缓存区
		//_flushall();  //清空所有缓存区
		scanf("%s%s%d", &data.key, &data.name, &data.age);
		if (data.age)   //若年龄不为0
		{
			if (!SLAdd(&SL, data))    //若添加节点失败
			{
				break;
			}
		}
		else            //若年龄为0
		{
			break;      //退出死循环
		}
	} while (1);
	printf("\n顺序表的节点顺序为：\n");
	SLAll(&SL);

	fflush(stdin);
	printf("\n要取出节点的序号：");
	scanf("%d", &i);
	//按照序号查找节点：返回的是Data结构体的指针，输入参数是顺序表变量的地址
	pdata = SLFindByNumber(&SL, i);
	//返回值不为空
	if (pdata)
	{
		printf("第%d个节点尾：（%s%s%d）\n", i, pdata->key, pdata->name, pdata->age);
	}
	scanf("%d", &i);
	return 0;
}



