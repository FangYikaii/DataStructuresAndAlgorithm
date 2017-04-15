/*
HANDLE CreateThread(
	LPSECURITY_ATTRIBUTES lpsa, //安全属性大小
	DWORD cbStack, //线程初始栈大小
	LPTHREAD_START_ROUTINE lpStartAddr,  //线程开始的位置
	LPVOID lpvThreadParam,  //接收线程过程函数的参数
	DWORD fdwCreate,  //创建线程时的标志
	LPDWORD lpIDThread, //保存线程的ID
);
-1-第一个参数是安全属性结构，主要控制该线程句柄是否可为进程的子进程继承使用，默认使用NULL时表示不能继承；若想继承线程句柄，则需要设置该结构体，将结构体的bInheritHandle成员初始化为TRUE；
-2-cbStack表示的线程初始栈的大小，若使用0则表示采用默认大小初始化；
-3-lpStartAddr表示线程开始的位置，即线程要执行的函数代码，这点有点类似于回调函数的使用；
-4-lpvThreadParam用来接收线程过程函数的参数，不需要时可以设置为NULL；
-5-fdwCreate表示创建线程时的标志，CREATE_SUSPENDED表示线程创建后挂起暂不执行，必须调用ResumeThread才可以执行，0表示线程创建之后立即执行
-6-lpIDThread用来保存线程的ID；
*/

/*
-1-CreateMutex创建一个互斥量：
HANDLE CreateMutex(
LPSECURITY_ATTRIBUTES lpMutexAttributes,
BOOL bInitialOwner,
LPCTSTR lpName
);
第一个参数同样是安全结构，默认是NULL不能继承句柄；第二个参数为FALSE时创建Mutex时不指定所有权，若为TRUE则指定为当前的创建线程ID为所有者，其他线程访问需要先ReleaseMutex；第三个参数用于设置Mutex名，后续我们会说明，为NULL时表示是匿名互斥量。
-2-WaitForSingleObject()：请求一个互斥量的访问权；
-3-ReleaseMutex()：释放一个互斥量的访问权；

*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int tickets = 100;
HANDLE hMutex;  //句柄--互斥量

//功能：线程1示例
//输入：接收线程过程函数的参数
//输出：线程初始栈大小
DWORD WINAPI Fun1Proc(LPVOID lpParameter);  


//功能：线程2示例
//输入：接收线程过程函数的参数
//输出：线程初始栈大小
DWORD WINAPI Fun2Proc(LPVOID lpParameter);

//功能：线程3示例
//输入：接收线程过程函数的参数
//输出：线程初始栈大小
DWORD WINAPI Fun3Proc(LPVOID lpParameter);


int _tmain(int argc, _TCHAR* argv[])
{
	///*
	//实例1
	//*/
	int j = 0;
	//定义线程1，初始化线程1
	//安全属性结构：NULL；初始栈大小:0；线程开始的位置：Fun1Proc；接收线程过程函数的参数：NULL;创建线程时的标志：0；保存线程的ID:NULL
	HANDLE hThread_1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	while (j++ < 1000)
	{
		cout << "MainThread is running for " << "the " << j << " times" << endl;
	}
	CloseHandle(hThread_1);
	system("pause");

	/*
	实例2:互斥量
	*/
	//定义线程1，初始化线程1
	//输入：（1）安全属性结构，能否继承句柄：NULL；(2)创建者是否拥有所有权，FALSE为没有所有权,遇到第一个WaitForSingleObject的时候就把所有权给它
	hMutex = CreateMutex(NULL, FALSE, NULL);  //实例化互斥量句柄，创建互斥量
	
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			cout << "Only one instance can run !" << endl;
			system("pause");
			return 0;
		}
	}

	//定义线程1，初始化线程1
	//安全属性结构：NULL；初始栈大小:0；线程开始的位置：Fun1Proc；接收线程过程函数的参数：NULL;创建线程时的标志：0；保存线程的ID:NULL
	HANDLE h_Thread_2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	HANDLE h_Thread_3 = CreateThread(NULL, 0, Fun3Proc, NULL, 0, NULL);
	Sleep(4000);        // 让2个线程有足够的时间执行完操作。
	CloseHandle(h_Thread_2);   //关闭线程2
	CloseHandle(h_Thread_3);   //关闭线程3
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
		参数：
		hHandle：指定对象或事件的句柄；
		dwMilliseconds: 等待时间，以毫妙为单位，当超过等待时间时，此函数将返回。如果该参数设置为0，则该函数立即返回，如果设置为INFINITE，则该函数直到有信号才返回。
		返回值：
		如果此函数成功，该函数的返回之标识了引起该函数返回的事件。返回值如下：
		WAIT_ABANDONED（0x00000080L）
		指定的对象是一个互斥对象，该对象没有被拥有该对象的线程在线程结束前释放。互斥对象的所有权被同意授予调用该函数的线程。互斥对象被设置成为无信号状态。
		WAIT_OBJECT_0 （0x00000000L）
		指定的对象出有有信号状态。
		WAIT_TIMEOUT （0x00000102L）
		超过等待时间，指定的对象处于无信号状态
		如果失败，返回 WAIT_FAILED；
		*/
		//WaitForSingleObject 函数用来检测 hHandle 事件的信号状态，当函数的执行时间超过 dwMilliseconds 就返回，
		//但如果参数 dwMilliseconds 为 INFINITE 时函数将直到相应时间事件变成有信号状态才返回，否则就一直等待下去，直到 WaitForSingleObject 有返回直才执行后面的代码。
		WaitForSingleObject(hMutex, INFINITE);  //infinite无限，等到函数有信号才返回
		if (tickets>0)
		{
			Sleep(10);        //执行挂起一段时间的用法
			cout << "Thread 2 sell ticket :" << tickets-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);   //释放互斥量
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
		ReleaseMutex(hMutex);   //释放互斥量
	}
	return 0;
}