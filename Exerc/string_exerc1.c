#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  

/*
���±�׼��һ���ַ���S��ʾһ���绰���룬�ַ�����N���ַ���ɣ����֣��ո񣬶����ߣ�-�����������ٰ�����λ����
���±�׼������1�����Ժ����ַ���S�еĿո�Ͷ����ߣ���2���������Գ���Ϊ3�Ŀ���з��飬�õ��������߷ָ���3���������һ�����������������ַ����ȿ�����2

NΪ2-100�ڵ�������
�ַ���s����0-9���ո�Ͷ��������
s���ٰ�����λ����
*/

#define N 100           //�ַ�����󳤶�

char* solution(char* s)          
{
	int i,j=0;
	int len = strlen(s);        //����
	char* str_cut = NULL;       //���壺ɾ�������ַ�����ַ���
	char* str_out = NULL;       //���壺����������ַ���
	str_cut=(char*)malloc(N * sizeof(char));        //malloc����N���ȵ�char�ڴ�
	str_out= (char*)malloc(N * sizeof(char));       //malloc����N���ȵ�char�ڴ�

	//����ַ����Ƿ����0-9���ո񣬶�����
	for (i = 0; i < len; i++)
	{
		if (s[i] <= '9'&&s[i] >= '0' || s[i] == '-'||s[i]==' ')
		{

		}
		else
		{
			exit(1);
		}
	}

	//�ַ�������
	for (i = 0; i < len; i++)
	{
		if (s[i] <= '9'&&s[i] >= '0')
		{
			str_cut[j] = s[i];
			j++;
		}
	}
	str_cut[j] = '\0';            //�������ַ���
	len = strlen(str_cut);        //�����ĳ���
	if (len < 2)
	{
		exit(1);
	}
	if (len % 3 == 0)
	{
		j = len / 3;
		for (i = 0; i < j-1; i++)  //������6������j=2������ֻ��ѭ��һ�Σ�����i=0��iҪ��j-1
		{
			str_out[i * 4] = str_cut[i * 3];
			str_out[i * 4 + 1] = str_cut[i * 3 + 1];
			str_out[i * 4 + 2] = str_cut[i * 3 + 2];
			str_out[i * 4 + 3] = '-';
		}
		//���һ��
		str_out[i * 4] = str_cut[i * 3];
		str_out[i * 4 + 1] = str_cut[i * 3 + 1];
		str_out[i * 4 + 2] = str_cut[i * 3 + 2];
		str_out[i * 4 + 3] = '\0';
	}
	else if (len % 3 == 1)
	{
		j = len / 3;
		for (i = 0; i < j-1; i++)     //������7������j=2������ֻ��ѭ��һ�Σ�����i=0��iҪ��j-1��ʡ��4��
		{
			str_out[i * 4] = str_cut[i * 3];
			str_out[i * 4 + 1] = str_cut[i * 3 + 1];
			str_out[i * 4 + 2] = str_cut[i * 3 + 2];
			str_out[i * 4 + 3] = '-';
		}
		//���һ��
		str_out[i * 4] = str_cut[i * 3];
		str_out[i * 4 + 1] = str_cut[i * 3 + 1];
		str_out[i * 4 + 2] = '-';
		str_out[i * 4 + 3] = str_cut[i * 3 + 2];
		str_out[i * 4 + 4] = str_cut[i * 3 + 3];
		str_out[i * 4 + 5] = '\0';
	}
	else
	{
		j = len / 3;
		for (i = 0; i < j; i++)   //������7������j=2������ֻ��ѭ��һ�Σ�����i=0��iҪ��j-1��ʣ��5��
		{
			str_out[i * 4] = str_cut[i * 3];
			str_out[i * 4 + 1] = str_cut[i * 3 + 1];
			str_out[i * 4 + 2] = str_cut[i * 3 + 2];
			str_out[i * 4 + 3] = '-';
		}
		//���һ��
		str_out[i * 4] = str_cut[i * 3];
		str_out[i * 4 + 1] = str_cut[i * 3 + 1];
		str_out[i * 4 + 2] = str_cut[i * 3 + 2];
		str_out[i * 4 + 3] = '-';
		str_out[i * 4 + 4] = str_cut[i * 3 + 3];
		str_out[i * 4 + 5] = str_cut[i * 3 + 4];
		str_out[i * 4 + 6] = '\0';
	}
	free(str_cut);   //�ͷž���������ڴ�
	return str_out;
}

//������  
void main()
{
	char str[N];   //����һ��str
	char* str_new = NULL;
	str_new = (char*)malloc(N * sizeof(char));       //malloc����N���ȵ�char�ڴ�
	gets(str);     //gets��fgets���տո�
	printf("ԭʼ�ַ�����%s\n", str);
	str_new=solution(str);
	printf("�����ַ�����%s\n",str_new);
	while (1);
}