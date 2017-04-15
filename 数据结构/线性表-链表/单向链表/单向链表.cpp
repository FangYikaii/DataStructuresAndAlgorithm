// 单向链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

template<class T>
class slistNode
{
public:
	slistNode()         //构造函数
	{
		next = NULL; 
	}
	T data;             //值域
	slistNode* next;    //指针域
};


template<class T>
class mylist
{
private:
	unsigned int listlength;     //链表长度
	slistNode<T>* node;          //临时节点
	slistNode<T>* lastnode;      //头结点
	slistNode<T>* headnode;      //尾节点
public:
	mylist();                    //初始化
	unsigned int length();       //链表元素的个数
	void add(T x);               //表尾添加元素
	void traversal();            //遍历整个链表并打印
	bool isEmpty();              //判断链表是否为空
	slistNode<T>* find(T x);     //查找第一个值为x的节点，返回节点的地址，找不到返回NULL
	void Delete(T x);            //删除第一个值为x的节点
	void insert(T x, slistNode<T>* p);   //在p节点后插入值为x的节点
	void insertHead(T x);		 //在链表的头部插入节点
};

template<class T>
mylist<T>::mylist()
{
	node = NULL;             //临时节点=NULL
	lastnode = NULL;         //头节点=NULL
	headnode = NULL;         //尾节点=NULL
	listlength = 0;          //长度
}

template<class T>
void mylist<T>::add(T x)
{
	node = new slistNode<T>();  //申请一个节点
	node->data = x;             //为节点赋值
	if (lastnode == NULL)       //如果没有尾节点，则链表为空，node既为头结点，也是尾节点
	{
		headnode = node;        
		lastnode = node;
	}
	else
	{
		lastnode->next = node;  //node既为尾节点的下一个节点
		lastnode = node;        //把尾节点赋值为node
	}
	++listlength;               //元素个数+1
}

template<class T>
void mylist<T>::traversal()
{
	node = headnode;          //临时节点指向头节点
	//遍历链表并输出
	while (node != NULL)
	{
		cout << node->data << endl;     //节点的数据输出
		node = node->next;
	}
	cout << endl;
}


template<class T>
bool mylist<T>::isEmpty()
{
	return listlength == 0;          //判断链表是否为空，返回真为空，假不为空
}


template<class T>
slistNode<T>* mylist<T>::find(T x)
{
	node = headnode;             //用临时节点指向头节点
	while (node != NULL&&node->data != x)   //遍历链表，遇到值相同的节点跳出
	{
		node = node->next;
	}
	return node;              //返回找到的节点的地址，如果没有找到则返回NULL
}


template<class T>
void mylist<T>::Delete(T x)
{
	slistNode<T>* temp = headnode;   //申请一个临时节点指向头指针
	if (temp == NULL)             //如果节点为空，则表示该链表无元素，可以直接返回
		return;
	if (temp->data == x)          //如果头节点的值为要删除的值，则删除头结点
	{
		headnode = temp->next;      //把头结点指向头结点的下一个节点
		if (temp->next == NULL)    //如果链表中只有一个节点，删除后就没有节点了，把尾节点置为空
			lastnode = NULL;
		delete(temp);               //删除头节点
		return;
	}
	while (temp->next != NULL&&temp->next->data != x)  //遍历链表找到第一个值与x相等的节点，temp表示这个节点的上一个节点
	{
		temp = temp->next;
	}
	if (temp->next == NULL)         //如果没有找到则返回
		return;
	if (temp->next == lastnode)                //如果找到的是尾节点
	{
		lastnode = temp;                    //把尾节点指向它的上一个节点
		delete(temp->next);                //删除尾节点
		temp->next = NULL;
	}
	else  //如果不是尾节点
	{
		node = temp->next;          //用临时节点node指向要删除的节点
		temp->next = node->next;     //要删除的节点的上一个节点指向要删除节点的下一个节点
		delete(node);
		node = NULL;
	}
}

template<class T>
void mylist<T>::insert(T x, slistNode<T>* p)
{
	if (p == NULL)
		return;
	node = new slistNode<T>();      //申请一个内存空间
	node->data = x;
	node->next = p->next;
	p->next = node;
	if (node->next == NULL)         //如果node为尾节点
		lastnode = node;
}

template<class T>
void mylist<T>::insertHead(T x)
{
	node = new slistNode<T>();
	node->data = x;
	node->next = headnode;
	headnode = node;
}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

