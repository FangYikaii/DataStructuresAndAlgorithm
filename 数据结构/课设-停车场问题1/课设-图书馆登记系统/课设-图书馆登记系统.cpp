// ����-ͼ��ݵǼ�ϵͳ.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*

��Ҫ��C��C++��̡�
��ͣ������һ����ͣ��n������������ͨ������ֻ��һ�����ſɹ�����������
������ͣ�����ڰ���������ʱ����Ⱥ�˳�������ɱ��������У����������϶ˣ����ȵ���ĵ�һ����ͣ����ͣ��������ˣ�,
��ͣ��������ͣ��n�������������������ֻ��������ı���ϵȺ�һ���г����ߣ������ڱ���ϵĵ�һ�������ɿ��룻
��ͣ������ĳ����Ҫ�뿪ʱ������֮�����ĳ����������˳�����Ϊ����·�������������������⣬���������ٰ�ԭ������복����
ÿ��ͣ���ڳ����ĳ������뿪ͣ����ʱ���밴��ͣ����ʱ�䳤�̽��ɷ��á���Ϊͣ�������ư�����Ҫ����й����ģ�����

������Ҫ��
��ջģ��ͣ�������Զ���ģ�⳵����ı�������մ��ն˶���������������н���ģ�����
ÿһ���������ݰ�������������������������ȥ����Ϣ���������պ����Լ��������ȥ��ʱ�̡�
��ÿһ���������ݽ��в�����������ϢΪ�����ǳ�����������������ͣ�����ڻ����ϵ�ͣ��λ�ã�
���ǳ�����ȥ�������������ͣ������ͣ����ʱ���Ӧ���ɵķ��ã��ڱ����ͣ����ʱ�䲻�շѣ���
ջ��˳��ṹʵ�֣�����������ṹʵ�֡�

*/

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX 10        //��������
#define price 0.05    //ÿ����ÿ�����ķ���

typedef struct time   //ʱ��ڵ㣺ʱ����
{
	int hour;
	int min;
}Time;

typedef struct node   //������Ϣ�ڵ㣺���ƺţ�ʱ���뿪��ʱ�䵽��
{
	char num[10];
	Time reach;
	Time leave;
}CarNode;

typedef struct NODE  //ģ�⳵վ�����Ŀ������top -----------------��ջ����
{
	CarNode *stack[MAX + 1];
	int top;
}SeqStackCar;

typedef struct car   //ģ������Ϣ������������һ����
{
	CarNode *data;
	struct car *next;
}QueueNode;

typedef struct Node    //ģ��ͨ��------------------------------��������
{
	QueueNode *head;
	QueueNode *rear;
}LinkQueueCar;


void InitStack(SeqStackCar *); //��ʼ��ջ����վ��
int InitQueue(LinkQueueCar *); //��ʼ�����
int arrival(SeqStackCar *, LinkQueueCar *);  //��������
void leave(SeqStackCar *, SeqStackCar *, LinkQueueCar *); //�����뿪
void list(SeqStackCar, LinkQueueCar);       //��ʾ�泵����Ϣ

int _tmain(int argc, _TCHAR* argv[])
{
	SeqStackCar Enter, Temp;     //��վ
	LinkQueueCar Wait;        //ͨ��
	int ch;
	InitStack(&Enter);     //��ʼ����վ
	InitStack(&Temp);      //��ʼ����·����ʱջ
	InitQueue(&Wait);     //��ʼ��ͨ��
	
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
				printf("\nPlease choose��1|2|3|4.");
			}
		}
		switch (ch)
		{
		case 1:
			//��������
			arrival(&Enter, &Wait);
			break;
		case 2:
			//�����뿪
			leave(&Enter, &Temp, &Wait);
			break;
		case 3:
			//�б��ӡ��Ϣ
			list(Enter, Wait);
			break;
		case 4:
			//�˳�������
			exit(0);
		default:
			break;
		}
	}
}

void InitStack(SeqStackCar *s)   //��ʼ��ջ
{
	int i;
	s->top = 0;
	for (i = 0; i < MAX; i++)
	{
		s->stack[i]=NULL;              //��ʼ��MAX��stack[i]
	}
}

