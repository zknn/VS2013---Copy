#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>
#include <queue>
#include <stack>
#include <list>
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
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const int* a, const int size, const int invalid)
	{
		assert(a);
		int index = 0;
		_root = Create(a, size, invalid, index);
	}
	Node* Create(const int* a, const int size, const int invalid, int& index)
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
		assert(_root);
		destroy(_root);
	}
	void destroy(Node* root)
	{
		if (root != NULL)
		{
			destroy(root->_left);
			destroy(root->_right);
			delete root;
		}
	}
	void PrevOrder()
	{
		assert(_root);
		_PrevOrder(_root);
		cout << endl;
	}
	void _PrevOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_data<<" ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
	}
	//判断是否为完全二叉树，借助辅助队列，当队列剩余节点全为空时，表明是完全二叉树
	bool  IsCompleteTree()
	{
		Node* cur = _root;
		queue<Node*> q;
		q.push(cur);
		while (cur)
		{
			q.push(cur->_left);
			q.push(cur->_right);
			q.pop();
			cur = q.front();
		}
		while (!q.empty())
		{
			if (q.front())
				return false;
			q.pop();
		}
		return true;
	}
	//查找两个节点的最近公共祖先（普通二叉树）
	Node* FindCommonAncestr(Node* x1,Node* x2)
	{
		assert(x1&&x2);
		stack<Node*> path1;
		stack<Node*> path2;
		if (GetNodePath(path1, x1) == false)
			return NULL;
		if (GetNodePath(path2, x2) == false)
			return NULL;
		while (path1.size() != path2.size())
		{
			if (path1.size() > path2.size())
				path1.pop();
			else
				path2.pop();
		}
		while (!path1.empty())
		{
			if (path1.top() == path2.top())
				return path1.top();
			path1.pop();
			path2.pop();
		}
	}
	//借助栈来实现，存储从根节点到此节点的路径
	bool GetNodePath(stack<Node*> &path,Node* node)
	{
		assert(_root);
		if (_GetNodePath(_root, path, node) == true)
			return true;
		else
			return false;
	} 
	bool _GetNodePath(Node* root, stack<Node*>& path, Node* node)
	{
		if (root == NULL)
			return false;
		path.push(root);
		if (root->_data == node->_data)
			return true;
		if (_GetNodePath(root->_left, path, node) == true)
			return true;
		if (_GetNodePath(root->_right, path, node) == true)
			return true;
		path.pop();
		return false;
	}
private:
	Node* _root;
};


void testf()  
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.PrevOrder();
	if (tree.IsCompleteTree() == true)
		cout << "该树是完全二叉树" << endl;
	else
		cout << "该树不是完全二叉树" << endl;
	BinaryTreeNode* node1 = new BinaryTreeNode(7);
	BinaryTreeNode* node2 = new BinaryTreeNode(6);
	BinaryTreeNode* node=tree.FindCommonAncestr(node1, node2);
	if (node != NULL)
		cout << "最近祖先是" << node->_data << endl;
	else
		cout << "没有公共祖先" << endl;
}

//二叉搜索树
struct BinaryNode
{
	int _data;
	BinaryNode* _left;
	BinaryNode* _right;
	BinaryNode(int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinarySearch
{
	typedef BinaryNode Node;
public:
	BinarySearch()
		:_root(NULL)
	{}
	~BinarySearch()
	{
		assert(_root);
		destroy(_root);
	}
	void destroy(Node* root)
	{
		if (root != NULL)
		{
			destroy(root->_left);
			destroy(root->_right);
			delete root;
		}
	}
	void  Insert(int data)
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
				cout << "无法插入，该节点已存在" << endl;
				return;
			}
		}
		if (parent->_data > data)
			parent->_left = new Node(data);
		else
			parent->_right = new Node(data);
	 
	}
	void PrevOrder()
	{
		assert(_root);
		_PrevOrder(_root);
		cout << endl;
	}
	void _PrevOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_data << " ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
	}
	//在二叉搜索树中查找两个节点的最近公共祖先
	Node* GetCommonAncersor(Node* x1, Node* x2)
	{
		if (_root == NULL)
			return NULL;
		Node* cur=_GetCommonAncersor(_root, x1, x2);
	}
	
	Node* _GetCommonAncersor(Node* root, Node* x1, Node* x2)
	{
		if (root == NULL)
			return NULL;
		if( (x1->_data<root->_data&&x2->_data>root->_data) || (x1->_data > root->_data&&x2->_data < root->_data))
			return root;
		if (x1->_data == root->_data)
			return x1;
		if (x2->_data == root->_data)
			return x2;
		if (x1->_data < root->_data&&x2->_data < root->_data)
			return _GetCommonAncersor(root->_left, x1, x2);
		if (x1->_data > root->_data&&x2->_data >root->_data)
		return	_GetCommonAncersor(root->_right, x1, x2);
	}
