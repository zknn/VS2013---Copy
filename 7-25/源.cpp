#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stack>

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
	BinaryTree(int* a, int size, const int invalid)
	{
		if (a)
		{
			int index = 0;
			_root = Create(a, size, invalid, index);
		}
	}
    Node* Create(int *a, int size, const int invalid, int & index)
	{
		Node* cur = NULL;
		if (index < size&&a[index] != invalid)
		{
			cur = new Node(a[index]);
			cur->_left = Create(a, size, invalid, ++index);
			cur->_right = Create(a, size, invalid, ++index);
			return cur;
		}
		return NULL;
	}
	void PrevOrder()  //前序非递归
	{
		if (_root == NULL)
		{
			cout << "当前树是空树" << endl; 
			return;
		}
		Node* cur = _root;
		stack<Node*> s;
		s.push(cur);
		Node* prev = NULL;
		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->_data << " ";
			s.pop();
			if (top->_right)
				s.push(top->_right);
			if (top->_left)
			s.push(top->_left);
		}
		cout << endl;
	}
	void InOrder()  //中序非递归
	{
		if (_root == NULL)
		{
			cout << "当前树为空树" << endl;
			return;
		}
		if (_root->_left == NULL&&_root->_right == NULL)
		{
			cout <<"该树只有一个节点"<< _root->_data << endl;
			return;
		}
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cout << top->_data << " ";
			cur = top->_right;
		}
		cout << endl;
	}

	void PostInorder()    //后序非递归

	{
		if (_root == NULL)
		{
			cout << "当前树为空树" 
				<< endl;
			return;
		}
		if (_root->_left == NULL&&_root->_right == NULL)
		{
			cout << "该树只有一个节点" << _root->_data << endl;
			return;
		}
		Node* cur = _root;
		Node* prev = NULL;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << " ";
				prev = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}
	~BinaryTree()
	{
		if (_root)
		{
			destroy(_root);
		}
	}
	void destroy(Node* root)
	{
		if (root)
		{
			destroy(root->_left);
			destroy(root->_right);
			delete root;
			root = NULL;
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
	cout << "PrevOrder: ";
	tree.PrevOrder();
	cout << "InOrder: ";
	tree.InOrder();
	cout << "PostOrder: ";
	tree.PostInorder();
}
struct ListNode
{
	int _data;
	ListNode* _next;
	ListNode(int data)
		:_data(data)
		,_next(NULL)
	{}
};
class List
{
	typedef ListNode Node;
public:
	List()
		:_head(NULL)
	{}
	void PushBack(int data)
	{
		if (_head == NULL)
		{
			_head = new Node(data);
			return;
		}
		Node* cur = _head;
		while (cur->_next)
		{
			cur = cur->_next;
		}
		cur->_next = new Node(data);
	}
	Node* GetHead()
	{
		return _head;
	}
	Node* Find(int data)
	{
		if (_head == NULL)
			return NULL;
		Node* cur = _head;
		while (cur->_next)
		{
			if (cur->_data == data)
				return cur;
			cur = cur->_next;
		}
		if (cur->_data == data)
		{
			return cur;
		}
		return NULL;
	}
	void Erase(int data)
	{
		if (_head == NULL)
			return;
		Node* cur = _head;
		Node* node = Find(data);
		if (node == NULL)
			return;
		if (cur==node)
		{
			Node* nnext = cur->_next;
			delete cur;
			_head = nnext;
			return;
		}
		Node* head = _head;
		Node* prev = NULL;
		while (head->_next)
		{
			prev = head;
			head = head->_next;
		}
		if (head==node)
		{
			delete head;
			prev->_next = NULL;
			return;
		}
		Node* next = cur->_next;
		while (cur->_next != node)
		{
			cur = cur->_next;
		}
		cur->_next = next;
		delete node;
	}
	void difference(List l)   //将差集保存在原本链表中
	{
		Node* head1 = _head;
		Node* head2 = l.GetHead();
		Node* prev = NULL;
		Node* del = NULL;
		while (head1)
		{
			head2 = l.GetHead();
			while (head2&&head1->_data != head2->_data)
				head2 = head2->_next;
			if (head2)
			{
				if (!prev)
					_head = head1->_next;
				else
					prev->_next = head1->_next;
				del = head1;
				head1 = head1->_next;
				delete del;
			}
			else
			{
				prev = head1;
				head1 = head1->_next;
			}
		}
	}
	void Print()
	{
		if (_head != NULL)
		{
			Node* cur = _head;
			while (cur)
			{
				cout << cur->_data << " ";
				cur = cur->_next;
			}
			cout << endl;
		}
	}
private:
	Node* _head;
};

void testList()
{
	List l;
	l.PushBack(5);
	l.PushBack(10);
	l.PushBack(20);
	l.PushBack(15);
	l.PushBack(25);
	l.PushBack(30);

	l.Print();
	List s;
	s.PushBack(5);
	s.PushBack(15);
	s.PushBack(35);
	s.PushBack(25);
	s.Print();
	l.difference(s);
	l.Print();

}
int main()
{
	//testBinaryTree();
	testList();
	return 0;
}