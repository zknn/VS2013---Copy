#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

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
	//1.将两个有序链表合并成一个有序链表
	void Merge(List l1, List l2)
	{
		Node* head1 = l1.GetRoot();
		Node* head2 = l2.GetRoot();
		_root = _Merge(head1, head2);
	}
	Node* _Merge(Node* head1, Node* head2)
	{
		if (head1 == NULL)
			return head2;
		if (head2 == NULL)
			return head1;
		Node* root = NULL;

		if (head1->_data <= head2->_data)
		{
			root = head1;
			root->_next = _Merge(head1->_next, head2);
		}
		if (head1->_data > head2->_data)
		{
			root = head2;
			root->_next = _Merge(head1, head2->_next);

		}
		return root;
	}

	Node* GetRoot()
	{
		return _root;
	}
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


int main()
{
	List l1;
	l1.PushBack(0);
	l1.PushBack(2);
	l1.PushBack(4);
	l1.PushBack(8);
	l1.Print();
	List l2;
	l2.PushBack(1);
	l2.PushBack(3);
	l2.PushBack(5);
	l2.PushBack(6);
	l2.Print();
	List l3;
	l3.Merge(l1, l2);

	l3.Print();


	return 0;
}



//利用构造函数求解1+2+...+n

class SUM
{
public:
	SUM()
	{
		++n;
		sum += n;
	}
	static unsigned int getsum()
	{
		return sum;
	}
private:
	static size_t n;
	static size_t sum;
};
size_t SUM::n = 0;
size_t SUM::sum = 0;

class A;
A* array[2];

class A
{
public:
	virtual size_t sum(size_t n)
	{
		return 0;
	}
};
class B :public A
{
public:
	virtual size_t sum(size_t n)
	{
		return  array[!!n]->sum(n - 1) + n;
	}
};
int main()
{
	size_t N;
	cout << "请输入N的值：";
	cin >> N;
	SUM *s = new SUM[N];
	delete[] s;
	s = NULL;
	cout << SUM::getsum() << endl;
	A a;
	B b;
	array[0] = &a;
	array[1] = &b;
	int value = array[1]->sum(N);
	cout << value << endl;
}


