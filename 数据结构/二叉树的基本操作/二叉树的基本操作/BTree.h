#ifndef BTREE_H
#define BTREE_H

struct BTreeNode
{
	int data;
	BTreeNode *lChild, *rChild;
};

class BTree
{
public:
	void setRoot(BTreeNode* r)
	{
		root = r;
	}
	BTreeNode* getRoot()
	{
		return root;
	}
	void inOrder();           //����������ݹ飩
	void NotReInOrder();      //����������ǵݹ飩
	BTreeNode* createBTree(); //����������
	void preOrder();          //ǰ��������ݹ飩
	void NotRePreOrder();     //ǰ��������ǵݹ飩
	void postOrder();         //����������ݹ飩
	void NotRePostOrder();    //����������ǵݹ飩
	int BTreeSize();          //��ڵ����
	int BTreeLeaves();        //��Ҷ�ӽڵ����
	int BTreeHeight();        //������
	int layerHeight();        //��η�������
protected:
	void inOrder(BTreeNode*); //�������
	void preOrder(BTreeNode*);//ǰ�����
	void postOrder(BTreeNode*);//�������
	int BTreeSize(BTreeNode*);//�ڵ����
	int BTreeLeaves(BTreeNode*);//Ҷ�Ӹ���
	int BTreeHeight(BTreeNode*);//����
private:
	BTreeNode* root;
};



#endif
