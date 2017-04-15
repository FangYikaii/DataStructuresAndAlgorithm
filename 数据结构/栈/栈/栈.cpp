// 栈.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SeqStack.h"
#include "BothStack.h"
#include "LinkStack.h"
/*
前置条件：栈不存在
输    入：无
功    能：栈的初始化
输    出：无
后置条件：构造一个空栈
*/
template <class T>
SeqStack<T>::SeqStack()
{
	top = -1;
}

/*
* 前置条件：栈已存在
* 输    入：无
* 功    能：销毁栈
* 输    出：无
* 后置条件：释放栈所占用的存储空间
*/
template <class T>
SeqStack<T>::~SeqStack()
{


}

/*
* 前置条件：栈已存在
* 输    入：元素值x
* 功    能：在栈顶插入一个元素x
* 输    出：如果插入不成功，抛出异常
* 后置条件：如果插入成功，栈顶增加了一个元素
*/
template <class T>
void SeqStack<T>::Push(T x)
{
	if (top == StackSize - 1)
		throw "上溢";
	top++;
	data[top] = x;
}

/*
* 前置条件：栈已存在
* 输    入：无
* 功    能：读取当前的栈顶元素
* 输    出：若栈不空，返回当前的栈顶元素值
* 后置条件：栈不变
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
* 前置条件：栈已存在
* 输    入：无
* 功    能：删除栈顶元素
* 输    出：如果删除成功，返回被删元素值，否则，抛出异常
* 后置条件：如果删除成功，栈顶减少了一个元素
*/
template<class T>
T SeqStack<T>::Pop()
{
	T x;
	if (top == -1)
		throw "下溢";
	x = data[top--];  //先弹出当前top元素，再--
	return x;
}

/*
* 前置条件：栈已存在
* 输    入：无
* 功    能：判断栈是否为空
* 输    出：如果栈为空，返回1，否则，返回0
* 后置条件：栈不变
*/
template <class T>
bool SeqStack<T>::Empty()
{
	if (top == -1)
		return 1;  //空
	else
		return 0;  //非空
}


/*
* 前置条件：栈不存在
* 输    入：无
* 功    能：栈的初始化
* 输    出：无
* 后置条件：构造一个空栈
*/
template <class TT>
BothStack<TT>::BothStack()
{
	top1 = -1;   //一个在栈底
	top2 = BothStackSize;      //一个在栈顶
}


/*
* 前置条件：共享空间已存在
* 输    入：无
* 功    能：销毁两栈共享的数组空间
* 输    出：无
* 后置条件：将两栈共享的数组空间释放
*/
template<class TT>
BothStack<TT>::~BothStack()
{
}

/*
* 前置条件：共享空间已存在
* 输    入：栈号i，元素值x
* 功    能：在栈i顶插入一个元素x
* 输    出：若插入不成功，则抛出插入异常
* 后置条件：若插入成功，则栈i顶插入了一个栈顶元素
*/
template <class TT>
void BothStack<TT>::Push(int i, TT x)
{
	if (top1 == top2 - 1)   //也就是已经满了，top1，top2隔了1个
		throw "上溢";
	if (i == 1)
		data[++top1] = x;     //先top1++（升上去[左]），再把x装入data[top1]
	if (i == 2)
		data[--top2] = x;   //先top2--（退回去[右]），再把x装入data[top2]
}

/*
* 前置条件：共享空间已存在
* 输    入：栈号i
* 功    能：在栈i中删除栈顶元素
* 输    出：若删除不成功，则抛出删除异常
* 后置条件：若删除成功，则栈i中删除了栈顶元素
*/
template <class TT>
TT BothStack<TT>::Pop(int i)
{
	//将栈1的栈顶元素出栈
	if (i==1)
	{	
		if (top == -1)
			throw "下溢";
		return data[top1--];    //返回弹出的元素：原来的data[top1]，然后top1--
	}
	//将栈2的栈顶元素出栈
	if (i == 2)
	{
		if (top2 == BothStackSize)
			throw "下溢";
		return data[top2++];      //返回弹出的元素，原来的data[top2],然后top2++，退回去

	}
}


/*
* 前置条件：共享空间已存在
* 输    入：栈号i
* 功    能：读取栈i当前的栈顶元素
* 输    出：若栈i不空，返回栈i当前的栈顶元素值
* 后置条件：两栈均不变
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
* 前置条件：共享空间已存在
* 输    入：栈号i
* 功    能：判断栈i是否为空栈
* 输    出：若栈i为空栈，返回0；否则返回1
* 后置条件：两栈均不变
*/
template<class TT>
bool BothStack<TT>::Empty(int i)
{
	if (i == 1)
	{
		if (top1 == -1)
			return 0;    //空栈，返回0
		else
			return 1;      //非空，返回1
	}
	if (i == 2)
	{
		if (top2 == StackSize)
			return 0;        //空栈，返回0
		else
			return 1;       //非空，返回1
	}
}

///////////////链栈--链表一样的栈
/*
* 前置条件：栈不存在
* 输    入：无
* 功    能：栈的初始化
* 输    出：无
* 后置条件：构造一个空栈
*/
template<class TTT>
LinkStack<TTT>::LinkStack()
{
	top = NULL;
}

/*
* 前置条件：栈已存在
* 输    入：无
* 功    能：销毁栈
* 输    出：无
* 后置条件：释放栈所占用的存储空间
*/
template <class TTT>
LinkStack<TTT>::~LinkStack()
{
	//若还有节点
	while (top)
	{
		Node<TTT> *p;   //定义一个Node节点的指针（空）
		p = top->next;  //top的next（小一位）指向新的p（第二top）
		delete top;   //删除top的节点Node
		top = p;      //把p设为top
	}
}

/*
* 前置条件：栈已存在
* 输    入：节点s
* 功    能：在栈顶插入该节点
* 输    出：无
* 后置条件：如果插入成功，栈顶增加了一个元素
*/
template<class TTT>
void LinkStack<TTT>::Push(TTT x)
{
	Node<TTT> *s;
	s = new Node < TTT > ;   //new一个Node节点的指针
	s->data = x;      //申请一个x的数据域的给该节点
	s->next = top;    //s的next（小一位）指向top
	top = s;      //将节点s插在栈顶
}


/*
* 前置条件：栈已存在
* 输    入：无
* 功    能：删除栈顶元素
* 输    出：如果删除成功，返回被删元素值，否则，抛出异常
* 后置条件：如果删除成功，栈顶减少了一个元素
*/
template <class TTT>
TTT LinkStack<TTT>::Pop()
{
	Node<TTT> *p;           //初始化一个Node指针
	int x;
	if (top == NULL)      //如果栈为空
		throw "下溢";
	
	x = top->data;      //暂存栈顶元素
	p = top;           
	top = top->next;   //将栈顶节点摘链（top为前top指向下一个的值)
	delete p;
	return x;       //返回弹出元素
}

/*
* 前置条件：栈已存在
* 输    入：无
* 功    能：读取当前的栈顶元素
* 输    出：若栈不空，返回当前的栈顶元素值
* 后置条件：栈不变
*/
template <class TTT>
TTT LinkStack<TTT>::GetPop()
{
	if (top != NULL)
		return top->data;
}

/*
* 前置条件：栈已存在
* 输    入：无
* 功    能：判断栈是否为空
* 输    出：如果栈为空，返回1，否则，返回0
* 后置条件：栈不变
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

