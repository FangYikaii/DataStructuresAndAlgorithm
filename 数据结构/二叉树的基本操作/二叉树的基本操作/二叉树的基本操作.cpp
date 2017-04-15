// 二叉树的基本操作.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BTree.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//建立二叉树的算法
BTreeNode* BTree::createBTree()
{
	BTreeNode* current = 0;
	int val = 0;
	cin >> val;
	//-1的个数比数值的个数多1
	if (val == -1)
	{
		return NULL;
	}
	else
	{
		current = new BTreeNode;
		current->data = val;
		current->lChild = createBTree();
		current->rChild = createBTree();
		return current;
	}
}

//利用重载的方法
void BTree::inOrder()
{
	inOrder(root);
	cout << endl;
}

//中序访问二叉树（递归）
void BTree::inOrder(BTreeNode* r)
{
	if (r != 0)  //是if，而不是while
	{
		inOrder(r->lChild);  //递归访问
		cout << r->data << " ";
		inOrder(r->rChild);  //递归访问
	}
}

//中序遍历（非递归not recursion）
void BTree::NotReInOrder()
{
	stack<BTreeNode*> s;  //声明一个栈s
	BTreeNode* r = getRoot();
	//如果栈s不为空或节点不为0
	while (!s.empty() || r != 0)
	{
		while (r != 0)
		{
			s.push(r);   //压入
			r = r->lChild;   //左子树
		}
		if (!s.empty())
		{
			r = s.top();  //取栈顶元素
			s.pop();      //弹栈顶元素
			cout << r->data << " ";  //打印
			r = r->rChild;  //右子树
		}
	}
}

//重载形式  
void BTree::preOrder()
{
	preOrder(root);
	cout << endl;
}


//前序递归访问二叉树(递归)  
void BTree::preOrder(BTreeNode* r)
{
	if (r != 0) //是if，而不是while  
	{
		cout << r->data << " ";
		preOrder(r->lChild); //递归访问  
		preOrder(r->rChild); //递归访问  
	}
}


//前序遍历(非递归)  
//节点-左子树-右子树
void BTree::NotRePreOrder()
{
	stack<BTreeNode*> s;
	BTreeNode* r = getRoot();  //要遍历的树
	s.push(r);     //压入s

	while (!s.empty())  //第一个不为空
	{
		r = s.top();
		s.pop();

		cout << r->data << " ";

		if (r->rChild != 0)
			s.push(r->rChild);
		if (r->lChild != 0)
			s.push(r->lChild);
	}
}


//重载形式  
void BTree::postOrder()
{
	postOrder(root);
	cout << endl;
}

//后序遍历(递归)  
//左-右-节点
void BTree::postOrder(BTreeNode* r)
{
	if (r != 0) //是if，而不是while  
	{
		postOrder(r->lChild); //递归访问  
		postOrder(r->rChild); //递归访问  
		cout << r->data << " ";
	}
}


//后序非递归访问要定义新的结构体类型  
struct Node
{
	BTreeNode* tp;
	bool flag;
};

//后序遍历(非递归)  
void BTree::NotRePostOrder()
{
	Node node; //定义Node结构体的一个结点  
	stack<Node> s;

	BTreeNode* r = getRoot();
	while (!s.empty() || r != 0)
	{
		while (r != 0)
		{
			node.tp = r;
			node.flag = 0;
			s.push(node);
			r = r->lChild;
		}

		if (!s.empty())
		{
			node = s.top();
			s.pop();
			r = node.tp; //将栈顶的BTreeNode*部分赋给r  
			if (node.flag == 1)
			{
				cout << r->data << " ";
				r = 0; //表示已经访问了该结点  
			}
			else
			{
				node.flag = 1;
				s.push(node);
				r = r->rChild;
			}
		}
	}
}


//重载形式  
int BTree::BTreeSize()
{
	return BTreeSize(root);
}

//求二叉树结点个数的函数  
int BTree::BTreeSize(BTreeNode* r)
{
	//二叉树的结点个数为左右子树的高度之和再+1  
	if (r == 0) return 0;
	else
		return 1 + BTreeSize(r->lChild) + BTreeSize(r->rChild);
}

//重载形式  
int BTree::BTreeLeaves()
{
	return BTreeLeaves(root);
}

//求二叉树叶子结点个数的函数  
int BTree::BTreeLeaves(BTreeNode* r)
{
	//当为空时，返回0；当找到叶子时返回1  
	if (r == 0) return 0;
	else
		if (r->lChild == 0 && r->rChild == 0)
			return 1;
		else
			return BTreeLeaves(r->lChild) + BTreeLeaves(r->rChild);
}

//重载形式  
int BTree::BTreeHeight()
{
	return BTreeHeight(root);
}

//求二叉树高度的函数  
int BTree::BTreeHeight(BTreeNode* r)
{
	if (r == 0) return 0;
	else
	{
		//二叉树的高度为左右子树的最大者+1  
		int lHei = BTreeHeight(r->lChild);
		int rHei = BTreeHeight(r->rChild);
		return (lHei>rHei) ? lHei + 1 : rHei + 1;
	}
}



//层次遍历求树高需要利用的新结构  
struct LayerBTreeNode
{
	BTreeNode* ptr;
	int height;
};

//层次遍历求高度  
int BTree::layerHeight()
{
	queue<LayerBTreeNode> que;
	LayerBTreeNode temp, lTemp, rTemp; //牺牲空间来获得算法的清晰度  

	BTreeNode* r = getRoot();

	int hei = 1;
	temp.ptr = r;
	temp.height = 1;
	que.push(temp); //先将根对应的LayerBTreeNode对象进队  

	//不为空时  
	while (!que.empty())
	{
		//BTreeNode* btreePtr=0;  

		temp = que.front(); //取出队首元素  
		que.pop();

		r = temp.ptr;

		//用当前的高度跟取出的队首进行比较  
		if (hei<temp.height)
			hei = temp.height;

		if (r->lChild != 0 || r->rChild != 0)
		{
			//如果它的左右子树不为空，则进队列  
			if (r->lChild != 0)
			{
				lTemp.ptr = r->lChild;
				lTemp.height = temp.height + 1; //在原来高度基础上加1,再入队列  
				que.push(lTemp);
			}
			if (r->rChild != 0)
			{
				rTemp.ptr = r->rChild;
				rTemp.height = temp.height + 1;
				que.push(rTemp);
			}

		}
	}
	return hei;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

