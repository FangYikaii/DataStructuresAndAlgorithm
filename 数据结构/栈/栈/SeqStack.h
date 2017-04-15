//if not define:条件指示符#ifndef 的最主要目的是防止头文件的重复包含和编译。
//如果标识符SEQSTACK_H 没有被定义，则重定义标识SEQSTACK_H ，执行#define SEQSTACK_H ...  #endif
#ifndef SEQSTACK_H 
#define SEQSTACK_H


//栈的顺序存储结构--顺序栈

const int StackSize = 10;

template<class T>      //定义模板类SeqStack
class SeqStack
{
public:
	SeqStack();         //构造函数，栈的初始化
	~SeqStack();        //析构函数
	void Push(T x);     //将元素x入栈
	T Pop();            //将栈顶元素弹出
	T GetTop();         //取栈顶元素(并不删除)
	bool Empty();       //判断栈是否为空
private:
	T data[StackSize];    //存放栈元素的数组
	int top;              //栈顶指针，指示栈顶元素在数组中的下标
};


#endif