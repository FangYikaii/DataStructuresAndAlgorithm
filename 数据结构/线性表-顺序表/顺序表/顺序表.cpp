#include "stdafx.h"
#include <stdio.h>
#include <string.h>

#define MAXLEN 100        //����˳������󳤶�

typedef struct
{
	char key[10];        //�ڵ�ؼ���
	char name[20];
	int age;
}DATA;                  //����ڵ�����


//���±�1��ʼ��¼�ڵ�
typedef struct
{
	DATA ListData[MAXLEN + 1];      //����˳���Ľṹ����,������101�����ݳ���
	int ListLen;                    //˳����Ѵ�ڵ������
}SLType;             //����˳���ṹ


void SLInit(SLType* SL)  //��ʼ��˳������ԭ����˳����Ѿ��������ݣ�Ҳ�ᱻ���ǣ���Ӱ�����
{
	SL->ListLen = 0;
}

int SLLength(SLType* SL)
{
	return (SL->ListLen);     //����˳����Ԫ������
}

int SLInsert(SLType* SL, int n, DATA data)    //����Ԫ��
{
	int i;
	//���˳���ڵ������Ѿ�������������
	if (SL->ListLen >= MAXLEN)
	{
		printf("˳������������ܲ���ڵ㣡\n");
		return 0;
	}
	//����ڵ���Ų���ȷ
	if (n<1 || n>SL->ListLen - 1)
	{
		printf("����Ԫ����Ŵ��󣬲��ܲ���Ԫ�أ�\n");
		return 0;
	}
	//��˳������������ƶ�
	for (i = SL->ListLen; i >= n; i--)
	{
		SL->ListData[i + 1] = SL->ListData[i];
	}
	//����ڵ�
	SL->ListData[n] = data;
	//˳���ڵ�����+1
	SL->ListLen++;
	return 1;   //�ɹ����룬����1
}


int SLAdd(SLType* SL, DATA data)   //׷�ӽڵ�
{
	if (SL->ListLen >= MAXLEN)
	{
		printf("˳�����������������ӽڵ��ˣ�\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}

int SLDelete(SLType* SL, int n)  //ɾ���ڵ�
{
	int i;
	if (n<1 || n>SL->ListLen + 1)
	{
		printf("ɾ���ڵ���Ŵ��󣬲���ɾ���ڵ㣡");
		return 0;   //ɾ�����ɹ�������0
	}
	//��˳����е�������ǰ�ƶ�������
	for (i = n; i < SL->ListLen; i++)
	{
		SL->ListData[i] = SL->ListData[i + 1];
	}
	SL->ListLen--;      //˳���Ԫ�ؼ�һ
	return 1;
}

DATA* SLFindByNumber(SLType* SL, int n)  //������ŷ�������Ԫ��
{
	if (n<1 || n>SL->ListLen + 1)
	{
		printf("�ڵ���Ŵ��󣬲��ܷ��ؽڵ㣡\n");
		return NULL;
	}
	return &(SL->ListData[n]);    //���������ӦԪ�صĵ�ַ
}

int SLFindByCont(SLType* SL, char* key)  //���ؼ��ֽڵ��ѯ����
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

int SLAll(SLType* SL)   //��ʾ���нڵ�
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
	SLType SL;    //����˳������
	DATA data;    //����ڵ㱣���������ͱ���
	DATA *pdata;  //����ڵ㱣��ָ�����
	char  key[10];

	printf("˳��������ʾ��\n");
	SLInit(&SL);    //��ʼ��˳���˳�������ĵ�ַ��Ϊ��������
	printf("��ʼ��˳�����ɣ�\n");
	do
	{
		printf("������ӵĽڵ㣨ѧ�� ���� ���䣩��");
		fflush(stdin);  //������뻺����
		//_flushall();  //������л�����
		scanf("%s%s%d", &data.key, &data.name, &data.age);
		if (data.age)   //�����䲻Ϊ0
		{
			if (!SLAdd(&SL, data))    //����ӽڵ�ʧ��
			{
				break;
			}
		}
		else            //������Ϊ0
		{
			break;      //�˳���ѭ��
		}
	} while (1);
	printf("\n˳���Ľڵ�˳��Ϊ��\n");
	SLAll(&SL);

	fflush(stdin);
	printf("\nҪȡ���ڵ����ţ�");
	scanf("%d", &i);
	//������Ų��ҽڵ㣺���ص���Data�ṹ���ָ�룬���������˳�������ĵ�ַ
	pdata = SLFindByNumber(&SL, i);
	//����ֵ��Ϊ��
	if (pdata)
	{
		printf("��%d���ڵ�β����%s%s%d��\n", i, pdata->key, pdata->name, pdata->age);
	}
	scanf("%d", &i);
	return 0;
}



