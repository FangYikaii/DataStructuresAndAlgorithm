// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

template<class T>
class slistNode
{
public:
	slistNode()         //���캯��
	{
		next = NULL; 
	}
	T data;             //ֵ��
	slistNode* next;    //ָ����
};


template<class T>
class mylist
{
private:
	unsigned int listlength;     //������
	slistNode<T>* node;          //��ʱ�ڵ�
	slistNode<T>* lastnode;      //ͷ���
	slistNode<T>* headnode;      //β�ڵ�
public:
	mylist();                    //��ʼ��
	unsigned int length();       //����Ԫ�صĸ���
	void add(T x);               //��β���Ԫ��
	void traversal();            //��������������ӡ
	bool isEmpty();              //�ж������Ƿ�Ϊ��
	slistNode<T>* find(T x);     //���ҵ�һ��ֵΪx�Ľڵ㣬���ؽڵ�ĵ�ַ���Ҳ�������NULL
	void Delete(T x);            //ɾ����һ��ֵΪx�Ľڵ�
	void insert(T x, slistNode<T>* p);   //��p�ڵ�����ֵΪx�Ľڵ�
	void insertHead(T x);		 //�������ͷ������ڵ�
};

template<class T>
mylist<T>::mylist()
{
	node = NULL;             //��ʱ�ڵ�=NULL
	lastnode = NULL;         //ͷ�ڵ�=NULL
	headnode = NULL;         //β�ڵ�=NULL
	listlength = 0;          //����
}

template<class T>
void mylist<T>::add(T x)
{
	node = new slistNode<T>();  //����һ���ڵ�
	node->data = x;             //Ϊ�ڵ㸳ֵ
	if (lastnode == NULL)       //���û��β�ڵ㣬������Ϊ�գ�node��Ϊͷ��㣬Ҳ��β�ڵ�
	{
		headnode = node;        
		lastnode = node;
	}
	else
	{
		lastnode->next = node;  //node��Ϊβ�ڵ����һ���ڵ�
		lastnode = node;        //��β�ڵ㸳ֵΪnode
	}
	++listlength;               //Ԫ�ظ���+1
}

template<class T>
void mylist<T>::traversal()
{
	node = headnode;          //��ʱ�ڵ�ָ��ͷ�ڵ�
	//�����������
	while (node != NULL)
	{
		cout << node->data << endl;     //�ڵ���������
		node = node->next;
	}
	cout << endl;
}


template<class T>
bool mylist<T>::isEmpty()
{
	return listlength == 0;          //�ж������Ƿ�Ϊ�գ�������Ϊ�գ��ٲ�Ϊ��
}


template<class T>
slistNode<T>* mylist<T>::find(T x)
{
	node = headnode;             //����ʱ�ڵ�ָ��ͷ�ڵ�
	while (node != NULL&&node->data != x)   //������������ֵ��ͬ�Ľڵ�����
	{
		node = node->next;
	}
	return node;              //�����ҵ��Ľڵ�ĵ�ַ�����û���ҵ��򷵻�NULL
}


template<class T>
void mylist<T>::Delete(T x)
{
	slistNode<T>* temp = headnode;   //����һ����ʱ�ڵ�ָ��ͷָ��
	if (temp == NULL)             //����ڵ�Ϊ�գ����ʾ��������Ԫ�أ�����ֱ�ӷ���
		return;
	if (temp->data == x)          //���ͷ�ڵ��ֵΪҪɾ����ֵ����ɾ��ͷ���
	{
		headnode = temp->next;      //��ͷ���ָ��ͷ������һ���ڵ�
		if (temp->next == NULL)    //���������ֻ��һ���ڵ㣬ɾ�����û�нڵ��ˣ���β�ڵ���Ϊ��
			lastnode = NULL;
		delete(temp);               //ɾ��ͷ�ڵ�
		return;
	}
	while (temp->next != NULL&&temp->next->data != x)  //���������ҵ���һ��ֵ��x��ȵĽڵ㣬temp��ʾ����ڵ����һ���ڵ�
	{
		temp = temp->next;
	}
	if (temp->next == NULL)         //���û���ҵ��򷵻�
		return;
	if (temp->next == lastnode)                //����ҵ�����β�ڵ�
	{
		lastnode = temp;                    //��β�ڵ�ָ��������һ���ڵ�
		delete(temp->next);                //ɾ��β�ڵ�
		temp->next = NULL;
	}
	else  //�������β�ڵ�
	{
		node = temp->next;          //����ʱ�ڵ�nodeָ��Ҫɾ���Ľڵ�
		temp->next = node->next;     //Ҫɾ���Ľڵ����һ���ڵ�ָ��Ҫɾ���ڵ����һ���ڵ�
		delete(node);
		node = NULL;
	}
}

template<class T>
void mylist<T>::insert(T x, slistNode<T>* p)
{
	if (p == NULL)
		return;
	node = new slistNode<T>();      //����һ���ڴ�ռ�
	node->data = x;
	node->next = p->next;
	p->next = node;
	if (node->next == NULL)         //���nodeΪβ�ڵ�
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

