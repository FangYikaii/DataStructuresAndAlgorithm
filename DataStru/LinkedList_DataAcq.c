#include <stdio.h>  
#include <malloc.h>  
#include <windows.h>
#include "stdlib.h"

/*
  #pragma comment( comment-type ,["commentstring"] )
  comment-type��һ��Ԥ����ı�ʶ����ָ��ע�͵����ͣ�Ӧ����compiler��exestr��lib��linker֮һ��
  commentstring��һ���ṩΪcomment - type�ṩ������Ϣ���ַ�����

  Winmm.lib:����֧��windows��ý����
*/
#pragma comment(lib,"Winmm.lib")

#define random_int(x)        (rand()%x)
#define random_double(x)      (rand()/(double)(RAND_MAX/x))

typedef struct Item;//��������������  
typedef struct node * PNode;//����ڵ�ָ��  

//������
typedef struct Item
{
	int DigitalChannelData[2];            //������
	double AnalogChannelData[2];          //ģ����
}Item;


//�ڵ�Ķ���  
typedef struct node
{
	Item item;//������  
	PNode next;//����  
}Node, *SList;


//int gtime_ID1, gtime_ID2;


Item InitItem(Item item);                            //����һ��Item������ṹ��
int SL_Creat(SList *p_list, int size);               //����һ��size����������ͷָ�븳��p_listָ��
int SL_Insert(SList list, int pos, Item item);		 //�ú����Ĺ�����������list��posλ�ò�����Ԫ�أ���ֵΪitem
int SL_GetItem(SList list, int pos, Item *p_item);   //�ú����Ĺ����ǻ�ȡ������list��posλ�õ�Ԫ�ص��������ֵ����p_item��ָ�ı���
int SL_Delete(SList list, int pos, Item *p_item);    //�ú����Ĺ�����ɾ��������list��posλ�õ�Ԫ�أ���ֵ����p_item��ָ�ı���
int SL_SetItem(SList list, int pos, Item item);      //�ú����Ĺ����ǽ�����list��posλ�õ�Ԫ�ص�����������Ϊitem
int SL_Empty(SList list);                            //�ú����Ĺ������ж�����list�Ƿ�Ϊ�ձ�
int SL_Size(SList list);                             //�ú����Ĺ����Ƿ�������list�нڵ�ĸ���������ͷ�ڵ�
int SL_Clear(SList *p_list);                         //�ú����Ĺ����������������нڵ㣬����ͷ�ڵ�
SList AddDatax(SList plist);                         //��plist������ݣ�һ��һ��
SList printx(SList plist);                           //ʵ��plist�Ĵ�ӡ�����
/*
����
Item:
����ֵ
Item��
�ú������ڳ�ʼ��һ��Item
*/
Item InitItem(Item item)
{
	item.DigitalChannelData[0] = random_int(10);
	item.DigitalChannelData[1] = random_int(10);
	item.AnalogChannelData[0] = random_double(100);
	item.AnalogChannelData[1] = random_double(1000);
	return item;
}

/*
int SL_Creat(SList *p_list,int size)
����
p_list��ָ��һ������ָ�룬�˴������ͷ��ַ
size��Ҫ������������������Ԫ�ؿռ������������ͷ�ڵ�
����ֵ
���ɹ�����1�����򷵻�0��
����
�ú����Ĺ����Ǵ���һ����СΪsize�������������ͷָ�븳��p_lsit��ָ������ָ�롣
*/
int SL_Creat(SList *p_list, int size)
{
	PNode p = NULL;
	int i;

	*p_list = (SList)malloc(sizeof(Node));       //Ϊ����ָ������ڴ�
	if (*p_list == NULL)                         //�������ָ��Ϊ�գ��򷵻�
		return -1;
	(*p_list)->next = NULL;                      //����ָ����ָ�ڵ㣬ָ����Ϊ��
	(*p_list)->item = InitItem((*p_list)->item); //����ָ����ָ�ڵ㣬������

	for (i = size; i>1; i--)                     //��ʼ������ָ�룺size-1��
	{
		p = (PNode)malloc(sizeof(Node));         //Ϊ�ڵ�����ڴ�
		if (p == NULL)
			return -1;
		p->item = InitItem(p->item);             //�ڵ�������
		p->next = (*p_list)->next;               //��p_list��ָ����Ҳ����β��(null)���ŵ�p��ָ������
		(*p_list)->next = p;                     //��p_list������������Ϊp
	}
	return 1;
}

