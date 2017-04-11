#pragma once
#include <iostream>   //io流
#include <atlbase.h>  //ALT类
#include <atlsync.h>  //ALT类
#include <vector>

using namespace std;

class CMultiThreadTest
{
public:
	bool Init();                                         //初始化类成员
	bool UnInit();                                       //释放资源
	void NotifyDowork(const std::vector<int> &data);    //const std::vector<int> : 容器类
	
	static DWORD CALLBACK TestThread(LPVOID);            //线程函数，必须是静态函数
	DWORD TestProc();                                    //线程工作实现

private:
	std::vector<int> m_data;                             //同步数据
	ATL::CEvent m_NotifyEvent;                           //通知事件
	HANDLE m_hThread;                                    //线程句柄
};

bool CMultiThreadTest::Init()
{
	//创建事件
	BOOL bRet = m_NotifyEvent.Create(NULL, TRUE, FALSE, NULL);
	//如果创建事件失败
	if (!bRet)
	{
		return false;
	}

	//挂起的方式创建线程
	//输入：1.安全属性大小;2.线程初始栈大小;3.线程开始的位置4.接收线程过程函数的参数;5.创建线程时的标志;6.保存线程的ID
	m_hThread = CreateThread(NULL, 0, &CMultiThreadTest::TestThread, this, CREATE_SUSPENDED, NULL);
	if (NULL == m_hThread)
	{
		return false;
	}

	//唤醒线程
	ResumeThread(m_hThread);
	return true;
}

bool CMultiThreadTest::UnInit()
{
	//通知线程处理data数据
	//事件句柄值不为空
	if (m_NotifyEvent != NULL)
	{
		m_NotifyEvent.Set();
	}

	if (m_hThread != NULL)
	{
		//预留100ms让线程处理完数据，100ms是个估值
		WaitForSingleObject(m_hThread, 100);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	return true;
}

//线程入口，线程被唤醒后执行该函数
//线程函数：将lpParam转化为对象指针，执行对象的成员函数TestProc()
//功能：1.将线程函数逻辑和业务逻辑分离2.TestThread是静态函数，类静态函数只能处理类的静态成员变量，而很多时候我们希望线程处理类的非静态成员变量。
DWORD CALLBACK CMultiThreadTest::TestThread(LPVOID lpParam)
{
	if (lpParam == NULL)
	{
		return 0;
	}
	//将LPVOID转化为CMultiThreadTest类的指针，reinterpret_cast是一个危险的类型转换，一般只适用于指针和整数之间的转换。
	CMultiThreadTest *lpThis = reinterpret_cast<CMultiThreadTest*>(lpParam);
	return lpThis->TestProc();
}

//
DWORD CMultiThreadTest::TestProc()
{
	while (true)
	{
		//每5s监听一次，秒数直接影响程序的性能
		DWORD dwRet = WaitForSingleObject(m_NotifyEvent, 5000);

		//进入循环5s没有事件发生，不做任何处理
		if (dwRet == WAIT_TIMEOUT)
		{
			continue;
		}

		//打印数组
		for (unsigned int i = 0; i < m_data.size(); i++)
		{
			cout << m_data[i] << " ";
		}
		cout << endl;

		//重置事件
		m_NotifyEvent.Reset();
	}
	return 0;
}

//把外部传来的data赋值给类的非静态成员变量m_data
void CMultiThreadTest::NotifyDowork(const std::vector<int>&data)  //vector容器
{
	m_data = data;
	m_NotifyEvent.Set();  //通知线程处理m_data数据
}



