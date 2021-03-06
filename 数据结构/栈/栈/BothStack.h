//栈的顺序存储结构--双栈

#ifndef BOTHSTACK_H 
#define BOTHSTACK_H

const int BothStackSize = 100;  //最大容量

template <class TT>
class BothStack
{
public:  
	BothStack();  //构造函数，将两个栈分别初始化
	~BothStack();  //析构函数
	void Push(int i, TT x);  //将元素x压入栈i
	TT Pop(int i);        //对栈i执行出栈操作
	TT GetTop(int i);     //取栈i的栈顶元素
	bool Empty(int i);   //判断栈i是否为空栈
private:
	TT data[BothStackSize];  //存放两个栈的数组
	int top1, top2;      //两个栈的栈顶指针，分别指向各自的栈顶元素在数组中的下标
};



#endif