int InitQueue(LinkQueueCar *Q)  //��ʼ�����
{
	Q->head = (QueueNode *)malloc(sizeof(QueueNode));   //��̬��̬�����ڴ�
	if (Q->head != NULL)
	{
		Q->head->next = NULL;
		Q->rear = Q->head;               //��==β
		return 1;
	}
	else return -1;
}

void print(CarNode *p)  //��ӡ��վ������Ϣ��p��ָ�룩
{
	int A1, A2, B1, B2;
	printf("\nplease input the depart time:/**:**/");
	scanf("%d:%d", &(p->leave.hour), &(p->leave.min));  //�����뿪��ʱ��
	printf("\nthe number of the car:");
	puts(p->num);
	printf("\nthe time the car arrive: %d:%d", p->reach.hour, p->reach.min);
	printf("the depart time: %d:%d", p->leave.hour, p->leave.min);
	A1 = p->reach.hour;
	A2 = p->reach.min;
	B1 = p->leave.hour;
	B2 = p->leave.min;
	printf("\nthe fee: %2.1fԪ", ((B1 - A1) * 60 + (B2 - A2))*price);
	free(p);          //�ͷ�ָ��
}

int arrival(SeqStackCar *Enter, LinkQueueCar *W)	//��������:ģ�⳵վ��������Ϣ���飬top��  ģ��ͨ���������Ϣ��,�����Ϣβ��
{
	CarNode *p;     //������Ϣ
	QueueNode *t;   //ͨ����Ϣ
	
	p = (CarNode *)malloc(sizeof(CarNode));       //�����ڴ�ռ�
	_flushall();   //������� 
	printf("\ninput the number of the car(������A1245):");
	gets(p->num);

	//����δ����������վ
	if (Enter->top < MAX)
	{
		Enter->top++;   //�������++
		printf("\nthe place of the car.", Enter->top);   //��ʾ���
		
		printf("\nthe time the car arrive:/**:/**/");    //���뵽��ʱ��
		scanf("%d:%d", &(p->reach.hour), &(p->reach.min));
		
		Enter->stack[Enter->top] = p;   //�ѳ�����Ϣ����ջ��
		return 1;
	}
	//�����Ѿ����ˣ���������
	else
	{
		printf("\n�ó����ڱ���ȴ���");
		t = (QueueNode *)malloc(sizeof(QueueNode));      //�����ڴ�ռ�t:��ͨ����Ϣ��
		t->data = p;   //�����Ϣ����ǰ������Ϣ--p������Ϣ
		t->next = NULL;  //�����Ϣ���¸������Ϣ--NULL
		
		W->rear->next = t;   //�����Ϣ--�¸������Ϣ--t
		W->rear = t;          //�����Ϣ
		return 1;
	}
}

