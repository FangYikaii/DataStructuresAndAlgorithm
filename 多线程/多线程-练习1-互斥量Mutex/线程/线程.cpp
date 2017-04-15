/*
HANDLE CreateThread(
	LPSECURITY_ATTRIBUTES lpsa, //��ȫ���Դ�С
	DWORD cbStack, //�̳߳�ʼջ��С
	LPTHREAD_START_ROUTINE lpStartAddr,  //�߳̿�ʼ��λ��
	LPVOID lpvThreadParam,  //�����̹߳��̺����Ĳ���
	DWORD fdwCreate,  //�����߳�ʱ�ı�־
	LPDWORD lpIDThread, //�����̵߳�ID
);
-1-��һ�������ǰ�ȫ���Խṹ����Ҫ���Ƹ��߳̾���Ƿ��Ϊ���̵��ӽ��̼̳�ʹ�ã�Ĭ��ʹ��NULLʱ��ʾ���ܼ̳У�����̳��߳̾��������Ҫ���øýṹ�壬���ṹ���bInheritHandle��Ա��ʼ��ΪTRUE��
-2-cbStack��ʾ���̳߳�ʼջ�Ĵ�С����ʹ��0���ʾ����Ĭ�ϴ�С��ʼ����
-3-lpStartAddr��ʾ�߳̿�ʼ��λ�ã����߳�Ҫִ�еĺ������룬����е������ڻص�������ʹ�ã�
-4-lpvThreadParam���������̹߳��̺����Ĳ���������Ҫʱ��������ΪNULL��
-5-fdwCreate��ʾ�����߳�ʱ�ı�־��CREATE_SUSPENDED��ʾ�̴߳���������ݲ�ִ�У��������ResumeThread�ſ���ִ�У�0��ʾ�̴߳���֮������ִ��
-6-lpIDThread���������̵߳�ID��
*/

/*
-1-CreateMutex����һ����������
HANDLE CreateMutex(
LPSECURITY_ATTRIBUTES lpMutexAttributes,
BOOL bInitialOwner,
LPCTSTR lpName
);
��һ������ͬ���ǰ�ȫ�ṹ��Ĭ����NULL���ܼ̳о�����ڶ�������ΪFALSEʱ����Mutexʱ��ָ������Ȩ����ΪTRUE��ָ��Ϊ��ǰ�Ĵ����߳�IDΪ�����ߣ������̷߳�����Ҫ��ReleaseMutex��������������������Mutex�����������ǻ�˵����ΪNULLʱ��ʾ��������������
-2-WaitForSingleObject()������һ���������ķ���Ȩ��
-3-ReleaseMutex()���ͷ�һ���������ķ���Ȩ��

*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int tickets = 100;
HANDLE hMutex;  //���--������

//���ܣ��߳�1ʾ��
//���룺�����̹߳��̺����Ĳ���
//������̳߳�ʼջ��С
DWORD WINAPI Fun1Proc(LPVOID lpParameter);  


//���ܣ��߳�2ʾ��
//���룺�����̹߳��̺����Ĳ���
//������̳߳�ʼջ��С
DWORD WINAPI Fun2Proc(LPVOID lpParameter);

//���ܣ��߳�3ʾ��
//���룺�����̹߳��̺����Ĳ���
//������̳߳�ʼջ��С
DWORD WINAPI Fun3Proc(LPVOID lpParameter);


int _tmain(int argc, _TCHAR* argv[])
{
	///*
	//ʵ��1
	//*/
	int j = 0;
	//�����߳�1����ʼ���߳�1
	//��ȫ���Խṹ��NULL����ʼջ��С:0���߳̿�ʼ��λ�ã�Fun1Proc�������̹߳��̺����Ĳ�����NULL;�����߳�ʱ�ı�־��0�������̵߳�ID:NULL
	HANDLE hThread_1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	while (j++ < 1000)
	{
		cout << "MainThread is running for " << "the " << j << " times" << endl;
	}
	CloseHandle(hThread_1);
	system("pause");

	/*
	ʵ��2:������
	*/
	//�����߳�1����ʼ���߳�1
	//���룺��1����ȫ���Խṹ���ܷ�̳о����NULL��(2)�������Ƿ�ӵ������Ȩ��FALSEΪû������Ȩ,������һ��WaitForSingleObject��ʱ��Ͱ�����Ȩ����
	hMutex = CreateMutex(NULL, FALSE, NULL);  //ʵ�������������������������
	
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			cout << "Only one instance can run !" << endl;
			system("pause");
			return 0;
		}
	}

	//�����߳�1����ʼ���߳�1
	//��ȫ���Խṹ��NULL����ʼջ��С:0���߳̿�ʼ��λ�ã�Fun1Proc�������̹߳��̺����Ĳ�����NULL;�����߳�ʱ�ı�־��0�������̵߳�ID:NULL
	HANDLE h_Thread_2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	HANDLE h_Thread_3 = CreateThread(NULL, 0, Fun3Proc, NULL, 0, NULL);
	Sleep(4000);        // ��2���߳����㹻��ʱ��ִ���������
	CloseHandle(h_Thread_2);   //�ر��߳�2
	CloseHandle(h_Thread_3);   //�ر��߳�3
	system("pause");	 
	return 0;
}

