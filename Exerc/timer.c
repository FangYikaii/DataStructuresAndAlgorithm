#include <stdio.h>
#include "windows.h"  

/*
#pragma comment( comment-type ,["commentstring"] )
comment-type��һ��Ԥ����ı�ʶ����ָ��ע�͵����ͣ�Ӧ����compiler��exestr��lib��linker֮һ��
commentstring��һ���ṩΪcomment - type�ṩ������Ϣ���ַ�����
Winmm.lib:����֧��windows��ý����
*/
#pragma comment(lib,"Winmm.lib")   //UINT , UINT ,DWORD ,DWORD ,DWORD 

int gtime_ID1, gtime_ID2;          //���صõ���ID

void CALLBACK print100ms(UINT wTimerID, UINT msg, DWORD data, DWORD dwl, DWORD dw2)
{
	printf("100ms print:%d\n", data);
}


void CALLBACK print1000ms(UINT wTimerID, UINT msg, DWORD data, DWORD dwl, DWORD dw2)
{
	printf("~~~~~~1000ms print:%d\n", data);
}

//DWORD_PRTd
//word   ˫�� �����ĸ��ֽ�
//ptr     pointer��д ��ָ��
//[]���������һ����ֵַ�������ַָ��һ��˫��������
//����mov eax, dword ptr[12345678]  ���ڴ��ַ12345678�е�˫���ͣ�32λ�����ݸ���ea
void DataAcq(DWORD_PTR data)    
{

	/*
	MMRESULT timeSetEvent�� UINT uDelay, UINT uResolution,  LPTIMECALLBACK lpTimeProc, WORD dwUser, UINT fuEvent ��
	����: uDelay���Ժ���ָ���¼������ڡ�
	Uresolution���Ժ���ָ����ʱ�ľ��ȣ���ֵԽС��ʱ���¼��ֱ���Խ�ߡ�ȱʡֵΪ1ms��
	LpTimeProc��ָ��һ���ص�������
	DwUser������û��ṩ�Ļص����ݡ�
	FuEvent��ָ����ʱ���¼����ͣ�
		TIME_ONESHOT��uDelay�����ֻ����һ���¼�
		TIME_PERIODIC ��ÿ��uDelay���������Եز����¼�
	*/
	gtime_ID1 = timeSetEvent(100, 1, (LPTIMECALLBACK)print100ms, data, TIME_PERIODIC);
	gtime_ID2 = timeSetEvent(1000, 1, (LPTIMECALLBACK)print1000ms, data, TIME_PERIODIC);
	if (gtime_ID1 == NULL || gtime_ID2 == NULL)
	{
		printf("time ID is not created\n");
		return;
	}
	return;
}

void main()
{
	int i = 0;
	while (1)
	{
		DataAcq(i);	
		Sleep(1000);
		i++;

		/*
		timeKillEvent �ص���ʱ���ĺ�����һ��Ҫһһ��Ӧ��ÿ��timeSetEvent���صĶ�ʱ����ID�ǲ�һ���ģ�Ҳ����˵����һ��timeSetEvent�ͻ����һ��Id
		���ü���timeSetEvent������Ҫ���ü���timeKillEvent �����ұ��������Ӧ��ID,������ܳ��ֳ������
		*/
		timeKillEvent(gtime_ID1);
		timeKillEvent(gtime_ID2);
	}
}