void leave(SeqStackCar *Enter, SeqStackCar *Temp, LinkQueueCar *W)  //�����뿪 
{
	int i, room;
	CarNode *p, *t;  //������Ϣ
	QueueNode *q;    //ͨ����Ϣ
	//�жϳ������Ƿ��г�
	if (Enter->top > 0)  //�г�
	{
		while (1)   //�����뿪����Ϣ
		{
			printf("\n�����복�ڳ�����λ��/1--%d/:", Enter->top);
			scanf("%d", &room);        //�����뿪�ĳ���λ��
			if (room >= 1 && room <= Enter->top)  //����ʵ�����
				break;
		}
		//�����վ��top>����Index
		//�Ͱѳ�վ��top�Ƶ�temp�ĳ�վ
		while (Enter->top > room)       
		{
			Temp->top++;           
			Temp->stack[Temp->top] = Enter->stack[Enter->top];  //�ѳ�վtop�Ƶ�temp��վ
			Enter->stack[Enter->top] = NULL;             //��վtop��Ϊnull
			Enter->top--;      //��վtop--
		}
		p = Enter->stack[Enter->top];      //��p��Ϊ��վtopλ�ĳ�����Ϣ��Ҳ����Ҫ�뿪�ĳ�����Ϣ
		Enter->stack[Enter->top] = NULL;   //�ѳ�վtopλ�ĳ�����Ϣ��ΪNULL--ɾ��������Ϣ
		Enter->top--;                      //top--
		//��temp��վ�ĳ��Ƶ�ԭ���ĳ�վ
		while (Temp->top >= 1)
		{
			Enter->top++;    //top++
			Enter->stack[Enter->top] = Temp->stack[Temp->top];      //��temp��վ��top�Ƶ�ԭ���ĳ�վ
			Temp->stack[Temp->top] = NULL;     //�ѳ�վ��top��Ϊnull
			Temp->top--;        //top--
		}
		print(p);    //��ӡp����Ϣ
		
		//�ж�ͨ�����Ƿ��г�����վ�Ƿ�����
		//ͨ�����Ƿ��г�   (W->head != W->rear)   �� ��= β
		//Enter->top < MAX ��վ��û��
		//������վ
		if ((W->head != W->rear) && Enter->top < MAX)   //����ĳ������복��
		{
			q = W->head->next;       //q�ǳ�վ��head��nextָ��
			t = q->data;             //t-qָ��ָ��ġ���������Ϣ
			Enter->top++;            //��վtop++
			printf("\n�����%s�ų����복����%dλ��", t->num, Enter->top);      //�����ĺ���     �����λ��
			printf("\n���������ڵ�ʱ��/**:**/��");
			scanf("%d:%d", &(t->reach.hour), &(t->reach.min));                //ͨ������վ������ʱ�䣺�������
			W->head->next = q->next;                                          //��վ��head��nextָ�� == ָ��q��nextָ��
			//���qΪW��β����ͷ�� == β��
			if (q == W->rear)
			{
				//ͷ�� == β��
				W->rear = W->head;
			}
			//ͨ������ĳ������복վ
			Enter->stack[Enter->top] = t;
			free(q);
		}
		else
		{
			printf("\n�����û�г���\n");
		}
	}
	else
	{
		printf("\n�����û�г�.\n");
	}
}


void list1(SeqStackCar *S)        //�б���ʾ������Ϣ
{
	int i;
	//����г�
	if (S->top > 0)
	{
		printf("\n������");
		printf("\n λ�� ����ʱ�� ���ƺ�\n");
		//�ѳ������еĳ�����һ��
		for (i = 1; i <= S->top; i++)
		{
			printf("%d", i);     //����index
			printf("%d:%d ", S->stack[i]->reach.hour, S->stack[i]->reach.min);     //����ʱ��
			puts(S->stack[i]->num);    //���ƺ�
		}
	}
	else
	{
		printf("\n������û�г�");
	}

}

void list2(LinkQueueCar *W)    //�б���ʾ�����Ϣ
{
	QueueNode *p;
	//headָ��ĵ�һ��ָ��
	p = W->head->next;
	if (W->head != W->rear)        //�жϱ���Ƿ��г�
	{
		printf("\n�ȴ������ĺ���Ϊ��");
		//�������еĳ���
		while (p != NULL)
		{
			puts(p->data->num);
			p = p->next;       //p=p->next:����ı���  
		}
	}
	else
	{
		printf("\n�����û�г���");
	}
}


void list(SeqStackCar S, LinkQueueCar W)
{
	int flag, tag;
	flag = 1;
	while (flag)
	{
		printf("\n��ѡ�� 1|2|3��");
		printf("\n1.����\n2.���\n3.����\n");
		while (1)
		{
			scanf("%d", &tag);
			if (tag >= 1 && tag <= 3)
			{
				break;
			}
			else
			{
				printf("\n��ѡ�� 1|2|3��");
			}
		}
		switch (tag)
		{
		case 1:
			list1(&S);
			break;       //�б���ʾ������Ϣ
		case 2:
			list2(&W);
			break;      //�б���ʾ�����Ϣ
		case 3:
			flag = 0;
			break;
		default:
			break;
		}
	}
}