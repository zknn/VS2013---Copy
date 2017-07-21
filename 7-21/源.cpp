#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <queue>
//1.二叉树的层序遍历
struct BinaryTreeNode
{
	int _data;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	BinaryTreeNode(int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinaryTree
{
public:
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(int* a, int size,const int& invalid)
	{
		int index = 0;
		_root = CreateNode(a, size,index,invalid);
	}
	Node* CreateNode(int* a, int size,int& index,const int& invalid)
	{
		Node* cur = NULL;
		if (index < size&&a[index] != invalid)
		{
			cur = new Node(a[index]);
			cur->_left = CreateNode(a, size, ++index, invalid);
			cur->_right = CreateNode(a, size, ++index, invalid);
		}
		return cur;
	}
	void BFS()   //借助队列实现
	{
		queue<Node*> q;
		q.push(_root);
		while (q.empty() == false)
		{
			cout << q.front()->_data << " ";
			if (q.front()->_left!=NULL)
			q.push(q.front()->_left);
			if (q.front()->_right != NULL)
				q.push(q.front()->_right);
			q.pop();	
		}
		cout << endl;
	}
private:
	Node* _root;
};

void test()
{
	int a[] = { 1, 2, 3, '#', '#',4,'#','#',5,6};
	int sz = sizeof(a) / sizeof(a[0]);
	BinaryTree t(a, sz, '#');
	t.BFS();
}


//2.给定一个整数N，那么N的阶乘N！有几个0

void judjezero(int n)
{
	int sum = 0;
	while (n >=5)
	{
		sum += n / 5;
		n = n / 5;
	}
	cout << sum << endl;
}

void testzero(int N)
{
	int count = 0;
	for (int i = N; i > 0; i--)
	{
		int j = i;
		while (j % 5 == 0)
		{
			count++;
			j =j/ 5;
		}
	}
	cout << count << endl;;
}
int main()
{
	//test();
	judjezero(15);
	testzero(15);
	return 0;
}