private:
	Node* _root;
};
void testSearch()
{
	int arr[] = { 5,3,4,1,7,8,2,6,0,9 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinarySearch tree;
	for (int i = 0; i < size; ++i)
	{
		tree.Insert(arr[i]);
	}
	tree.PrevOrder();
	BinaryNode* node1 = new BinaryNode(6);
	BinaryNode* node2 = new BinaryNode(7);
	BinaryNode* node = tree.GetCommonAncersor(node1, node2);
	if (node == NULL)
		cout << "没有公共祖先" << endl;
	else
		cout << "公共祖先是： " << node->_data << endl;

}

struct Node
{
	int _data;
	Node* _left;
	Node* _right;
	Node* _parent;
	Node(int data)
		: _data(data)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};
class Binary
{
public:
	Binary()
		:_root(NULL)
	{}
	Binary(int* a, int size, int invalid)
	{
		int index = 0;
		_root = Create(a,size,invalid,index);
		_root->_parent = NULL;
	}
	Node* Create(int *a,int size,int invalid,int &index)
	{
		Node* cur = NULL;
		if (index < size&&a[index] != invalid)
		{
			cur = new Node(a[index]);
			cur->_left = Create(a, size, invalid, ++index);
			cur->_right = Create(a, size, invalid, ++index);
			if (cur->_left)
			(cur->_left)->_parent = cur;
			if (cur->_right)
			(cur->_right)->_parent = cur;
		}
		return cur;
	}
	~Binary()
	{
		assert(_root);
		destroy(_root);
	}
	void destroy(Node* root)
	{
		if (root != NULL)
		{
			destroy(root->_left);
			destroy(root->_right);
			delete root;
		}
	}

	Node* GetAncersor(Node* x1, Node* x2)
	{
		if (x1 == NULL || x2 == NULL)
			return NULL;
		list<Node*> l1;
		list<Node*> l2;
		Node* parent1 = x1->_parent;
		while (parent1)
		{
			l1.push_front(parent1);
			parent1 = parent1->_parent;
		}
		Node* parent2 = x2->_parent;
		while (parent2)
		{
			l2.push_front(parent2);
			parent2 = parent2->_parent;
		}
		while(l1.size()!= l2.size())
		{
			if (l1.size() > l2.size())
				l1.pop_back();
			else
				l2.pop_back();
		}
		while (!l1.empty() && !l2.empty())
		{
			if (l1.back() == l2.back())
				return l1.back();
			l1.pop_back();
			l2.pop_back();
		}
	}
	Node* Find(int data)
	{
		Node* node = _Find(_root, data);
		if (node!=NULL)
			return node;
		else
			return NULL;
	}
	Node* _Find(Node* root, int data)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == data)
			return root;
		Node* ret = _Find(root->_left, data);
		if (ret)
			return ret;
		return _Find(root->_right, data);
	}

private:
	Node* _root;
};

void testBinary()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	Binary tree(arr, size, '#');
	Node* node1 = tree.Find(3);
	Node* node2 = tree.Find(4);
	Node* node=tree.GetAncersor(node1, node2);
	if (node != NULL)
		cout << "公共祖先是： " << node->_data << endl;
	else
		cout << "没有公共祖先" << endl;
}
int main()
{
	//testf();
	//testSearch();
	testBinary();
	return 0;
}