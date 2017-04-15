// 多线程-练习3-TCPIP.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "windowsx.h"
#include "CmnHdr.h"
#include <tchar.h>
#include "resource.h"

//////////////////////////////////////////////////////////////////////////

//事件：客户端发出请求
HANDLE g_hevtRequestSubmitted;

//事件：服务端发出结果
HANDLE g_hevtResultReturned;

//主对话框句柄。当服务线程接收到关闭消息时，会检测该句柄是否有效
HWND g_hMainDlg;

//客户线程与服务线程共享的缓冲区
//TCHAR 定义的宏，可用于双字节字符串
//因为C++支持两种字符串，即常规的ANSI编码（使用""包裹）和Unicode编码（使用L""包裹），这样对应的就有了两套字符串处理函数，比如：strlen和wcslen，分别用于处理两种字符串
TCHAR g_szSharedRequestAndResultBuffer[1024];   

//客户端发送一个特殊的字符串，用来结束程序
TCHAR g_szServerShutdown[] = TEXT("Server Shutdown");

//////////////////////////////////////////////////////////////////////////

//服务器线程执行代码段
DWORD WINAPI ServerThread(PVOID pvParam)
{
	//假设服务线程没被停止
	BOOL fShutdown = FALSE;

	while (!fShutdown)
	{
		//等待客户线程提交请求
		WaitForSingleObject(g_hevtRequestSubmitted, INFINITE);

		//检查是否要结束程序（并关闭对话框时，会设置退出字符串）
		//这里检查g_hMainDlg==NULL，可以防止用户手动输入“Server Shutdown”字符串
		//而导致该线程退出的现象，也就是用户输入该字符串并不退出。
		//_tcscmp用来比较宽字符串UNICODE
		fShutdown = (g_hMainDlg == NULL) && (_tcscmp(g_szSharedRequestAndResultBuffer, g_szServerShutdown) == 0);

		if (!fShutdown)
		{
			//处理客户线程的请求
			_tcsrev(g_szSharedRequestAndResultBuffer);  //反转字符串
		}

		//通知客户线程，服务线程己处理完毕
		SetEvent(g_hevtResultReturned);
	}

	//客户线程要求退出
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
BOOL  Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	chSETDLGICONS(hwnd, IDI_HANDSHAKE);

	//初始化编辑框
	Edit_SetText(GetDlgItem(hwnd, IDC_REQUEST), TEXT("Some test data"));

	g_hMainDlg = hwnd;
	return TRUE;
}

//
void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtrl, UINT codeNotify)
{
	switch (id)
	{
	case IDCANCEL:
		EndDialog(hwnd, id);
		break;
	case IDC_SUBMIT:

		//将客户请求的字符串拷入共享缓冲区
		Edit_GetText(GetDlgItem(hwnd, IDC_REQUEST),
			g_szSharedRequestAndResultBuffer, _countof(g_szSharedRequestAndResultBuffer));
		//客户线程提交请求，表示缓冲区己准备好。并等待服务线程返回处理结果
		SignalObjectAndWait(g_hevtRequestSubmitted, g_hevtResultReturned, INFINITE, FALSE);

		//显示服务线程的处理结果
		Edit_SetText(GetDlgItem(hwnd, IDC_RESULT), g_szSharedRequestAndResultBuffer);
		break;
	}
}

//对话框消息处理函数
INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
		chHANDLE_DLGMSG(hwnd, WM_COMMAND, Dlg_OnCommand);
	}
	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInstExe, HINSTANCE, PTSTR, int)
{
	//创建并初始化2个未触发的自动事件对象
	g_hevtRequestSubmitted = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_hevtResultReturned = CreateEvent(NULL, FALSE, FALSE, NULL);

	//创建服务线程
	DWORD dwThreadID;
	HANDLE hThreadServer = chBEGINTHREADEX(NULL, 0, ServerThread, NULL, 0, &dwThreadID);

	/*
	INT_PTR DialogBox(          
	HINSTANCE hInstance,
    LPCTSTR lpTemplate,
    HWND hWndParent,
    DLGPROC lpDialogFunc
	);
	这个函数根据对话框资源，创建一个模式对话框，这个对话框应该用EndDialog来结束。
	hInstance 当前应用程序实例句柄。
	lpTemplate 标识对话框模板资源，有两种使用方式：一种是把对话框模板的ID强制转为LPCTSTR，一种可以使用MAKEINTRESOURCE宏得到标识ID。
	hWndParent 父窗口的句柄。
	lpDialogFunc 对话框消息处理函数。
	*/

	//运行UI线程（主线程,也是客户线程）
	DialogBox(hInstExe, MAKEINTRESOURCE(IDD_HANDSHAKE), NULL, Dlg_Proc);
	g_hMainDlg = NULL; //表示对话框己退出

	//主线程UI线程正在关闭，这时服务线程可能被阻塞在Wait*函数中，将其唤醒，
	//并填写退出字符串，以便退出
	_tcscpy_s(g_szSharedRequestAndResultBuffer, _countof(g_szSharedRequestAndResultBuffer), g_szServerShutdown);
	SetEvent(g_hevtRequestSubmitted);

	//等待服务线程退出
	HANDLE h[2];
	h[0] = g_hevtResultReturned;    //服务器返回字符线程
	h[1] = hThreadServer;    //服务器线程
	WaitForMultipleObjects(2, h, TRUE, INFINITE);

	//关闭所有的句柄
	CloseHandle(g_hevtResultReturned);
	CloseHandle(g_hevtRequestSubmitted);
	CloseHandle(hThreadServer);
	return 0;
}