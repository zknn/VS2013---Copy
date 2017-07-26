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
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(int *a, int size, const int invalid)
	{
		if (a)
		{
		int	index = 0;
		_root = Create(a, size, invalid, index);
		}
	}
	Node* Create(int* a, int size, const int invalid, int& index)
	{
		Node* cur = NULL;
		if (index < size&&a[index] != invalid)
		{
			cur = new Node(a[index]);
			cur->_left = Create(a, size, invalid, ++index);
			cur->_right = Create(a, size, invalid, ++index);
		}
		return cur;
	}

	~BinaryTree()
	{
		Destroy(_root);
	}
	void Destroy(Node* root)
	{
		if (root == NULL)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
	Node* GetRoot()
	{
		if (_root)
			return _root;
		else
			return NULL;
		
	}
	void  JudjeRoot(BinaryTree& tree)
	{
		Node* root = tree.GetRoot();
		bool result = _JudjeRoot(_root, root);
		if (result == false)
			cout << "树2不是树1的子树" << endl;
		else
			cout << "树2是树1的子树" << endl;
	}
	bool _JudjeRoot(Node* root1, Node* root2)  //判断tree2的根节点是否在tree1中
	{
		bool result = false;
		if (root1 == NULL || root2 == NULL)
			return false;
		if (root1&&root2)
		{
			if (root1->_data == root2->_data)
				result = _JudjeTree(root1,root2);
			if (!result)
				result = _JudjeRoot(root1->_left, root2);
			if (!result)
				result = _JudjeRoot(root1->_right, root2);
		}
		return result;
	}
	void  JudjeTree(BinaryTree& tree)  //判断根节点是否可以找到
	{
		Node* root = tree.GetRoot();
		_JudjeTree(_root, root);
	}
	bool _JudjeTree(Node* root1, Node* root2)  
	{
		if (root2 == NULL)
			return true;
		if (root1 == NULL)
			return false;
		if (root1->_data != root2->_data)
			return false;
		return _JudjeTree(root1->_left, root2->_left) && _JudjeTree(root1->_right, root2->_right);
	}
	void PrevOrder()
	{
		if (_root)
		{
			_PrevOrder(_root);
		}
		cout << endl;
	}
	//查找函数
	void Find(const int data)
	{
		if (_root)
		{
			if (_Find(_root,data))
			{
				cout <<"找到了，是："<< _Find(_root,data)->_data << endl;
				return;
			}
			cout << "没有此节点" << endl;
			return;
		}
		cout << "二叉树为空" << endl;
			
	}
	Node* _Find(Node* root,const int data)
	{
		if (root == NULL)
			return NULL;
		if (root->_left == NULL&&root->_right == NULL)
		{
			if (root->_data = data)
				return root;
			else
				return NULL;
		}
		if (root->_data == data)
			return root;
		_Find(root->_left,data);
		_Find(root->_right,data);
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
private:
	Node* _root;
};

void testfind()  //测试查找函数
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.PrevOrder();
	tree.Find(1);
	tree.Find(2);
	tree.Find(3);
	tree.Find(4);
	tree.Find(5);
	tree.Find(6);
	tree.Find(7);
	tree.Find(0);
}
void testJudje()//测试判断子树
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree treeA(arr, size, '#');
	cout << "树A的前序遍历： " << endl;
	treeA.PrevOrder();
	int arr1[] = {  2, 3, '#', '#', 4};
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree treeB(arr1, size1, '#');
	cout << "树B的前序遍历： " << endl;
	treeB.PrevOrder();
	treeA.JudjeRoot(treeB);
	cout << endl << endl;
	int arr2[] = { 7,8,'#','#',9 };
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	BinaryTree treeC(arr2, size2, '#');
	cout << "树A的前序遍历： " << endl;
	treeA.PrevOrder();
	cout << "树C的前序遍历： " << endl;
	treeC.PrevOrder();
	treeA.JudjeRoot(treeC);
}
int main()
{
	//testfind();
	testJudje();
	return 0;
}