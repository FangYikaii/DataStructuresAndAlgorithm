//ջ�����Ӵ洢�ṹ--��ջ
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
	LinkStack();     //���캯�����ÿ���ջ
	~LinkStack();    //�����������ͷ���ջ�и��ڵ�Ĵ洢�ռ�
	void Push(TTT x);  //��Ԫ��xѹ��ջ��
	TTT Pop();     //��ջ��Ԫ�س�ջ
	TTT GetPop();    //ȡջ��Ԫ�أ���ɾ����
	bool Empty();     //�ж������Ƿ�Ϊ��ջ
private:
	Node<T> *top;   //ջ��ָ��
};


#endif