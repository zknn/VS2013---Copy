#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <queue>

//1.�������Ҷ�ӽڵ�ĸ���/���������k��Ľڵ����

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
	BinaryTree()
		:_root(NULL)
	{}
	Node* CreateTree(int *a, int& size,const int& invalid, int& index)
	{
		Node* cur = NULL;
		if (index < size&&a[index] != invalid)
		{
			cur = new Node(a[index]);
			cur->_left = CreateTree(a, size, invalid, ++index);
			cur->_right = CreateTree(a, size, invalid, ++index);
		}
		return cur;
	}
	BinaryTree(int* a, int size,const int& invalid)
	{
		int index = 0;
		_root=CreateTree(a, size, invalid, index);
	}
	void destroy(Node* root)
	{
		if (root == NULL)
			return;
		destroy(root->_left);
		destroy(root->_right);
		delete root;
	}
	~BinaryTree()
	{
		destroy(_root);
	}
	//���K��Ľڵ����
	int leafCountK(int k)
	{
		return _leafCountK(_root, k);
	}
	int _leafCountK(Node* root, int k)
	{
		if (_root == NULL || k < 0)
			return 0;
		if (k == 0)
			return 1;
		else
			return _leafCountK(root->_left, k - 1) + _leafCountK(root->_right, k - 1);
	}
	//��Ҷ�ӽڵ����
	int  leafCount()
	{
		int count = 0;
		 _leafCount(_root,count);
		 return count;
	}
	void  _leafCount(Node* root,int & count)
	{
		if (root->_left == NULL&&root->_right == NULL)
		{
			count++;
			return;
		}
		_leafCount(root->_left, count);
		_leafCount(root->_left, count);
	}
private:
	Node* _root;
};


void testBinaryTree()
{
	
	int arr[] = { 1, 2, 3 ,'#', '#',4,'#','#', 5, 6,'#','#' ,7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	cout << "Ҷ�ӽڵ�ĸ�����" << tree.leafCount() << endl;
	cout << "��2��Ľڵ�������Ը��ڵ�Ϊ��0�㣩" << tree.leafCountK(2) << endl;
	cout << "��1��Ľڵ�������Ը��ڵ�Ϊ��0�㣩" << tree.leafCountK(1) << endl;
	cout << "��0��Ľڵ�������Ը��ڵ�Ϊ��0�㣩" << tree.leafCountK(0) << endl;
}

#include <vector>
//2.һ����������һ�����ֵĴ��������������һ�룬�������ַ����磺int a[]={2,3,2,2,2,2,2,5,4,1,2,3}���������һ���������2
void Count(int* a,int size)     //�о����ԣ�����Ԥ��֪��ԭ������Ĵ�С
{
	if (a == NULL)
		return ;
	 int  suma = size - 1;
	int average = suma / 2;
	int uu[10] = { 0 };
	//vector<int> uu;
	//uu.reserve(size);
//	uu.resize(size, 0);
	int* s = a;
	for (int i = 0; i <size; i++)
	{
		uu[*(s++)]++;
	}
	s = a;
	for (int i = 0; i <size; i++)
	{
		if (uu[*s] >= average)
		{
			cout << "������ " << *s<<endl;
			return;
		}
	}
	cout << "û����������" << endl;
}

void testCount()
{
	int a[] = { 2, 3, 2, 2, 2, 2, 2, 5, 4, 1, 2, 3 };
    int size = sizeof(a) / sizeof(a[0]);
	Count(a, size);
	int a1[] = { 1 };
	 int size1 = sizeof(a1) / sizeof(a1[0]);
	Count(a1, size1);
	int a2[] = { 0, 1, 2, 3, 3, 4, 5, 7 };
	 int size2 = sizeof(a2) / sizeof(a2[0]);
	Count(a2, size2);
}
int main()
{
	//testBinaryTree();

	testCount();
	return 0;
}