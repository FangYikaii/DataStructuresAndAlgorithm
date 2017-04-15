// ���߳�-��ϰ3-�¼�Event.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI Thread1(LPVOID lpParmeter);
DWORD WINAPI Thread2(LPVOID lpParmeter);

static HANDLE g_hEvent = INVALID_HANDLE_VALUE;
static int g_iCnt = 100;

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread1 = INVALID_HANDLE_VALUE;
	HANDLE hThread2 = INVALID_HANDLE_VALUE;
	g_hEvent = CreateEvent(NULL, false, false, "Event");
	if (!g_hEvent)
	{
		cout << "Failed to CreateEvent !" << endl;
		return 0;
	}
	/*HANDLE CreateEvent(
	LPSECURITY_ATTRIBUTES lpEventAttributes,    // SECURITY_ATTRIBUTES�ṹָ�룬��ΪNULL
	BOOL bManualReset,                          // �ֶ�/�Զ�
	��                                           // TRUE�� ��WaitForSingleObject������ֶ�����
	ResetEvent����ź�                    ��   // FALSE����WaitForSingleObject��ϵͳ�Զ�����¼��ź�
	BOOL bInitialState,                         // ��ʼ״̬
													LPCTSTR lpName                              // �¼�������
	);*/
	hThread1 = CreateThread(NULL, 0, Thread1, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Thread2, NULL, 0, NULL);
	SetEvent(g_hEvent);
	Sleep(4000);        // ��2���߳����㹻��ʱ��ִ���������  
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	system("PAUSE");
	return 0;

	return 0;
}

DWORD WINAPI Thread1(LPVOID lpParmeter)
{
	while (true)
	{
		//�����¼�����
		WaitForSingleObject(g_hEvent, INFINITE);  //��ʱ��ȴ�
		if (g_iCnt > 0)
		{
			Sleep(20);
			cout << "Thread1:" << g_iCnt-- << endl;
			SetEvent(g_hEvent);   //�¼�
		}
		else
		{
			SetEvent(g_hEvent);
			break;
		}
	}
	return 0;
}

DWORD WINAPI Thread2(LPVOID lpParameter)
{
	while (true)
	{
		//�����¼�����
		WaitForSingleObject(g_hEvent, INFINITE);  //��ʱ��ȴ�
		if (g_iCnt > 0)
		{
			Sleep(20);
			cout << "Thread2:" << g_iCnt-- << endl;
			SetEvent(g_hEvent);   //�¼�
		}
		else
		{
			SetEvent(g_hEvent);
			break;
		}
	}
	return 0;
}
