#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

struct Node
{
	int _data;
	Node* _left;
	Node* _right;
	Node(int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};

class BinaryTree
{
public:
	BinaryTree(int* a,int size,const int invalid)
	{
		int index = 0;
		_root=Create(a, size, invalid, index);
	}
	Node* Create(int* a, int size, const int invalid, int& index)
	{  
		Node* cur = NULL;
		if (index<size&&a[index] != invalid)
		{
		    cur = new Node(a[index]);
			cur->_left = Create(a, size, invalid, ++index);
			cur->_right = Create(a, size, invalid, ++index);
		}
		return cur;
	}
	void Depth()
	{
		if (_root != NULL)
		{
			cout << "二叉树高度为:" << _Depth(_root) << endl;;
		}
	}
	int _Depth(Node* root)
	{
		if (root == NULL)
			return 0;
		int leftcount = _Depth(root->_left);
		int rightcount = _Depth(root->_left);
		return leftcount >= rightcount ? leftcount +1: rightcount+1;
		
	}
	void IsBalanceN()  //判断平衡
	{
		if (_root == NULL)
		{
			cout << "该树为空树" << endl;
			return;
		}
		if (_root->_left == NULL&&_root->_right == NULL)
		{
			cout << "该树只有一个节点" << endl;
			return;
		}
		int left = _Depth(_root->_left);
		int right = _Depth(_root->_right);
		if (abs(left - right) < 2)
			cout << "该树是平衡树" << endl;
		else
			cout << "该树不是平衡树" << endl;
	}
	void IsBalance()  //时间复杂度为O(n)  判断平衡
	{
		if (_root == NULL)
		{
			cout << "该树为空树" << endl;
			return;
		}
		int count = 0;
		if (_IsBalance(_root, count) == true)
		{
			cout << "该树为平衡树" << endl;
		}
		else
		{
			cout << "该树不是平衡树" << endl;

		}
	}
	bool _IsBalance(Node* root,int & count)
	{
		if (root == NULL)
			return true;
		int leftcount;
		int rightcount;
		if (_IsBalance(root->_left, leftcount) == false)
			return false;
		if (_IsBalance(root->_right, rightcount) == false)
			return false;
		return abs(leftcount - rightcount) < 2;
	}
	~BinaryTree()
	{
		if (_root != NULL)
		{
			destroy(_root);
		}
	}
	void destroy(Node* root)
	{
		if (root != NULL)
		{
			destroy(root->_left);
			destroy(root->_right);
			delete root;
			root = NULL;
		}
	}
	void Mirror()  //二叉树的镜像
	{
		if (_root == NULL)
			return;
		_Mirror(_root);
	}
	void _Mirror(Node* root)
	{
		if (root == NULL)
			return;
		if (root->_left != NULL || root->_right != NULL)
		{
			Node* tmp=root->_left;
			root->_left = root->_right;
			root->_right = tmp;
			_Mirror(root->_left);
			_Mirror(root->_right);
		}
	}
private:
	Node* _root;
};

void testBinaryTree()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.Depth();
	tree.IsBalance();
	tree.IsBalanceN();
	tree.Mirror();
}


void Find(int* a,int x,int row,int link)
{
	if (a != NULL&&row > 0 && link > 0)
	{
		int rows = 0;
		int links = link - 1;
		while (rows < row&&links >= 0)
		{
			if (a[rows*link + links] == x)
			{
				cout << "找到该数,此数在第"<<rows+1<<"行，第"<<links+1<<"列" << endl;
				return;
			}
			else if (a[rows*link + links]>x)
				--links;
			else
				++rows;
		}
		cout << "没找到" << endl;
	}
	cout << "没找到" << endl;
}
void test()
{
	int arr[][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
	Find((int*)arr, 6, 3, 4);
}
int main()
{
	//testBinaryTree();
	test();
	return 0;
}