DWORD WINAPI Fun1Proc(LPVOID lpParameter)
{
	int i = 0;
	while (i++ < 1000)
		cout << "Thread 1 is running for" << " the " << i << " times " << endl;

	return 0;
}

DWORD WINAPI Fun2Proc(LPVOID lpParamter)
{
	while (true)
	{
		/*
		DWORD WaitForSingleObject
		(
			HANDLE hHandle,
			DWORD dwMilliseconds
		);
		������
		hHandle��ָ��������¼��ľ����
		dwMilliseconds: �ȴ�ʱ�䣬�Ժ���Ϊ��λ���������ȴ�ʱ��ʱ���˺��������ء�����ò�������Ϊ0����ú����������أ��������ΪINFINITE����ú���ֱ�����źŲŷ��ء�
		����ֵ��
		����˺����ɹ����ú����ķ���֮��ʶ������ú������ص��¼�������ֵ���£�
		WAIT_ABANDONED��0x00000080L��
		ָ���Ķ�����һ��������󣬸ö���û�б�ӵ�иö�����߳����߳̽���ǰ�ͷš�������������Ȩ��ͬ��������øú������̡߳�����������ó�Ϊ���ź�״̬��
		WAIT_OBJECT_0 ��0x00000000L��
		ָ���Ķ���������ź�״̬��
		WAIT_TIMEOUT ��0x00000102L��
		�����ȴ�ʱ�䣬ָ���Ķ��������ź�״̬
		���ʧ�ܣ����� WAIT_FAILED��
		*/
		//WaitForSingleObject ����������� hHandle �¼����ź�״̬����������ִ��ʱ�䳬�� dwMilliseconds �ͷ��أ�
		//��������� dwMilliseconds Ϊ INFINITE ʱ������ֱ����Ӧʱ���¼�������ź�״̬�ŷ��أ������һֱ�ȴ���ȥ��ֱ�� WaitForSingleObject �з���ֱ��ִ�к���Ĵ��롣
		WaitForSingleObject(hMutex, INFINITE);  //infinite���ޣ��ȵ��������źŲŷ���
		if (tickets>0)
		{
			Sleep(10);        //ִ�й���һ��ʱ����÷�
			cout << "Thread 2 sell ticket :" << tickets-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);   //�ͷŻ�����
	}
	return 0;
}

DWORD WINAPI Fun3Proc(LPVOID lpParameter)
{
	while (true)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets>0)
		{
			Sleep(10);
			cout << "Thread 3 sell ticket:" << tickets-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);   //�ͷŻ�����
	}
	return 0;
}