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
			cout << "�������߶�Ϊ:" << _Depth(_root) << endl;;
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
	void IsBalanceN()  //�ж�ƽ��
	{
		if (_root == NULL)
		{
			cout << "����Ϊ����" << endl;
			return;
		}
		if (_root->_left == NULL&&_root->_right == NULL)
		{
			cout << "����ֻ��һ���ڵ�" << endl;
			return;
		}
		int left = _Depth(_root->_left);
		int right = _Depth(_root->_right);
		if (abs(left - right) < 2)
			cout << "������ƽ����" << endl;
		else
			cout << "��������ƽ����" << endl;
	}
	void IsBalance()  //ʱ�临�Ӷ�ΪO(n)  �ж�ƽ��
	{
		if (_root == NULL)
		{
			cout << "����Ϊ����" << endl;
			return;
		}
		int count = 0;
		if (_IsBalance(_root, count) == true)
		{
			cout << "����Ϊƽ����" << endl;
		}
		else
		{
			cout << "��������ƽ����" << endl;

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
	void Mirror()  //�������ľ���
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
				cout << "�ҵ�����,�����ڵ�"<<rows+1<<"�У���"<<links+1<<"��" << endl;
				return;
			}
			else if (a[rows*link + links]>x)
				--links;
			else
				++rows;
		}
		cout << "û�ҵ�" << endl;
	}
	cout << "û�ҵ�" << endl;
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