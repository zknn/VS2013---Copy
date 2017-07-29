#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//单例模式，饿汉实现

class singleton
{
protected:
	singleton()
	{}
private:
	static singleton* p;
public:
	static singleton* initance();
};
singleton* singleton::p = new singleton();
singleton* singleton::initance()
{
	return p;
}
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
#include <stack>
class Binary
{
public:
	Binary()
		:_root(NULL)
	{}
	void Insert(int data)
	{
		if (_root == NULL)
		{
			_root = new Node(data);
			return;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_data > data)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_data < data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				cout << "该数已存在" << endl;
				return;
			}
		}
		if (parent->_data > data)
		{
			parent->_left = new Node(data);
		}
		if (parent->_data < data)
		{
			parent->_right = new Node(data);
		}
	}
	void PrevOrder()
	{
		if (_root)
			_PrevOrder(_root);
		cout << endl;
	}
	void _PrevOrder(Node* root)
	{
		if (root)
		{
			cout << root->_data << " ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
	}
	Node* change()
	{
		if (_root == NULL)
			return NULL;
		Node* rightnode = NULL;
		_change(_root, rightnode);
		Node* head = rightnode;
		while (head != NULL&&head->_left != NULL)
			head = head->_left;
		return head;
	}
	void _change(Node* root,Node*& rightnode)
	{
		if (root == NULL)
			return;
		Node* cur = root;
		if (cur->_left)
			_change(cur->_left,rightnode);
		cur->_left = rightnode;
		if (rightnode)
		   rightnode->_right = cur;
		rightnode = cur;
		if (cur->_right)
			_change(cur->_right, rightnode);
	}
private:
	Node* _root;
};
void test()
{
	Binary tree;
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int size = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < size; i++)
	{
		tree.Insert(arr[i]);
	}
	cout << "前序遍历" << endl;
	tree.PrevOrder();
	Node* root=tree.change();
	while (root)
	{
		cout <<root->_data<< " ";
		root = root->_right;
	}
	cout << endl;
}
int main()
{
	test();
	return 0;
}