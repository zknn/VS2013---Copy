#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <stack>
struct Node
{
	int _data;
	Node* _next;
	Node(int data)
		:_data(data)
		, _next(NULL)
	{}
};

class List
{
public:

	List()
		:_root(NULL)
	{}
	void PushBack(int data)
	{
		if (_root == NULL)
		{
			_root = new Node(data);
			_root->_next = NULL;
		}
		else
		{
			Node* cur = _root;
			while (cur->_next != NULL)
			{
				cur = cur->_next;
			}
			cur->_next = new Node(data);
			cur->_next->_next = NULL;
		}
	}
	void Reverse()  //链表逆置
	{
		Node* cur = _root;
		Node* prev = NULL;
		Node* next = NULL;
		if (cur == NULL || cur->_next == NULL)
		{
			return;
		}
		while (cur)
		{
			
			next = cur->_next;
			cur->_next = prev;
			prev = cur;
			cur = next;
		}
		_root = prev;
	}
	size_t Size()
	{
		size_t count = 0;
		Node* cur = _root;
		while (cur)
		{
			cur = cur->_next;
			count++;
		}
		return count;
	}
	//查找单链表的倒数第K的节点
	Node* FindK(int k)
	{
		Node* cur = _root;
		size_t count=0;
		while (cur&&count != (Size() - k ))
		{
			++count;
			cur = cur->_next;
		}
		return cur;
	}
	//递归实现
	/*void  RReverse()
	{
		Node* cur=_root;
		_RReverse(cur, _root);


	}
	void _RReverse(Node* cur,Node* root)
	{
		if (cur == NULL || cur->_next == NULL)
		{
			root = cur;
		}
		Node* next = cur->_next;
		_RReverse(next, root);
		cur->_next = NULL;
		next->_next = cur;
	}*/

	void Print()
	{
		Node* cur = _root;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
protected:
	Node* _root;
};

int Add(int data1, int data2)
{
	int sum;
	int carry;
	if (data1 == 0)
		return data2;
	if (data2 == 0)
		return data1;
	while (data2 != 0)
	{
		sum = data1^data2;
		carry = (data1&data2) << 1;
		data1 = sum;
		data2 = carry;
	}
	return sum;
}
int main()
{
	cout << Add(6, 4) << endl;   //10
	cout << Add(0, 0) << endl;   //0
	cout << Add(1, 0) << endl;   //1
	cout << Add(0, 1) << endl;   //1
	cout << Add(-1, 2) << endl;  //1
	cout << Add(-1, -2) << endl;  //-3
	List l1;
	l1.PushBack(0);
	l1.PushBack(2);
	l1.PushBack(4);
	l1.PushBack(8);
	l1.PushBack(9);
	l1.Print();
	//l1.Reverse();
	//l1.Print();
	cout << l1.Size() << endl;
	int k;
	cout << "请输入要查找的节点序号（倒序）";
	cin >> k;
	Node* cur =l1. FindK(k);
	cout << cur->_data << endl;
	//List l2;
	//l2.PushBack(0);
	//l2.Reverse();
	//List l3;
	//l3.Reverse();
	//l1.RReverse();
	//l1.Print();

	return 0;
}

