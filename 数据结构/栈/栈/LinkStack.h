//栈的链接存储结构--链栈
#ifndef LinkSTACK_H 
#define LinkSTACK_H

template<class TTT>
struct Node
{
	TTT data;
	Node<TTT> *next;
};

template<class TTT>
class LinkStack
{
public:
	LinkStack();     //构造函数，置空链栈
	~LinkStack();    //析构函数，释放链栈中各节点的存储空间
	void Push(TTT x);  //将元素x压入栈中
	TTT Pop();     //将栈顶元素出栈
	TTT GetPop();    //取栈顶元素（不删除）
	bool Empty();     //判断链表是否为空栈
private:
	Node<T> *top;   //栈顶指针
};


#endif