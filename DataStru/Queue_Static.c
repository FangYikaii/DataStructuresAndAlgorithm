#include <stdio.h>  
#include "stdlib.h"
#include <malloc.h>  
#include <windows.h>
/*
���У�
���Ƚ��ȳ����Ĵ洢�ṹ��
����ʽ���У�������ʵ�֣��������ࣩ��
�ھ�̬���У�������ʵ�֣�����̬����ͨ����������ѭ�����С�

ѭ�����е�����������
��front,frontָ����еĵ�һ��Ԫ�ء�
��rear,rearָ����е����һ����ЧԪ�ص���һԪ�ء�
���е������������������Ӻ���ӡ�
========================================================
��ӣ�β����ӣ�
�ٽ�ֵ����rear�������λ�á�
��rear = (rear+1)%����ĳ��ȡ�

���ӣ�ͷ�����ӣ�
front = (front+1)%����ĳ��ȡ�

�����Ƿ�Ϊ��
front��rear��ֵ��ȣ���ö��о�һ��Ϊ�ա�

�����Ƿ�����
ע�⣺ѭ�������У���n��λ�ã�ͨ����n-1��ֵ����1��
��ѭ�������У�front��rearָ���ֵ����أ��޹��ɡ�front���ܱ�rearָ���ֵ��Ҳ���ܱ�rearָ���ֵС��Ҳ����������ȡ�

�㷨��
�ٶ�����һ����ʶ������
������һ��Ԫ�أ�rear��frontָ���ֵ�����ţ������������
*/

/*
#include <stdlib.h>
int rand(void);
����һ��α���������Χ��0-RAND_MAX(����ʵ�ֲ�ͬ����������32767)
void srand(unsigned int seed);
����α������㷨�����ӣ����seed��ͬ�����ɵ�α�������ÿ����ͬ


�������
(1)rand()%n   ��Χ��0~n-1
(2)n+rand()%(m-n+1)   ��Χ��0~n-1
(3)rand()%(double)(RAND_MAX/x)   ��Χ��0~n double
(4)
*/
#define random_int(x)        (rand()%x)                          //���������
#define random_double(x)      (rand()/(double)(RAND_MAX/x))       //˫�����������
#define MAX_LENGTH           100                                 //������󳤶�
#define TRUE                 1
#define FALSE                0
//������
typedef struct Item
{
	int DigitalChannelData[2];            //������
	double AnalogChannelData[2];          //ģ����
}Item;

//���нṹ
typedef struct QueueStatic
{
	Item* pBase;           //���ڶ�̬�����ڴ棬pBase���ڱ���ָ��Item��ָ��������׵�ַ
	int front;             //ָ��ͷ���
	int rear;              //ָ��β�ڵ�
}QS;

//��������  
Item initItem(Item item);               //��ʼ��һ��Item�ṹ

void initQueue(QS* pQs);                //���г�ʼ���ĺ���  
int enQueue(QS* pQs, Item item);        //��ӵĺ���   
int outQueue(QS* pQs, Item* pItem);     //���ӵĺ���,ͬʱ������ӵ�Ԫ�� 
int isEmpty(QS* pQs);                   //�ж϶����Ƿ�Ϊ�յĺ���  
int isFull(QS* pQs);                    //�ж϶����Ƿ����ĺ���   
void traverseQueue(QS* pQs);            //�������еĺ���  

void main()
{
	QS qs;                      //�������ж����ָ��
	Item item = { 0, 0, 0, 0 };                   //���ڱ��������Ԫ�صĵ�ַ
	srand((unsigned)time(NULL));         //����α������㷨������
	initQueue(&qs);
	while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			item = initItem(item);
			enQueue(&qs, item);
		}
		printf("(1)����У�\n");
		traverseQueue(&qs);
		Sleep(3000);

		printf("(2)�����У�\n");
		while (!isEmpty(&qs))
		{
			if (outQueue(&qs, &item))
			{
				printf("���ӣ�%d %d %6.2f %6.2f\n", item.DigitalChannelData[0], item.DigitalChannelData[0], item.AnalogChannelData[0], item.AnalogChannelData[1]);
			}
		}
		Sleep(3000);

		printf("(3)��ն��У��˿̶���:\n");
		traverseQueue(&qs);

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
pQs:������нṹ��ָ��

��ʼ������
*/
void initQueue(QS* pQs)
{
	pQs->pBase = (Item*)malloc(sizeof(Item)*MAX_LENGTH);   //��̬����MAX_LENGTH��Item��������ռ�ռ� 
	pQs->front = 0;                                        //��ʼ����front��rearֵΪ0
	pQs->rear = 0;
}

/*
���룺
pQs:������нṹ��ͷָ��
item��������

����к�����ʵ��
*/
int enQueue(QS* pQs, Item item)
{
	if (isFull(pQs))
	{
		printf("���������������ʧ�ܣ�\n");
		return FALSE;
	}
	else
	{
		//�����������µ�Ԫ��
		pQs->pBase[pQs->rear] = item;
		pQs->rear = (pQs->rear + 1) % MAX_LENGTH;       //��������rearȡֵ��Χ��0-MAX_LENGTH
		return TRUE;
	}
}

/*
���룺
pQs��������нṹ��ͷָ��
pItem:�����еĽڵ���������ָ��

���ӵĺ���,ͬʱ������ӵ�Ԫ��
*/
int outQueue(QS* pQs, Item* pItem)
{
	//�������Ϊ�գ�����false
	if (isEmpty(pQs))
	{
		printf("����Ϊ�գ�������ʧ�ܣ�\n");
		return FALSE;
	}
	else
	{
		*pItem = pQs->pBase[pQs->front];
		pQs->front = (pQs->front + 1) % MAX_LENGTH;
		return TRUE;
	}
}

/*
���룺
pQs��������нṹ��ͷָ��

�������к�����ʵ��
*/
void traverseQueue(QS* pQs)
{
	int i = pQs->front;             //�Ӷ���ͷ��ʼ
	printf("�������У�\n");
	while (i != pQs->rear)             //���û�дﵽrearλ�ã��Ϳ�ʼѭ��
	{
		printf("%d %d %6.2f %6.2f\n", pQs->pBase[i].DigitalChannelData[0], pQs->pBase[i].DigitalChannelData[0], pQs->pBase[i].AnalogChannelData[0], pQs->pBase[i].AnalogChannelData[1]);
		i = (i + 1) % MAX_LENGTH;              //�ƶ�����һ��λ��
	}
	printf("\n");
}

/*
���룺
pQs��������нṹ��ͷָ��

�ж϶����Ƿ������ĺ���ʵ��
*/
int isFull(QS* pQs)
{
	if ((pQs->rear + 1) % MAX_LENGTH == pQs->front)       //������
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
pQs��������нṹ��ͷָ��

�ж϶����Ƿ�Ϊ�յĺ���ʵ��
*/
int isEmpty(QS* pQs)
{
	if (pQs->rear == pQs->front)       //������
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}