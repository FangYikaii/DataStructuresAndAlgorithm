// 多线程-练习3-事件Event.cpp : 定义控制台应用程序的入口点。
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
	LPSECURITY_ATTRIBUTES lpEventAttributes,    // SECURITY_ATTRIBUTES结构指针，可为NULL
	BOOL bManualReset,                          // 手动/自动
	　                                           // TRUE： 在WaitForSingleObject后必须手动调用
	ResetEvent清除信号                    　   // FALSE：在WaitForSingleObject后，系统自动清除事件信号
	BOOL bInitialState,                         // 初始状态
													LPCTSTR lpName                              // 事件的名称
	);*/
	hThread1 = CreateThread(NULL, 0, Thread1, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Thread2, NULL, 0, NULL);
	SetEvent(g_hEvent);
	Sleep(4000);        // 让2个线程有足够的时间执行完操作。  
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
		//请求事件对象
		WaitForSingleObject(g_hEvent, INFINITE);  //长时间等待
		if (g_iCnt > 0)
		{
			Sleep(20);
			cout << "Thread1:" << g_iCnt-- << endl;
			SetEvent(g_hEvent);   //事件
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
		//请求事件对象
		WaitForSingleObject(g_hEvent, INFINITE);  //长时间等待
		if (g_iCnt > 0)
		{
			Sleep(20);
			cout << "Thread2:" << g_iCnt-- << endl;
			SetEvent(g_hEvent);   //事件
		}
		else
		{
			SetEvent(g_hEvent);
			break;
		}
	}
	return 0;
}