/*
int SL_Insert(SList list,int pos,Item item)
����
list��Ҫ�������ݵĵ�����
int��ָ��Ҫ����Ԫ�ص�λ�ã���1��ʼ����
item:Ҫ�����������
����ֵ
���ɹ�����1�����򷵻�-1��
����
�ú����Ĺ�����������list��posλ�ò�����Ԫ�أ���ֵΪitem��
*/
int SL_Insert(SList list, int pos, Item item)
{
	PNode p, q;
	int i;
	p = list;                                        //Ҫ�������ݵĵ�����
	i = 0; 
	while (p != NULL && i<pos - 1)                   //��ָ��p�ƶ���Ҫ����Ԫ��λ��֮ǰ  
	{
		p = p->next;                                 // pָ����һ��ָ����ֱ���ҵ�Ҫ������Ǹ��ڵ�p
		i++;                                         //i��pos��Ƚϣ�ֱ��i��pos-1���
	}
	if (p == NULL || i > pos - 1)
		return -1;

	q = (Node *)malloc(sizeof(Node));               //δ����ڵ�����ڴ�  
	if (q != NULL)                                  //���ڴ����ɹ������ڵ����ָ��λ��  
	{
		q->item = item;                             //������
		q->next = p->next;                          //��q��ָ����ָ��Ҫ����ڵ�p��ָ�����λ��
		p->next = q;                                //��p��ָ����ָ��q�ϣ�Ҳ���� ������һ��q
		return 1;
	}
	else
	{
		return -1;
	}
}

/*
int SL_GetItem(SList list,int pos,Item *p_item)
����
list��Ҫ��ȡ���������ڵĵ�����
int��ָ��Ҫ��ȡԪ���ڵ������е�λ��
p_item:ָ��Ҫ����������ı���
����ֵ
���ɹ�����1�����򷵻�-1��
����
�ú����Ĺ����ǻ�ȡ������list��posλ�õ�Ԫ�ص��������ֵ����p_item��ָ�ı�����
*/
int SL_GetItem(SList list, int pos, Item *p_item)
{
	PNode p;
	int i;

	p = list;
	i = 0;
	while (p != NULL && i<pos)                         //��ָ��p�ƶ���Ҫ���ص�Ԫ��λ��  
	{
		p = p->next;
		i++;                                           //i��¼pָ����ǵڼ���λ��  
	}
	if ((p == NULL) || (i>pos))
	{
		return -1;
	}
	*p_item = p->item;
	return 1;
}

/*
int SL_Delete(SList list,int pos,Item * p_item)
����
list��Ҫɾ��Ԫ�����ڵĵ�����
int��ָ��Ҫɾ��Ԫ���ڵ������е�λ��
p_item:ָ�����ɾ��Ԫ�ص�������ı���
����ֵ
���ɹ�����1�����򷵻�-1��
����
�ú����Ĺ�����ɾ��������list��posλ�õ�Ԫ�أ���ֵ����p_item��ָ�ı�����
*/
int SL_Delete(SList list, int pos, Item * p_item)
{
	PNode p, q;
	int i;
	p = list;
	i = 0;
	while (p != NULL && i<pos - 1)        //��ָ��p�ƶ���Ҫɾ��Ԫ��λ��֮ǰ  
	{
		p = p->next;
		i++;//i��¼pָ����ǵڼ���λ��  
	}
	if (p->next == NULL || i > pos - 1)
		return -1;
	q = p->next;
	p->next = q->next;                      //��Ҫɾ��Ԫ��λ��֮ǰ��Ԫ�ص�ָ����ָ��Ҫɾ��Ԫ��λ��֮���ָ��
	if (p_item != NULL)                      //ȡ��Ҫɾ��Ԫ�ص�������
		*p_item = q->item;                      
	free(q);                                //�ͷŽڵ��ڴ�
	return 1;
}

/*
int SL_SetItem(SList list,int pos,Item item)
����
list��Ҫ����Ԫ�����ڵĵ�����
int��ָ��Ҫ����Ԫ���ڵ������е�λ��
p_item:Ҫ����Ԫ�ص��������ֵ
����ֵ
���ɹ�����1�����򷵻�-1��
����
�ú����Ĺ����ǽ�����list��posλ�õ�Ԫ�ص�����������Ϊitem��
*/
int SL_SetItem(SList list, int pos, Item item)
{
	PNode p = NULL;
	int i;
	p = list;
	i = 0;
	while (p != NULL && i<pos)//��ָ��p�ƶ���Ҫ����Ԫ��λ��֮ǰ  
	{
		p = p->next;
		i++;//i��¼pָ����ǵڼ���λ��  
	}
	if (p == NULL || i > pos)
		return -1;
	p->item = item;
	return 1;
}

