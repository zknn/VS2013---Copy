#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>
//1.��������ĸ߶Ⱥ����ٶ�����

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
	//���ٶ�����
	void destroy(Node* root)
	{
		if (root == NULL)
			return;
			destroy(root->_left);
			destroy(root->_right);
			delete root;
	}
	//��������ĸ߶�
	void height()
	{
		int count=_height(_root);
		cout << "�����ĸ߶���" << count << endl;
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


//��������ڵ�

typedef struct Node{
	int data;
    Node *next;
	Node(int d)
		:data(d)
		, next(NULL)
	{}
}*pList;

void InitList(pList* pplist) //��ʼ������
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
		cout << "��ǰ����Ϊ��" << endl;
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

	while (cur!=stop)  //��ת
	{
		Node* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
}

Node* ReverseK(Node* head, int k)  //��������С��
{
	if (head == NULL || k <= 0)
		return NULL;
	Node* cur = head;
	for (int i = 0; i < k - 1; i++) //�ҵ���K���ڵ��λ��
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
	Reverse(head, cur);   //��ת��һ���ڵ㵽��K���ڵ�
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
	cout << "������Kֵ��";
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