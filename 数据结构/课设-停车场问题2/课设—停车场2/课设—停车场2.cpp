#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE 10

typedef struct
{
	int hour;
	int min;
}time;           //����ʱ��ṹ��


typedef struct
{
	int num;
	int position;
	time t;
	float money;
}Car;            //������Ϣ


typedef struct
{
	Car elem[SIZE + 1];
	int top;
}Stack;               //��վ��ջ


typedef struct Node
{
	Car data;
	struct Node *next;
}CQueueNode;          //�����Ϣ


typedef struct
{
	CQueueNode *front;
	CQueueNode *rear;
}LinkQueue;         //������ջ


//������ʼ��
void InitQueue(LinkQueue *Q)
{
	Q->front = (CQueueNode *)malloc(sizeof(CQueueNode));    //ʹmalloc���ص�ָ��ת��Ϊָ��CQueueNode�������ݵ�ָ��
	if (Q->front != NULL)
	{
		Q->rear = Q->front;              //�ײ�==β��
		Q->front->next = NULL;           //��ʼ��Q->front->next==NULL,��һ��ָ��null
	}
}

//�������
int EnterQueue(LinkQueue *Q, Car *t)
{
	CQueueNode *NewNode;      //�����ڵ���Ϣ
	NewNode = (CQueueNode *)malloc(sizeof(CQueueNode));     //�������ڵ�����ڴ�
	if (NewNode != NULL)
	{
		NewNode->data.num = t->num;      //�ڵ���Ϣ.data.����
		NewNode->data.t.hour = t->t.hour;  //�ڵ���Ϣ.data.ʱ��.hour
		NewNode->data.t.min = t->t.min;   //�ڵ���Ϣ.data.ʱ��.min
		NewNode->next = NULL;        //�ڵ���Ϣ.nextָ��=��
		Q->rear->next = NewNode;   //������Ϣ.�ײ�.nextָ��=�ڵ���Ϣ
		Q->rear = NewNode;     //������Ϣ.�ײ�=�ڵ���Ϣ
		return 1;
	}
	else
	{
		return 0;
	}
}

//��ʼ����վ
void InitStack(Stack *S)
{
	S->top = 0;      //top=0
}

//����ĳ����복վ
void Push(Stack *S, Car *r)
{ 
	S->top++;    //��վtop++
	S->elem[S->top].num = r->num;  //��վtop����ֵ.����
	r->position = S->elem[S->top].position = S->top;    //��վtop����ֵ.λ��
	S->elem[S->top].t.hour = r->t.hour;      //��վtop����ֵ.t.ʱ
	S->elem[S->top].t.min = r->t.min;     //��վtop����ֵ.t.��
}

//�жϳ����Ƿ�Ϊ��
int IsEmpty(Stack *S)
{
	return(S->top == 0 ? 1 : 0);
}

//�жϳ����Ƿ�Ϊ��
int IsFull(Stack *S)
{
	return(S->top == SIZE ? 1 : 0);
}

//���뿪����
//*n ������ָ��
int GetTop(Stack *S, Car *n)
{
	n->num = S->elem[S->top].num;      //nָ��ָ��ṹ��.num
	n->position = S->elem[S->top].position; //nָ��ָ��ṹ��.position
	n->t.hour = S->elem[S->top].t.hour;//nָ��ָ��ṹ��.t.hour
	n->t.min = S->elem[S->top].t.min;//nָ��ָ��ṹ��.t.min
	return 1;
}

//�����ĳ�ʻ��
int DeleteQueue(LinkQueue *Q, Car *x)
{
	CQueueNode *p;
	//������Ϊ��
	if (Q->front == Q->rear)
	{
		return 0;
	}
	//�������ĳ�ʻ�복��
	p = Q->front->next;      //��ȡ�������Ϣp = Q->front->next;   
	Q->front->next = p->next;    //p���복�⣬����ĳ���һ����Q->front->next��ָ��Ϊp->next��Ҳ��������p
	//���pʻ�복�������Ϳ���
	if (Q->rear == p)
		Q->rear = Q->front;  //�����ÿ�
	
	//������Ϣ
	x->num = p->data.num;
	x->t.hour = p->data.t.hour;
	x->t.hour = p->data.t.min;
	free(p);  //�ͷ���ʱָ��
	return 1;
}

