#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE 10

typedef struct
{
	int hour;
	int min;
}time;           //车的时间结构体


typedef struct
{
	int num;
	int position;
	time t;
	float money;
}Car;            //车辆信息


typedef struct
{
	Car elem[SIZE + 1];
	int top;
}Stack;               //车站堆栈


typedef struct Node
{
	Car data;
	struct Node *next;
}CQueueNode;          //便道信息


typedef struct
{
	CQueueNode *front;
	CQueueNode *rear;
}LinkQueue;         //过道堆栈


//过道初始化
void InitQueue(LinkQueue *Q)
{
	Q->front = (CQueueNode *)malloc(sizeof(CQueueNode));    //使malloc返回的指针转换为指向CQueueNode类型数据的指针
	if (Q->front != NULL)
	{
		Q->rear = Q->front;              //首部==尾部
		Q->front->next = NULL;           //初始化Q->front->next==NULL,下一个指针null
	}
}

//进入过道
int EnterQueue(LinkQueue *Q, Car *t)
{
	CQueueNode *NewNode;      //过道节点信息
	NewNode = (CQueueNode *)malloc(sizeof(CQueueNode));     //给过道节点分配内存
	if (NewNode != NULL)
	{
		NewNode->data.num = t->num;      //节点信息.data.车牌
		NewNode->data.t.hour = t->t.hour;  //节点信息.data.时间.hour
		NewNode->data.t.min = t->t.min;   //节点信息.data.时间.min
		NewNode->next = NULL;        //节点信息.next指针=空
		Q->rear->next = NewNode;   //过道信息.首部.next指针=节点信息
		Q->rear = NewNode;     //过道信息.首部=节点信息
		return 1;
	}
	else
	{
		return 0;
	}
}

//初始化车站
void InitStack(Stack *S)
{
	S->top = 0;      //top=0
}

//便道的车进入车站
void Push(Stack *S, Car *r)
{ 
	S->top++;    //车站top++
	S->elem[S->top].num = r->num;  //车站top数组值.车牌
	r->position = S->elem[S->top].position = S->top;    //车站top数组值.位置
	S->elem[S->top].t.hour = r->t.hour;      //车站top数组值.t.时
	S->elem[S->top].t.min = r->t.min;     //车站top数组值.t.分
}

//判断车库是否为空
int IsEmpty(Stack *S)
{
	return(S->top == 0 ? 1 : 0);
}

//判断车库是否为满
int IsFull(Stack *S)
{
	return(S->top == SIZE ? 1 : 0);
}

//车离开车库
//*n 是引用指针
int GetTop(Stack *S, Car *n)
{
	n->num = S->elem[S->top].num;      //n指针指向结构体.num
	n->position = S->elem[S->top].position; //n指针指向结构体.position
	n->t.hour = S->elem[S->top].t.hour;//n指针指向结构体.t.hour
	n->t.min = S->elem[S->top].t.min;//n指针指向结构体.t.min
	return 1;
}

//过道的车驶出
int DeleteQueue(LinkQueue *Q, Car *x)
{
	CQueueNode *p;
	//如果便道为空
	if (Q->front == Q->rear)
	{
		return 0;
	}
	//否则便道的车驶入车库
	p = Q->front->next;      //获取便道的信息p = Q->front->next;   
	Q->front->next = p->next;    //p开入车库，便道的车少一辆，Q->front->next的指向为p->next，也就是少了p
	//如果p驶入车库后过道就空了
	if (Q->rear == p)
		Q->rear = Q->front;  //过道置空
	
	//车辆信息
	x->num = p->data.num;
	x->t.hour = p->data.t.hour;
	x->t.hour = p->data.t.min;
	free(p);  //释放临时指针
	return 1;
}

//过道使出的车驶入车库
void In(Stack *S,LinkQueue *Q,Car *r)
{
	if (IsFull(S))
	{
		printf("车库已满，请等待！");
		EnterQueue(Q, r);        //过道的车驶出--（关键是r车辆信息，连接Stack车库信息和LinkQueue）
	}
	else
	{
		Push(S, r);
		printf("\n您现在所在的位置：%d", r->position);     //打印车的位置
	}
}

