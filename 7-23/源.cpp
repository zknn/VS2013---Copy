#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>
//1.求二叉树的高度和销毁二叉树

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
	BinaryTree(int* a, const int size, const int invalid)
	{
		assert(a);
		int index = 0;
		_root = CreateNode(a, size, invalid, index);
	}
	Node* CreateNode(int* a, const int size, const int invalid, int& index)
	{
		Node* cur = NULL;
		if (index < size&&a[index] != invalid)
		{
			cur = new Node(a[index]);
			cur->_left = CreateNode(a, size, invalid, ++index);
			cur->_right = CreateNode(a, size, invalid, ++index);
		}
		return cur;
	}
	~BinaryTree()
	{
		assert(_root);
		destroy(_root);
	}
	//销毁二叉树
	void destroy(Node* root)
	{
		if (root == NULL)
			return;
			destroy(root->_left);
			destroy(root->_right);
			delete root;
	}
	//求二叉树的高度
	void height()
	{
		int count=_height(_root);
		cout << "该树的高度是" << count << endl;
	}
	int _height(Node* root)
	{
		if (root == NULL)
			return 0;
		int leftcount = _height(root->_left);
		int rightcount = _height(root->_right);
		return leftcount >= rightcount ? leftcount + 1 : rightcount + 1;
	}
private:
	Node* _root;
};

void testBinaryTree()
{
	int arr[] = { 1, 2, 3, '#', '#', 4,'#','#',5, 6,'#', '#',  7 };
	const int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.height();
}


//定义链表节点

struct Node{
	int data;
    Node *next;
};

//函数在给定头结点和尾节点的情况下，对整个链表做翻转

void ReverseLinkList(Node *head, Node *end)
{
    if (head == NULL || end == NULL) return;
	Node *pre = NULL, *cur = head, *stop = end->next;
	while (cur != stop)
	{
		Node* nxt = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nxt;
	}
}

//k链表翻转

Node* ReverseKLinkList(Node *head, int k)
{
	if (head == NULL || k <= 0) return NULL;
	Node *cur = head;
	for (int i = 0; i<k - 1; i++)
	{
		cur = cur->next;
		if (cur == NULL)
			break;
	}

	//在链表长度小于k的情形下，直接返回原链表

	if (cur == NULL) return head;
	Node* begin = cur->next, *end = begin;
	Node* pre = head;
	ReverseLinkList(head, cur);
	while (begin != NULL)
	{
		for (int i = 0; i < k - 1; i++)
		{
			end = end->next;
			if (end == NULL)
				break;
		}
		if (end == NULL)
		{
			pre->next = begin;
			break;
		}
		else
		{
			Node *nextbegin = end->next;
			ReverseLinkList(begin, end);
			pre->next = end;
			pre = begin;
			begin = end = nextbegin;
		}
	}
	return cur;
}

int testList()
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	Node* node[12];
	for (int i = 0; i<12; i++)
	{
		node[i] = new Node;
		node[i]->next = NULL;
		node[i]->data = a[i];
	}
	for (int i = 0; i<11; i++)
	{
		node[i]->next = node[i + 1];
	}
	int k = 0;
	cout << "请输入K值：";
	cin >> k;
	Node *tmp = ReverseKLinkList(node[0], k);
    for (; tmp != NULL; tmp = tmp->next)
	{
		cout << tmp->data <<" ";
	}
	cout << endl;
	return 0;
}

int main()
{
	//testBinaryTree();
	testList();
	return 0;
}