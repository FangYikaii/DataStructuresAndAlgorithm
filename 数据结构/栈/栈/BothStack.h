//ջ��˳��洢�ṹ--˫ջ

#ifndef BOTHSTACK_H 
#define BOTHSTACK_H

const int BothStackSize = 100;  //�������

template <class TT>
class BothStack
{
public:  
	BothStack();  //���캯����������ջ�ֱ��ʼ��
	~BothStack();  //��������
	void Push(int i, TT x);  //��Ԫ��xѹ��ջi
	TT Pop(int i);        //��ջiִ�г�ջ����
	TT GetTop(int i);     //ȡջi��ջ��Ԫ��
	bool Empty(int i);   //�ж�ջi�Ƿ�Ϊ��ջ
private:
	TT data[BothStackSize];  //�������ջ������
	int top1, top2;      //����ջ��ջ��ָ�룬�ֱ�ָ����Ե�ջ��Ԫ���������е��±�
};



#endif