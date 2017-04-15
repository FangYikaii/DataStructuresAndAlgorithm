// 课设-图书馆登记系统.cpp : 定义控制台应用程序的入口点。
//
/*

【要求C或C++编程】
设停车场是一个可停放n辆汽车的狭长通道，且只有一个大门可供汽车进出。
汽车在停车场内按车辆到达时间的先后顺序，依次由北向南排列（大门在最南端，最先到达的第一辆车停放在停车场的最北端）,
若停车场内已停满n辆汽车，则后来的汽车只能在门外的便道上等候，一旦有车开走，则排在便道上的第一辆车即可开入；
当停车场内某辆车要离开时，在它之后进入的车辆必须先退出车场为它让路，待该辆车开出大门外，其他车辆再按原次序进入车场，
每辆停放在车场的车在它离开停车场时必须按它停留的时间长短交纳费用。试为停车场编制按上述要求进行管理的模拟程序。

【基本要求】
以栈模拟停车场，以队列模拟车场外的便道，按照从终端读入的输入数据序列进行模拟管理。
每一组输入数据包括三个数据项：汽车“到达”或“离去”信息、汽车牌照号码以及到达或离去的时刻。
对每一组输入数据进行操作后的输出信息为：若是车辆到达，则输出汽车在停车场内或便道上的停车位置；
若是车辆离去，则输出汽车在停车场内停留的时间和应交纳的费用（在便道上停留的时间不收费）。
栈以顺序结构实现，队列以链表结构实现。

*/

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX 10        //车库容量
#define price 0.05    //每分钟每辆车的费用

typedef struct time   //时间节点：时，分
{
	int hour;
	int min;
}Time;

typedef struct node   //车辆信息节点：车牌号，时间离开，时间到达
{
	char num[10];
	Time reach;
	Time leave;
}CarNode;

typedef struct NODE  //模拟车站：车的库存数，top -----------------【栈！】
{
	CarNode *stack[MAX + 1];
	int top;
}SeqStackCar;

typedef struct car   //模拟便道信息：本辆车，下一辆车
{
	CarNode *data;
	struct car *next;
}QueueNode;

typedef struct Node    //模拟通道------------------------------【链表！】
{
	QueueNode *head;
	QueueNode *rear;
}LinkQueueCar;


void InitStack(SeqStackCar *); //初始化栈（车站）
int InitQueue(LinkQueueCar *); //初始化便道
int arrival(SeqStackCar *, LinkQueueCar *);  //车辆到达
void leave(SeqStackCar *, SeqStackCar *, LinkQueueCar *); //车辆离开
void list(SeqStackCar, LinkQueueCar);       //显示存车的信息

int _tmain(int argc, _TCHAR* argv[])
{
	SeqStackCar Enter, Temp;     //车站
	LinkQueueCar Wait;        //通道
	int ch;
	InitStack(&Enter);     //初始化车站
	InitStack(&Temp);      //初始化让路的临时栈
	InitQueue(&Wait);     //初始化通道
	
	while (1)
	{
		printf("\n                1.The car arrive\n");
		printf("                2.The car leave\n");
		printf("                3.The schedule\n");
		printf("                4.Exit\n");
		while (1)
		{
			scanf("%d", &ch);
			if (ch >= 1 && ch < 4)
			{
				break;
			}
			else
			{
				printf("\nPlease choose：1|2|3|4.");
			}
		}
		switch (ch)
		{
		case 1:
			//车辆到达
			arrival(&Enter, &Wait);
			break;
		case 2:
			//车辆离开
			leave(&Enter, &Temp, &Wait);
			break;
		case 3:
			//列表打印信息
			list(Enter, Wait);
			break;
		case 4:
			//退出主程序
			exit(0);
		default:
			break;
		}
	}
}

void InitStack(SeqStackCar *s)   //初始化栈
{
	int i;
	s->top = 0;
	for (i = 0; i < MAX; i++)
	{
		s->stack[i]=NULL;              //初始化MAX个stack[i]
	}
}

int InitQueue(LinkQueueCar *Q)  //初始化便道
{
	Q->head = (QueueNode *)malloc(sizeof(QueueNode));   //动态动态分配内存
	if (Q->head != NULL)
	{
		Q->head->next = NULL;
		Q->rear = Q->head;               //首==尾
		return 1;
	}
	else return -1;
}

void print(CarNode *p)  //打印出站车的信息（p是指针）
{
	int A1, A2, B1, B2;
	printf("\nplease input the depart time:/**:**/");
	scanf("%d:%d", &(p->leave.hour), &(p->leave.min));  //输入离开的时间
	printf("\nthe number of the car:");
	puts(p->num);
	printf("\nthe time the car arrive: %d:%d", p->reach.hour, p->reach.min);
	printf("the depart time: %d:%d", p->leave.hour, p->leave.min);
	A1 = p->reach.hour;
	A2 = p->reach.min;
	B1 = p->leave.hour;
	B2 = p->leave.min;
	printf("\nthe fee: %2.1f元", ((B1 - A1) * 60 + (B2 - A2))*price);
	free(p);          //释放指针
}

