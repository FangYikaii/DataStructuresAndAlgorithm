
#include "stdafx.h"
#include "Thread.h"
#include <windows.h>
#include "time.h"
#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{
	CMultiThreadTest multiThreadTest;

	//��ʼ��ʧ��
	if (!multiThreadTest.Init())   //������Դ
	{
		return 0;
	}

	//(unsigned)time( NULL )��ȡ��ǰ��ʱ�䣨��1970�굽���ڵ�ʱ�������������޷���������
	//ͨ��srand(����)�����������������
	srand(unsigned int(time(NULL)));
	//vector������ʼ��
	std::vector<int> data;

	while (true)
	{
		data.clear();

		//����10�������
		for (int i = 0; i < 10; i++)
		{
			data.push_back(rand() % 1000);
		}
		//֪ͨ���߳���ִ�й���
		multiThreadTest.NotifyDowork(data);
		Sleep(2000);
	}

	multiThreadTest.UnInit();   //�ͷ���Դ
	return 0;
}

