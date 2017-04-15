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
	void inOrder();           //中序遍历（递归）
	void NotReInOrder();      //中序遍历（非递归）
	BTreeNode* createBTree(); //建立二叉树
	void preOrder();          //前序遍历（递归）
	void NotRePreOrder();     //前序遍历（非递归）
	void postOrder();         //后序遍历（递归）
	void NotRePostOrder();    //后序遍历（非递归）
	int BTreeSize();          //求节点个数
	int BTreeLeaves();        //求叶子节点个数
	int BTreeHeight();        //求树高
	int layerHeight();        //层次法求树高
protected:
	void inOrder(BTreeNode*); //中序遍历
	void preOrder(BTreeNode*);//前序遍历
	void postOrder(BTreeNode*);//后序遍历
	int BTreeSize(BTreeNode*);//节点个数
	int BTreeLeaves(BTreeNode*);//叶子个数
	int BTreeHeight(BTreeNode*);//树高
private:
	BTreeNode* root;
};



#endif
