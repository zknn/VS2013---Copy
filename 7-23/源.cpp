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

typedef struct Node{
	int data;
    Node *next;
	Node(int d)
		:data(d)
		, next(NULL)
	{}
}*pList;

void InitList(pList* pplist) //初始化链表
{
	assert(pplist != NULL);
	*pplist = NULL;
}
void PushBack(pList* pplist, int data)
{
	assert(pplist != NULL);
		Node* newnode = new Node(data);
		if (*pplist == NULL)
		{
			*pplist = newnode;
		}
		else
		{
			Node* cur = *pplist;
			while (cur->next)
			{
				cur = cur->next;
			}
			cur->next = newnode;
		}
}
void PrintList(pList plist)
{
	if (plist == NULL)
	{
		cout << "当前链表为空" << endl;
		return;
	}
	Node* cur = plist;
	while (cur)
	{
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}

void Reverse(Node* head, Node* tail)
{
	if (head == NULL || tail == NULL)
		return;
	Node* prev = NULL;
	Node* cur = head;
	Node* stop = tail->next;

	while (cur!=stop)  //翻转
	{
		Node* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
}

Node* ReverseK(Node* head, int k)  //当链表长度小于
{
	if (head == NULL || k <= 0)
		return NULL;
	Node* cur = head;
	for (int i = 0; i < k - 1; i++) //找到第K个节点的位置
	{
		cur = cur->next;
		if (cur == NULL)
			break;
	}
	if (cur == NULL)
		return head;
	Node* begin = cur->next;
	Node* end = begin;
	Node* prev = head;
	Reverse(head, cur);   //翻转第一个节点到第K个节点
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
			prev->next = begin;
			break;
		}
		else
		{
			Node* nextbegin = end->next;
			Reverse(begin, end);
			prev->next = end;
			prev = begin;
			begin = end = nextbegin;
		}
	}
	return cur;
}
void test()
{
	pList plist;
	InitList(&plist);
	int a[] = { 1, 2, 3, 4, 5};
	for (int i = 0; i < sizeof(a) / sizeof(a[0]);i++)
	{
		PushBack(&plist, a[i]);
	}
	PrintList(plist);
	Node* head = plist;
	int k = 0;
	cout << "请输入K值：";
	cin >> k;
	Node* cur=ReverseK(head, k);
	PrintList(cur);
}


int main()
{
	//testBinaryTree();
	test();
	return 0;
}