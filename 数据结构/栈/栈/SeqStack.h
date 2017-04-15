//if not define:����ָʾ��#ifndef ������ҪĿ���Ƿ�ֹͷ�ļ����ظ������ͱ��롣
//�����ʶ��SEQSTACK_H û�б����壬���ض����ʶSEQSTACK_H ��ִ��#define SEQSTACK_H ...  #endif
#ifndef SEQSTACK_H 
#define SEQSTACK_H


//ջ��˳��洢�ṹ--˳��ջ

const int StackSize = 10;

template<class T>      //����ģ����SeqStack
class SeqStack
{
public:
	SeqStack();         //���캯����ջ�ĳ�ʼ��
	~SeqStack();        //��������
	void Push(T x);     //��Ԫ��x��ջ
	T Pop();            //��ջ��Ԫ�ص���
	T GetTop();         //ȡջ��Ԫ��(����ɾ��)
	bool Empty();       //�ж�ջ�Ƿ�Ϊ��
private:
	T data[StackSize];    //���ջԪ�ص�����
	int top;              //ջ��ָ�룬ָʾջ��Ԫ���������е��±�
};


#endif