//Car弹出时候，h，m为进入的时间
void TaM(Car *r, int h, int m)
{
	
	if (m > r->t.min)
	{
		r->t.min += 60;
		r->t.hour -= 1;
	}

	h = r->t.hour - h;
	m = r->t.min - m;
	printf("\n停车 %d小时 %d 分钟\n", h, m);
	printf("每小时收费30元\n");
	h = h * 60;
	m = h + m;
	r->money = 0.5*m;
	printf("请支付金额%.2f元\n", r->money);
}

void Out(Stack *S, Stack *S0, Car *r, LinkQueue *Q)
{
	int tag = S->top;
	Car x;
	if (IsEmpty(S))
	{
		printf("车站没有车！");
	}
	else
	{
		//弹出到临时车站S0
		//当弹出汽车的车牌号不等于tag的车牌号且tag>0
		for (; r->num != S->elem[tag].num&&tag > 0; tag--)
		{
			Push(S0, &S->elem[tag]);
			S->top--;
		}
		//弹出所要弹的车辆
		if (r->num == S->elem[tag].num)
		{
			//计算价钱
			TaM(r, S->elem[tag].t.hour, S->elem[tag].t.min);
			S->top--;
			//临时车库的车驶入车库
			for (; S0->top > 0; S0->top--)
			{
				Push(S, &S0->elem[S0->top]);
			}
			//判断通道是否有车，如果有就驶入车库中
			if (S->top < SIZE&&Q->front != Q->rear)
			{
				DeleteQueue(Q, &x);
				Push(S, &x);
			}
		}
		//过道的车无需收车费
		else if (tag==0)
		{
			printf("未进入停车场应支付金额 0元");
			for (; S0->top > 0; S0->top--)
			{
				Push(S, &S0->elem[S0->top]);
			}
		}
	}
}

void print1(Stack *S)
{
	int tag;
	Car x;
	printf("停车场停车情况：\n");
	if (IsEmpty(S))
	{
		printf("无车！");
	}
	for (tag = S->top; S->top > 0; S->top--)
	{
		if (GetTop(S, &x))
		{
			printf("车牌号 %d，所在位置 %d，到达/离开时间 %d：%d\n", x.num, x.position, x.t.hour, x.t.min);
		}
	}
	S->top = tag;
}

void print2(LinkQueue *Q)
{
	CQueueNode *p;
	p = Q->front->next;
	for (; p != NULL; p = p->next)
	{
		printf("等待车牌号 %d，到达/离开时间%d:%d", p->data.num, p->data.t.hour, p->data.t.min);
	}
}

void print()
{
	printf("\n***********************************欢迎光临*************************************\n");
	printf("\n 请选择:\n");
	printf("\n 1 :到达");
	printf("\n 2 :离开");
	printf("\n 3 :搜索");
	printf("\n 4 :退出\n");
	printf("\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	int n, m, i = 1, j, flag = 0;
	Car c[SIZE];
	Stack S,S0;
	LinkQueue Q;
	InitStack(&S);
	InitStack(&S0);
	InitQueue(&Q);
	while (1)
	{
		print();
		scanf("%d", &m);
		switch (m)
		{
		case 1:
			printf("\n请输入车牌号:");
			scanf("%d", &c[i].num);
			printf("\n请输入到达/离开时间：");
			scanf("%d:%d", &c[i].t.hour, &c[i].t.min);
			In(&S, &Q, &c[i]);
			i++;
			break;
		case 2:
			printf("\n请输入车牌号：");
			scanf("%d", &n);
			for (j = 0; j < 10; j++)
			{
				if (n == c[j].num)
					break;
			}
			printf("\n请输入到达/离开时间：");
			scanf("%d:%d", &c[i].t.hour, &c[i].t.min);
			Out(&S, &S0, &c[j], &Q);
			break;
		case 3:
			print1(&S);    //输出车库中车的信息
			print2(&Q);    //输出过道上车的信息
			break;
		case 4:
			flag = 1;
			break;
		default:
			printf("\n输入错误，请输入1，2，3或4");
		}
		if (flag)
			break;
	}
	return 0;
}

