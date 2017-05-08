#include <stdio.h>  
#include "stdlib.h"
#include <malloc.h>  
#include <windows.h>

#define random_int(x)        (rand() % x)                          //���������
#define random_double(x)      (rand()/(double)(RAND_MAX/x))        //˫�����������
#define MAX_LENGTH           100                                   //ջ��󳤶�
#define INCREMENT_LENGTH     10                                    //ջ���ӵĳ���
#define TRUE                 1
#define FALSE                0


//������
typedef struct Item
{
	int DigitalChannelData[2];            //������
	double AnalogChannelData[2];          //ģ����
}Item;

typedef struct Stack
{
	Item* pbase;
	Item* ptop;
	int stacksize;
}SqStack;

Item initItem(Item item);               //��ʼ��һ��Item�ṹ
int initStack(SqStack* ps);             //����һ����ջ
int destoryStack(SqStack* ps);          //����ջ
int clearStack(SqStack* ps);            //���ջ
int isStackEmpty(SqStack* ps);          //�ж�ջ�Ƿ�Ϊ��
int getStackLength(SqStack* ps);        //����ջ�ĳ���
int getTop(SqStack* ps, Item* pitem);   //����ջ��Ԫ��
int push(SqStack* ps, Item item);       //��ջ
int pop(SqStack* ps, Item* pitem);      //��ջ
int traverseStack(SqStack ps);         //����ջ


void main()
{ 
	SqStack sq;                        //����ջָ��
	Item item = { 0, 0, 0, 0 };        //���ڱ���ջԪ��
	srand((unsigned)time(NULL));
	initStack(&sq);                    //��ʼ��ջ
	while (1)
	{
		printf("(1)��ջ��\n");
		for (int i = 0; i < 10; i++)
		{
			item = initItem(item);
			push(&sq, item);            //��ջ
		}
		traverseStack(sq);             //����
		Sleep(3000);

		printf("(2)��ջ��\n");
		while (!isStackEmpty(&sq))     //���Ϊ�գ�������ջ
		{
			if (pop(&sq, &item))
			{
				printf("��ջ��%d %d %6.2f %6.2f\n", item.DigitalChannelData[0], item.DigitalChannelData[1], item.AnalogChannelData[0], item.AnalogChannelData[1]);
			}
		}
		Sleep(3000);

		printf("(3)���ջ�����˿�ջ����\n");  //������պ��ջ
		traverseStack(sq);
		Sleep(3000);
	}

}


/*
����
Item:
����ֵ
Item��

�ú������ڳ�ʼ��һ��Item
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
���룺
ps:����ջ�ṹ��ָ��

����һ����ջ
*/
int initStack(SqStack* ps)
{	
	//����һ���ڵ㣬��ptopָ����
	ps->ptop = (Item*)malloc(sizeof(Item));
	if (ps->ptop != NULL)
	{
		//��pbaseҲָ��ڵ�
		ps->pbase = ps->ptop;
		//����ջ��󳤶�
		ps->stacksize = MAX_LENGTH;
		return TRUE;
	}
	else
	{
		printf("�ڴ����ʧ�ܣ�ջ��ʼ��ʧ�ܣ�");
		return FALSE;
	}
}

/*
���룺
ps:����ջ�ṹ��ָ��

����ջ
*/
int destoryStack(SqStack* ps)
{
	free(ps->pbase);          //�ͷ��ڴ�
	ps->pbase = NULL;         //��NULL
	ps->ptop = NULL;
	ps->stacksize = 0;
	return TRUE;
}

/*
���룺
ps:����ջ�ṹ��ָ��

��ջ�ÿ�
*/
int clearStack(SqStack* ps)
{
	ps->ptop = ps->pbase;
	return TRUE;
}

/*
���룺
ps:����ջ�ṹ��ָ��

�ж�ջ�Ƿ�Ϊ��
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
���룺
ps:����ջ�ṹ��ָ��

����ջ��Ԫ�ظ�����Ҳ����ջ�ĳ���
*/
int getStackLength(SqStack* ps)
{
	return ps->ptop - ps->pbase;
}

/*
���룺
ps:����ջ�ṹ��ָ��
pitem�����뷵��ջ��Ԫ�ص�ָ��

����ջ��Ԫ��
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
���룺
ps:����ջ�ṹ��ָ��
item������ջ��Ԫ��

��ջ
*/
int push(SqStack* ps, Item item)
{
	//���������ջ�Ĵ�С�������·���ջ���ڴ�
	if (ps->ptop - ps->pbase >= ps->stacksize)
	{
		//realloc����̬�ڴ����
		//ָ����=����������*��realloc��Ҫ�ı��ڴ��С��ָ�������µĴ�С��
		ps->pbase = (Item*)realloc(ps->pbase, (ps->stacksize + INCREMENT_LENGTH)*sizeof(Item));
		if (ps->pbase == NULL)
		{
			printf("�ڴ����ʧ�ܣ�ջ��չʧ�ܣ�");
			return FALSE;
		}
		else
		{
			ps->ptop = ps->pbase + ps->stacksize;
			ps->stacksize += INCREMENT_LENGTH;
		}
	}
	*(ps->ptop)++ = item;    //��1������item����2��ps->ptop+1��---Ҳ����ptop����û��ָ���κε�item
	return TRUE;
}

/*
ps������ջ�ṹ��ָ��
pitem:��ջԪ��

��ջ
*/
int pop(SqStack* ps, Item* pitem)
{
	if (ps->ptop == ps->pbase)
	{
		printf("ջΪ�գ���ջʧ�ܣ�\n");
		return FALSE;
	}
	else
	{
		*pitem = *(--ps->ptop);  //(1)ps->ptop-1;(2)ɾ��item��---Ҳ����ptop�տ�ʼû��ָ���κ�item���ȼ�һ����ȡ��item
		return TRUE;
	}
}

/*
ps:����ջ�ṹ��ָ��

����ջ
*/
int traverseStack(SqStack ps)
{
	printf("��ջ������\n");
	while (ps.ptop != ps.pbase)            //ջ��Ϊ��
	{
		ps.ptop--;
		Item* pitem = ps.ptop;
		printf("%d %d %6.2f %6.2f\n", pitem->DigitalChannelData[0], pitem->DigitalChannelData[1], pitem->AnalogChannelData[0], pitem->AnalogChannelData[1]);
	}
	return TRUE;
}
