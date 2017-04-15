// ���߳�-��ϰ3-TCPIP.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "windowsx.h"
#include "CmnHdr.h"
#include <tchar.h>
#include "resource.h"

//////////////////////////////////////////////////////////////////////////

//�¼����ͻ��˷�������
HANDLE g_hevtRequestSubmitted;

//�¼�������˷������
HANDLE g_hevtResultReturned;

//���Ի��������������߳̽��յ��ر���Ϣʱ������þ���Ƿ���Ч
HWND g_hMainDlg;

//�ͻ��߳�������̹߳���Ļ�����
//TCHAR ����ĺ꣬������˫�ֽ��ַ���
//��ΪC++֧�������ַ������������ANSI���루ʹ��""��������Unicode���루ʹ��L""��������������Ӧ�ľ����������ַ��������������磺strlen��wcslen���ֱ����ڴ��������ַ���
TCHAR g_szSharedRequestAndResultBuffer[1024];   

//�ͻ��˷���һ��������ַ�����������������
TCHAR g_szServerShutdown[] = TEXT("Server Shutdown");

//////////////////////////////////////////////////////////////////////////

//�������߳�ִ�д����
DWORD WINAPI ServerThread(PVOID pvParam)
{
	//��������߳�û��ֹͣ
	BOOL fShutdown = FALSE;

	while (!fShutdown)
	{
		//�ȴ��ͻ��߳��ύ����
		WaitForSingleObject(g_hevtRequestSubmitted, INFINITE);

		//����Ƿ�Ҫ�������򣨲��رնԻ���ʱ���������˳��ַ�����
		//������g_hMainDlg==NULL�����Է�ֹ�û��ֶ����롰Server Shutdown���ַ���
		//�����¸��߳��˳�������Ҳ�����û�������ַ��������˳���
		//_tcscmp�����ȽϿ��ַ���UNICODE
		fShutdown = (g_hMainDlg == NULL) && (_tcscmp(g_szSharedRequestAndResultBuffer, g_szServerShutdown) == 0);

		if (!fShutdown)
		{
			//����ͻ��̵߳�����
			_tcsrev(g_szSharedRequestAndResultBuffer);  //��ת�ַ���
		}

		//֪ͨ�ͻ��̣߳������̼߳��������
		SetEvent(g_hevtResultReturned);
	}

	//�ͻ��߳�Ҫ���˳�
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
BOOL  Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	chSETDLGICONS(hwnd, IDI_HANDSHAKE);

	//��ʼ���༭��
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

		//���ͻ�������ַ������빲������
		Edit_GetText(GetDlgItem(hwnd, IDC_REQUEST),
			g_szSharedRequestAndResultBuffer, _countof(g_szSharedRequestAndResultBuffer));
		//�ͻ��߳��ύ���󣬱�ʾ��������׼���á����ȴ������̷߳��ش�����
		SignalObjectAndWait(g_hevtRequestSubmitted, g_hevtResultReturned, INFINITE, FALSE);

		//��ʾ�����̵߳Ĵ�����
		Edit_SetText(GetDlgItem(hwnd, IDC_RESULT), g_szSharedRequestAndResultBuffer);
		break;
	}
}

//�Ի�����Ϣ������
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
	//��������ʼ��2��δ�������Զ��¼�����
	g_hevtRequestSubmitted = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_hevtResultReturned = CreateEvent(NULL, FALSE, FALSE, NULL);

	//���������߳�
	DWORD dwThreadID;
	HANDLE hThreadServer = chBEGINTHREADEX(NULL, 0, ServerThread, NULL, 0, &dwThreadID);

	/*
	INT_PTR DialogBox(          
	HINSTANCE hInstance,
    LPCTSTR lpTemplate,
    HWND hWndParent,
    DLGPROC lpDialogFunc
	);
	����������ݶԻ�����Դ������һ��ģʽ�Ի�������Ի���Ӧ����EndDialog��������
	hInstance ��ǰӦ�ó���ʵ�������
	lpTemplate ��ʶ�Ի���ģ����Դ��������ʹ�÷�ʽ��һ���ǰѶԻ���ģ���IDǿ��תΪLPCTSTR��һ�ֿ���ʹ��MAKEINTRESOURCE��õ���ʶID��
	hWndParent �����ڵľ����
	lpDialogFunc �Ի�����Ϣ��������
	*/

	//����UI�̣߳����߳�,Ҳ�ǿͻ��̣߳�
	DialogBox(hInstExe, MAKEINTRESOURCE(IDD_HANDSHAKE), NULL, Dlg_Proc);
	g_hMainDlg = NULL; //��ʾ�Ի����˳�

	//���߳�UI�߳����ڹرգ���ʱ�����߳̿��ܱ�������Wait*�����У����份�ѣ�
	//����д�˳��ַ������Ա��˳�
	_tcscpy_s(g_szSharedRequestAndResultBuffer, _countof(g_szSharedRequestAndResultBuffer), g_szServerShutdown);
	SetEvent(g_hevtRequestSubmitted);

	//�ȴ������߳��˳�
	HANDLE h[2];
	h[0] = g_hevtResultReturned;    //�����������ַ��߳�
	h[1] = hThreadServer;    //�������߳�
	WaitForMultipleObjects(2, h, TRUE, INFINITE);

	//�ر����еľ��
	CloseHandle(g_hevtResultReturned);
	CloseHandle(g_hevtRequestSubmitted);
	CloseHandle(hThreadServer);
	return 0;
}