/*
int SL_Empty(SList list)
����
list��Ҫ�жϵĵ�����
����ֵ
��Ϊ���򷵻�1�����򷵻� 0��
����
�ú����Ĺ������ж�����list�Ƿ�Ϊ�ձ�

*/
int SL_Empty(SList list)
{
	PNode p;
	p = list;
	if (p == NULL)
		return 1;
	return 0;
}

/*
int SL_Size(SList list)
����
list��Ҫ���ҵĵ�����
����ֵ
���ذ����ڵ�ĸ�����
����
�ú����Ĺ����Ƿ�������list�нڵ�ĸ���������ͷ�ڵ㡣

*/
int SL_Size(SList list)
{
	PNode p;
	int i;

	p = list;
	i = 0;
	while (p != NULL)
	{
		p = p->next;
		i++;
	}
	return i;
}

/*
int SL_Clear(SList *p_list)
����
p_list��ָ��Ҫ����ĵ�����
����ֵ
�ɹ�����ֵΪ1��
����
�ú����Ĺ����������������нڵ㣬����ͷ�ڵ㡣

*/
int SL_Clear(SList *p_list)
{
	PNode p, q;
	p = *p_list;          //p_listΪplistָ���SList
	while (p != NULL)
	{
		q = p->next;     //������q�洢p�����򣬷����ͷ�p���޷�����  
		free(p);         //�ͷ�p
		p = q;           //pָ����һ��
	}
	*p_list = NULL;//����ָ������ָ����ΪNULL  

	return 1;
}


/*
��ӡ����ʵ������ı���
*/
void SL_Print(SList list)
{
	if (NULL == list)   //����Ϊ��
	{
		printf("PrintList����ִ�У�����Ϊ��\n");
	}
	else
	{
		while (NULL != list)
		{
			printf("%d, %d, %6.2f, %6.2f\n", list->item.DigitalChannelData[0], list->item.DigitalChannelData[1], list->item.AnalogChannelData[0], list->item.AnalogChannelData[1]);
			list = list->next;
		}
	}
}

//SList CALLBACK AddData(UINT wTimerID, UINT msg, DWORD plist, DWORD dwl, DWORD dw2)
//{
//	if (SL_Empty(plist))
//	{
//		SL_Creat(&plist, 1);
//	}
//	else
//	{
//		int len = SL_Size(plist);
//		Item item = { 0, 0, 0, 0 };
//		item = InitItem(item);
//		SL_Insert(plist, len, item);
//	}
//	return plist;
//}
//
//SList CALLBACK print1000ms(UINT wTimerID, UINT msg, DWORD plist, DWORD dwl, DWORD dw2)
//{
//	SL_Print(plist);
//	SL_Clear(&plist);
//	return plist;
//}
//
//void DataAcq(DWORD_PTR plist)
//{
//	gtime_ID1 = timeSetEvent(100, 1, (LPTIMECALLBACK)AddData, plist, TIME_PERIODIC);
//	gtime_ID2 = timeSetEvent(1000, 1, (LPTIMECALLBACK)print1000ms, plist, TIME_PERIODIC);
//	if (gtime_ID1 == NULL || gtime_ID2 == NULL)
//	{
//		printf("time ID is not created\n");
//		return;
//	}
//	return;
//}



//��plist������ݣ�һ��һ��
SList AddDatax(SList plist)
{
	if (SL_Empty(plist))    //���Ϊ��
	{
		SL_Creat(&plist, 1);
	}
	else
	{
		int len = SL_Size(plist);
		Item item = { 0, 0, 0, 0 };
		item = InitItem(item);
		SL_Insert(plist, len, item);
	}
	return plist;
}

//ʵ��plist�Ĵ�ӡ�����
SList printx(SList plist)
{
	SL_Print(plist);     //��ӡ
	SL_Clear(&plist);    //���
	return plist;
}

void main()
{
	SList p_list = NULL;
	int size = 10;
	while (1)
	{
		//DataAcq(p_list);	
		//Sleep(1000);
		//timeKillEvent(gtime_ID1);
		//timeKillEvent(gtime_ID2);

		for (int i = 0; i < 10; i++)
		{
			p_list = AddDatax(p_list);
		}
		p_list = printx(p_list);
		Sleep(50000);
		printf("\n\n\n\n\n\n");
	}
}