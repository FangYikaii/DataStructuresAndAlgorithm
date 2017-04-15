// ջ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "SeqStack.h"
#include "BothStack.h"
#include "LinkStack.h"
/*
ǰ��������ջ������
��    �룺��
��    �ܣ�ջ�ĳ�ʼ��
��    ������
��������������һ����ջ
*/
template <class T>
SeqStack<T>::SeqStack()
{
	top = -1;
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ�����ջ
* ��    ������
* �����������ͷ�ջ��ռ�õĴ洢�ռ�
*/
template <class T>
SeqStack<T>::~SeqStack()
{


}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺Ԫ��ֵx
* ��    �ܣ���ջ������һ��Ԫ��x
* ��    ����������벻�ɹ����׳��쳣
* �����������������ɹ���ջ��������һ��Ԫ��
*/
template <class T>
void SeqStack<T>::Push(T x)
{
	if (top == StackSize - 1)
		throw "����";
	top++;
	data[top] = x;
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ���ȡ��ǰ��ջ��Ԫ��
* ��    ������ջ���գ����ص�ǰ��ջ��Ԫ��ֵ
* ����������ջ����
*/
template<class T>
T SeqStack<T>::GetTop()
{
	if (top != -1)
	{
		return data[top];
	}
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ�ɾ��ջ��Ԫ��
* ��    �������ɾ���ɹ������ر�ɾԪ��ֵ�������׳��쳣
* �������������ɾ���ɹ���ջ��������һ��Ԫ��
*/
template<class T>
T SeqStack<T>::Pop()
{
	T x;
	if (top == -1)
		throw "����";
	x = data[top--];  //�ȵ�����ǰtopԪ�أ���--
	return x;
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ��ж�ջ�Ƿ�Ϊ��
* ��    �������ջΪ�գ�����1�����򣬷���0
* ����������ջ����
*/
template <class T>
bool SeqStack<T>::Empty()
{
	if (top == -1)
		return 1;  //��
	else
		return 0;  //�ǿ�
}


/*
* ǰ��������ջ������
* ��    �룺��
* ��    �ܣ�ջ�ĳ�ʼ��
* ��    ������
* ��������������һ����ջ
*/
template <class TT>
BothStack<TT>::BothStack()
{
	top1 = -1;   //һ����ջ��
	top2 = BothStackSize;      //һ����ջ��
}


/*
* ǰ������������ռ��Ѵ���
* ��    �룺��
* ��    �ܣ�������ջ���������ռ�
* ��    ������
* ��������������ջ���������ռ��ͷ�
*/
template<class TT>
BothStack<TT>::~BothStack()
{
}

/*
* ǰ������������ռ��Ѵ���
* ��    �룺ջ��i��Ԫ��ֵx
* ��    �ܣ���ջi������һ��Ԫ��x
* ��    ���������벻�ɹ������׳������쳣
* ����������������ɹ�����ջi��������һ��ջ��Ԫ��
*/
template <class TT>
void BothStack<TT>::Push(int i, TT x)
{
	if (top1 == top2 - 1)   //Ҳ�����Ѿ����ˣ�top1��top2����1��
		throw "����";
	if (i == 1)
		data[++top1] = x;     //��top1++������ȥ[��]�����ٰ�xװ��data[top1]
	if (i == 2)
		data[--top2] = x;   //��top2--���˻�ȥ[��]�����ٰ�xװ��data[top2]
}

/*
* ǰ������������ռ��Ѵ���
* ��    �룺ջ��i
* ��    �ܣ���ջi��ɾ��ջ��Ԫ��
* ��    ������ɾ�����ɹ������׳�ɾ���쳣
* ������������ɾ���ɹ�����ջi��ɾ����ջ��Ԫ��
*/
template <class TT>
TT BothStack<TT>::Pop(int i)
{
	//��ջ1��ջ��Ԫ�س�ջ
	if (i==1)
	{	
		if (top == -1)
			throw "����";
		return data[top1--];    //���ص�����Ԫ�أ�ԭ����data[top1]��Ȼ��top1--
	}
	//��ջ2��ջ��Ԫ�س�ջ
	if (i == 2)
	{
		if (top2 == BothStackSize)
			throw "����";
		return data[top2++];      //���ص�����Ԫ�أ�ԭ����data[top2],Ȼ��top2++���˻�ȥ

	}
}


/*
* ǰ������������ռ��Ѵ���
* ��    �룺ջ��i
* ��    �ܣ���ȡջi��ǰ��ջ��Ԫ��
* ��    ������ջi���գ�����ջi��ǰ��ջ��Ԫ��ֵ
* ������������ջ������
*/
template <class TT>
TT BothStack<TT>::GetTop(int i)
{
	if (i == 1)
	{
		if (top != -1)
			return data[top1];
	}
	if (i == 2)
	{
		if (top2 != BothStackSize)
			return data[top2];
	}
}

/*
* ǰ������������ռ��Ѵ���
* ��    �룺ջ��i
* ��    �ܣ��ж�ջi�Ƿ�Ϊ��ջ
* ��    ������ջiΪ��ջ������0�����򷵻�1
* ������������ջ������
*/
template<class TT>
bool BothStack<TT>::Empty(int i)
{
	if (i == 1)
	{
		if (top1 == -1)
			return 0;    //��ջ������0
		else
			return 1;      //�ǿգ�����1
	}
	if (i == 2)
	{
		if (top2 == StackSize)
			return 0;        //��ջ������0
		else
			return 1;       //�ǿգ�����1
	}
}

///////////////��ջ--����һ����ջ
/*
* ǰ��������ջ������
* ��    �룺��
* ��    �ܣ�ջ�ĳ�ʼ��
* ��    ������
* ��������������һ����ջ
*/
template<class TTT>
LinkStack<TTT>::LinkStack()
{
	top = NULL;
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ�����ջ
* ��    ������
* �����������ͷ�ջ��ռ�õĴ洢�ռ�
*/
template <class TTT>
LinkStack<TTT>::~LinkStack()
{
	//�����нڵ�
	while (top)
	{
		Node<TTT> *p;   //����һ��Node�ڵ��ָ�루�գ�
		p = top->next;  //top��next��Сһλ��ָ���µ�p���ڶ�top��
		delete top;   //ɾ��top�Ľڵ�Node
		top = p;      //��p��Ϊtop
	}
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺�ڵ�s
* ��    �ܣ���ջ������ýڵ�
* ��    ������
* �����������������ɹ���ջ��������һ��Ԫ��
*/
template<class TTT>
void LinkStack<TTT>::Push(TTT x)
{
	Node<TTT> *s;
	s = new Node < TTT > ;   //newһ��Node�ڵ��ָ��
	s->data = x;      //����һ��x��������ĸ��ýڵ�
	s->next = top;    //s��next��Сһλ��ָ��top
	top = s;      //���ڵ�s����ջ��
}


/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ�ɾ��ջ��Ԫ��
* ��    �������ɾ���ɹ������ر�ɾԪ��ֵ�������׳��쳣
* �������������ɾ���ɹ���ջ��������һ��Ԫ��
*/
template <class TTT>
TTT LinkStack<TTT>::Pop()
{
	Node<TTT> *p;           //��ʼ��һ��Nodeָ��
	int x;
	if (top == NULL)      //���ջΪ��
		throw "����";
	
	x = top->data;      //�ݴ�ջ��Ԫ��
	p = top;           
	top = top->next;   //��ջ���ڵ�ժ����topΪǰtopָ����һ����ֵ)
	delete p;
	return x;       //���ص���Ԫ��
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ���ȡ��ǰ��ջ��Ԫ��
* ��    ������ջ���գ����ص�ǰ��ջ��Ԫ��ֵ
* ����������ջ����
*/
template <class TTT>
TTT LinkStack<TTT>::GetPop()
{
	if (top != NULL)
		return top->data;
}

/*
* ǰ��������ջ�Ѵ���
* ��    �룺��
* ��    �ܣ��ж�ջ�Ƿ�Ϊ��
* ��    �������ջΪ�գ�����1�����򣬷���0
* ����������ջ����
*/
template <class TTT>
bool LinkStack<TTT>::Empty()
{
	if (top == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