//����ʹ���ĳ�ʻ�복��
void In(Stack *S,LinkQueue *Q,Car *r)
{
	if (IsFull(S))
	{
		printf("������������ȴ���");
		EnterQueue(Q, r);        //�����ĳ�ʻ��--���ؼ���r������Ϣ������Stack������Ϣ��LinkQueue��
	}
	else
	{
		Push(S, r);
		printf("\n���������ڵ�λ�ã�%d", r->position);     //��ӡ����λ��
	}
}

//Car����ʱ��h��mΪ�����ʱ��
void TaM(Car *r, int h, int m)
{
	
	if (m > r->t.min)
	{
		r->t.min += 60;
		r->t.hour -= 1;
	}

	h = r->t.hour - h;
	m = r->t.min - m;
	printf("\nͣ�� %dСʱ %d ����\n", h, m);
	printf("ÿСʱ�շ�30Ԫ\n");
	h = h * 60;
	m = h + m;
	r->money = 0.5*m;
	printf("��֧�����%.2fԪ\n", r->money);
}

void Out(Stack *S, Stack *S0, Car *r, LinkQueue *Q)
{
	int tag = S->top;
	Car x;
	if (IsEmpty(S))
	{
		printf("��վû�г���");
	}
	else
	{
		//��������ʱ��վS0
		//�����������ĳ��ƺŲ�����tag�ĳ��ƺ���tag>0
		for (; r->num != S->elem[tag].num&&tag > 0; tag--)
		{
			Push(S0, &S->elem[tag]);
			S->top--;
		}
		//������Ҫ���ĳ���
		if (r->num == S->elem[tag].num)
		{
			//�����Ǯ
			TaM(r, S->elem[tag].t.hour, S->elem[tag].t.min);
			S->top--;
			//��ʱ����ĳ�ʻ�복��
			for (; S0->top > 0; S0->top--)
			{
				Push(S, &S0->elem[S0->top]);
			}
			//�ж�ͨ���Ƿ��г�������о�ʻ�복����
			if (S->top < SIZE&&Q->front != Q->rear)
			{
				DeleteQueue(Q, &x);
				Push(S, &x);
			}
		}
		//�����ĳ������ճ���
		else if (tag==0)
		{
			printf("δ����ͣ����Ӧ֧����� 0Ԫ");
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
	printf("ͣ����ͣ�������\n");
	if (IsEmpty(S))
	{
		printf("�޳���");
	}
	for (tag = S->top; S->top > 0; S->top--)
	{
		if (GetTop(S, &x))
		{
			printf("���ƺ� %d������λ�� %d������/�뿪ʱ�� %d��%d\n", x.num, x.position, x.t.hour, x.t.min);
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
		printf("�ȴ����ƺ� %d������/�뿪ʱ��%d:%d", p->data.num, p->data.t.hour, p->data.t.min);
	}
}

void print()
{
	printf("\n***********************************��ӭ����*************************************\n");
	printf("\n ��ѡ��:\n");
	printf("\n 1 :����");
	printf("\n 2 :�뿪");
	printf("\n 3 :����");
	printf("\n 4 :�˳�\n");
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
			printf("\n�����복�ƺ�:");
			scanf("%d", &c[i].num);
			printf("\n�����뵽��/�뿪ʱ�䣺");
			scanf("%d:%d", &c[i].t.hour, &c[i].t.min);
			In(&S, &Q, &c[i]);
			i++;
			break;
		case 2:
			printf("\n�����복�ƺţ�");
			scanf("%d", &n);
			for (j = 0; j < 10; j++)
			{
				if (n == c[j].num)
					break;
			}
			printf("\n�����뵽��/�뿪ʱ�䣺");
			scanf("%d:%d", &c[i].t.hour, &c[i].t.min);
			Out(&S, &S0, &c[j], &Q);
			break;
		case 3:
			print1(&S);    //��������г�����Ϣ
			print2(&Q);    //��������ϳ�����Ϣ
			break;
		case 4:
			flag = 1;
			break;
		default:
			printf("\n�������������1��2��3��4");
		}
		if (flag)
			break;
	}
	return 0;
}

