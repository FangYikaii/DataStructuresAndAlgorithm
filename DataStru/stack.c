#include <stdio.h>  
#include "stdlib.h"
#include <malloc.h>  
#include <windows.h>

#define random_int(x)        (rand() % x)                          //整型随机数
#define random_double(x)      (rand()/(double)(RAND_MAX/x))        //双精度型随机数
#define MAX_LENGTH           100                                   //栈最大长度
#define INCREMENT_LENGTH     10                                    //栈增加的长度
#define TRUE                 1
#define FALSE                0


//数据域
typedef struct Item
{
	int DigitalChannelData[2];            //数字量
	double AnalogChannelData[2];          //模拟量
}Item;

typedef struct Stack
{
	Item* pbase;
	Item* ptop;
	int stacksize;
}SqStack;

Item initItem(Item item);               //初始化一个Item结构
int initStack(SqStack* ps);             //构造一个空栈
int destoryStack(SqStack* ps);          //销毁栈
int clearStack(SqStack* ps);            //清空栈
int isStackEmpty(SqStack* ps);          //判断栈是否为空
int getStackLength(SqStack* ps);        //返回栈的长度
int getTop(SqStack* ps, Item* pitem);   //返回栈顶元素
int push(SqStack* ps, Item item);       //入栈
int pop(SqStack* ps, Item* pitem);      //出栈
int traverseStack(SqStack ps);         //遍历栈


void main()
{ 
	SqStack sq;                        //创建栈指针
	Item item = { 0, 0, 0, 0 };        //用于保存栈元素
	srand((unsigned)time(NULL));
	initStack(&sq);                    //初始化栈
	while (1)
	{
		printf("(1)入栈：\n");
		for (int i = 0; i < 10; i++)
		{
			item = initItem(item);
			push(&sq, item);            //入栈
		}
		traverseStack(sq);             //遍历
		Sleep(3000);

		printf("(2)出栈：\n");
		while (!isStackEmpty(&sq))     //如果为空，跳出出栈
		{
			if (pop(&sq, &item))
			{
				printf("出栈：%d %d %6.2f %6.2f\n", item.DigitalChannelData[0], item.DigitalChannelData[1], item.AnalogChannelData[0], item.AnalogChannelData[1]);
			}
		}
		Sleep(3000);

		printf("(3)清空栈区，此刻栈区：\n");  //遍历清空后的栈
		traverseStack(sq);
		Sleep(3000);
	}

}


/*
参数
Item:
返回值
Item：

该函数用于初始化一个Item
*/
Item initItem(Item item)
{
	item.DigitalChannelData[0] = random_int(10);
	item.DigitalChannelData[1] = random_int(10);
	item.AnalogChannelData[0] = random_double(100);
	item.AnalogChannelData[1] = random_double(1000);
	return item;
}

/*
输入：
ps:输入栈结构的指针

构造一个空栈
*/
int initStack(SqStack* ps)
{	
	//创建一个节点，让ptop指向它
	ps->ptop = (Item*)malloc(sizeof(Item));
	if (ps->ptop != NULL)
	{
		//将pbase也指向节点
		ps->pbase = ps->ptop;
		//设置栈最大长度
		ps->stacksize = MAX_LENGTH;
		return TRUE;
	}
	else
	{
		printf("内存分配失败！栈初始化失败！");
		return FALSE;
	}
}

/*
输入：
ps:输入栈结构的指针

销毁栈
*/
int destoryStack(SqStack* ps)
{
	free(ps->pbase);          //释放内存
	ps->pbase = NULL;         //置NULL
	ps->ptop = NULL;
	ps->stacksize = 0;
	return TRUE;
}

/*
输入：
ps:输入栈结构的指针

把栈置空
*/
int clearStack(SqStack* ps)
{
	ps->ptop = ps->pbase;
	return TRUE;
}

/*
输入：
ps:输入栈结构的指针

判断栈是否为空
*/
int isStackEmpty(SqStack* ps)
{
	if (ps->ptop == ps->pbase)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
输入：
ps:输入栈结构的指针

返回栈的元素个数，也就是栈的长度
*/
int getStackLength(SqStack* ps)
{
	return ps->ptop - ps->pbase;
}

/*
输入：
ps:输入栈结构的指针
pitem：输入返回栈顶元素的指针

返回栈顶元素
*/
int getTop(SqStack* ps, Item* pitem)
{
	if (ps->ptop > ps->pbase)
	{
		*pitem = *(ps->ptop - 1);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
输入：
ps:输入栈结构的指针
item：插入栈的元素

入栈
*/
int push(SqStack* ps, Item item)
{
	//如果超出了栈的大小，则重新分配栈的内存
	if (ps->ptop - ps->pbase >= ps->stacksize)
	{
		//realloc：动态内存调整
		//指针名=（数据类型*）realloc（要改变内存大小的指针名，新的大小）
		ps->pbase = (Item*)realloc(ps->pbase, (ps->stacksize + INCREMENT_LENGTH)*sizeof(Item));
		if (ps->pbase == NULL)
		{
			printf("内存分配失败！栈拓展失败！");
			return FALSE;
		}
		else
		{
			ps->ptop = ps->pbase + ps->stacksize;
			ps->stacksize += INCREMENT_LENGTH;
		}
	}
	*(ps->ptop)++ = item;    //（1）插入item，（2）ps->ptop+1。---也就是ptop现在没有指向任何的item
	return TRUE;
}

/*
ps：输入栈结构的指针
pitem:出栈元素

出栈
*/
int pop(SqStack* ps, Item* pitem)
{
	if (ps->ptop == ps->pbase)
	{
		printf("栈为空！出栈失败！\n");
		return FALSE;
	}
	else
	{
		*pitem = *(--ps->ptop);  //(1)ps->ptop-1;(2)删除item。---也就是ptop刚开始没有指向任何item，先减一，再取出item
		return TRUE;
	}
}

/*
ps:输入栈结构的指针

遍历栈
*/
int traverseStack(SqStack ps)
{
	printf("从栈顶遍历\n");
	while (ps.ptop != ps.pbase)            //栈不为空
	{
		ps.ptop--;
		Item* pitem = ps.ptop;
		printf("%d %d %6.2f %6.2f\n", pitem->DigitalChannelData[0], pitem->DigitalChannelData[1], pitem->AnalogChannelData[0], pitem->AnalogChannelData[1]);
	}
	return TRUE;
}