int arrival(SeqStackCar *Enter, LinkQueueCar *W)	//车辆到达:模拟车站（车辆信息数组，top）  模拟通道（便道信息首,便道信息尾）
{
	CarNode *p;     //车辆信息
	QueueNode *t;   //通道信息
	
	p = (CarNode *)malloc(sizeof(CarNode));       //分配内存空间
	_flushall();   //清除缓冲 
	printf("\ninput the number of the car(例：陕A1245):");
	gets(p->num);

	//车辆未满，车进车站
	if (Enter->top < MAX)
	{
		Enter->top++;   //车辆编号++
		printf("\nthe place of the car.", Enter->top);   //显示编号
		
		printf("\nthe time the car arrive:/**:/**/");    //输入到达时间
		scanf("%d:%d", &(p->reach.hour), &(p->reach.min));
		
		Enter->stack[Enter->top] = p;   //把车辆信息存入栈中
		return 1;
	}
	//车场已经满了，车进入便道
	else
	{
		printf("\n该车须在便道等待！");
		t = (QueueNode *)malloc(sizeof(QueueNode));      //分配内存空间t:（通道信息）
		t->data = p;   //便道信息：当前车辆信息--p车辆信息
		t->next = NULL;  //便道信息：下个便道信息--NULL
		
		W->rear->next = t;   //便道信息--下个便道信息--t
		W->rear = t;          //便道信息
		return 1;
	}
}

void leave(SeqStackCar *Enter, SeqStackCar *Temp, LinkQueueCar *W)  //车辆离开 
{
	int i, room;
	CarNode *p, *t;  //车辆信息
	QueueNode *q;    //通道信息
	//判断车场内是否有车
	if (Enter->top > 0)  //有车
	{
		while (1)   //输入离开的信息
		{
			printf("\n请输入车在车场的位置/1--%d/:", Enter->top);
			scanf("%d", &room);        //输入离开的车的位置
			if (room >= 1 && room <= Enter->top)  //符合实际情况
				break;
		}
		//如果车站的top>车辆Index
		//就把车站的top移到temp的车站
		while (Enter->top > room)       
		{
			Temp->top++;           
			Temp->stack[Temp->top] = Enter->stack[Enter->top];  //把车站top移到temp车站
			Enter->stack[Enter->top] = NULL;             //车站top置为null
			Enter->top--;      //车站top--
		}
		p = Enter->stack[Enter->top];      //把p置为车站top位的车辆信息，也就是要离开的车辆信息
		Enter->stack[Enter->top] = NULL;   //把车站top位的车辆信息置为NULL--删除车辆信息
		Enter->top--;                      //top--
		//把temp车站的车移到原来的车站
		while (Temp->top >= 1)
		{
			Enter->top++;    //top++
			Enter->stack[Enter->top] = Temp->stack[Temp->top];      //把temp车站的top移到原来的车站
			Temp->stack[Temp->top] = NULL;     //把车站的top置为null
			Temp->top--;        //top--
		}
		print(p);    //打印p的信息
		
		//判断通道上是否有车及车站是否已满
		//通道上是否有车   (W->head != W->rear)   首 ！= 尾
		//Enter->top < MAX 车站还没满
		//车辆进站
		if ((W->head != W->rear) && Enter->top < MAX)   //便道的车辆进入车场
		{
			q = W->head->next;       //q是车站的head的next指针
			t = q->data;             //t-q指针指向的——车辆信息
			Enter->top++;            //车站top++
			printf("\n便道的%s号车进入车场第%d位置", t->num, Enter->top);      //车辆的号码     进入的位置
			printf("\n请输入现在的时间/**:**/：");
			scanf("%d:%d", &(t->reach.hour), &(t->reach.min));                //通道车进站：到达时间：到达分钟
			W->head->next = q->next;                                          //车站的head的next指针 == 指向q的next指针
			//如果q为W的尾部：头部 == 尾部
			if (q == W->rear)
			{
				//头部 == 尾部
				W->rear = W->head;
			}
			//通道外面的车辆进入车站
			Enter->stack[Enter->top] = t;
			free(q);
		}
		else
		{
			printf("\n便道里没有车。\n");
		}
	}
	else
	{
		printf("\n便道里没有车.\n");
	}
}


void list1(SeqStackCar *S)        //列表显示车场信息
{
	int i;
	//如果有车
	if (S->top > 0)
	{
		printf("\n车场：");
		printf("\n 位置 到达时间 车牌号\n");
		//把车辆所有的车遍历一下
		for (i = 1; i <= S->top; i++)
		{
			printf("%d", i);     //车辆index
			printf("%d:%d ", S->stack[i]->reach.hour, S->stack[i]->reach.min);     //到达时间
			puts(S->stack[i]->num);    //车牌号
		}
	}
	else
	{
		printf("\n车场里没有车");
	}

}

void list2(LinkQueueCar *W)    //列表显示便道信息
{
	QueueNode *p;
	//head指向的第一个指针
	p = W->head->next;
	if (W->head != W->rear)        //判断便道是否有车
	{
		printf("\n等待车辆的号码为：");
		//遍历所有的车辆
		while (p != NULL)
		{
			puts(p->data->num);
			p = p->next;       //p=p->next:链表的遍历  
		}
	}
	else
	{
		printf("\n便道里没有车。");
	}
}


void list(SeqStackCar S, LinkQueueCar W)
{
	int flag, tag;
	flag = 1;
	while (flag)
	{
		printf("\n请选择 1|2|3：");
		printf("\n1.车场\n2.便道\n3.返回\n");
		while (1)
		{
			scanf("%d", &tag);
			if (tag >= 1 && tag <= 3)
			{
				break;
			}
			else
			{
				printf("\n请选择 1|2|3：");
			}
		}
		switch (tag)
		{
		case 1:
			list1(&S);
			break;       //列表显示车场信息
		case 2:
			list2(&W);
			break;      //列表显示便道信息
		case 3:
			flag = 0;
			break;
		default:
			break;
		}
	}
}