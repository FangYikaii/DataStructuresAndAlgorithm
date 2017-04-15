
#include "stdafx.h"
#include "Thread.h"
#include <windows.h>
#include "time.h"
#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{
	CMultiThreadTest multiThreadTest;

	//初始化失败
	if (!multiThreadTest.Init())   //创建资源
	{
		return 0;
	}

	//(unsigned)time( NULL )是取当前的时间（从1970年到现在的时间秒数）化成无符号整数。
	//通过srand(参数)设置随机数序列种子
	srand(unsigned int(time(NULL)));
	//vector容器初始化
	std::vector<int> data;

	while (true)
	{
		data.clear();

		//产生10个随机数
		for (int i = 0; i < 10; i++)
		{
			data.push_back(rand() % 1000);
		}
		//通知多线程类执行工作
		multiThreadTest.NotifyDowork(data);
		Sleep(2000);
	}

	multiThreadTest.UnInit();   //释放资源
	return 0;
}

