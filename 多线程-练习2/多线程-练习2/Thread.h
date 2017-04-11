#pragma once
#include <iostream>   //io��
#include <atlbase.h>  //ALT��
#include <atlsync.h>  //ALT��
#include <vector>

using namespace std;

class CMultiThreadTest
{
public:
	bool Init();                                         //��ʼ�����Ա
	bool UnInit();                                       //�ͷ���Դ
	void NotifyDowork(const std::vector<int> &data);    //const std::vector<int> : ������
	
	static DWORD CALLBACK TestThread(LPVOID);            //�̺߳����������Ǿ�̬����
	DWORD TestProc();                                    //�̹߳���ʵ��

private:
	std::vector<int> m_data;                             //ͬ������
	ATL::CEvent m_NotifyEvent;                           //֪ͨ�¼�
	HANDLE m_hThread;                                    //�߳̾��
};

bool CMultiThreadTest::Init()
{
	//�����¼�
	BOOL bRet = m_NotifyEvent.Create(NULL, TRUE, FALSE, NULL);
	//��������¼�ʧ��
	if (!bRet)
	{
		return false;
	}

	//����ķ�ʽ�����߳�
	//���룺1.��ȫ���Դ�С;2.�̳߳�ʼջ��С;3.�߳̿�ʼ��λ��4.�����̹߳��̺����Ĳ���;5.�����߳�ʱ�ı�־;6.�����̵߳�ID
	m_hThread = CreateThread(NULL, 0, &CMultiThreadTest::TestThread, this, CREATE_SUSPENDED, NULL);
	if (NULL == m_hThread)
	{
		return false;
	}

	//�����߳�
	ResumeThread(m_hThread);
	return true;
}

bool CMultiThreadTest::UnInit()
{
	//֪ͨ�̴߳���data����
	//�¼����ֵ��Ϊ��
	if (m_NotifyEvent != NULL)
	{
		m_NotifyEvent.Set();
	}

	if (m_hThread != NULL)
	{
		//Ԥ��100ms���̴߳��������ݣ�100ms�Ǹ���ֵ
		WaitForSingleObject(m_hThread, 100);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	return true;
}

//�߳���ڣ��̱߳����Ѻ�ִ�иú���
//�̺߳�������lpParamת��Ϊ����ָ�룬ִ�ж���ĳ�Ա����TestProc()
//���ܣ�1.���̺߳����߼���ҵ���߼�����2.TestThread�Ǿ�̬�������ྲ̬����ֻ�ܴ�����ľ�̬��Ա���������ܶ�ʱ������ϣ���̴߳�����ķǾ�̬��Ա������
DWORD CALLBACK CMultiThreadTest::TestThread(LPVOID lpParam)
{
	if (lpParam == NULL)
	{
		return 0;
	}
	//��LPVOIDת��ΪCMultiThreadTest���ָ�룬reinterpret_cast��һ��Σ�յ�����ת����һ��ֻ������ָ�������֮���ת����
	CMultiThreadTest *lpThis = reinterpret_cast<CMultiThreadTest*>(lpParam);
	return lpThis->TestProc();
}

//
DWORD CMultiThreadTest::TestProc()
{
	while (true)
	{
		//ÿ5s����һ�Σ�����ֱ��Ӱ����������
		DWORD dwRet = WaitForSingleObject(m_NotifyEvent, 5000);

		//����ѭ��5sû���¼������������κδ���
		if (dwRet == WAIT_TIMEOUT)
		{
			continue;
		}

		//��ӡ����
		for (unsigned int i = 0; i < m_data.size(); i++)
		{
			cout << m_data[i] << " ";
		}
		cout << endl;

		//�����¼�
		m_NotifyEvent.Reset();
	}
	return 0;
}

//���ⲿ������data��ֵ����ķǾ�̬��Ա����m_data
void CMultiThreadTest::NotifyDowork(const std::vector<int>&data)  //vector����
{
	m_data = data;
	m_NotifyEvent.Set();  //֪ͨ�̴߳���m_data����
}



