#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include  <assert.h>
struct Node
{
	int _data;
	Node* _next;
	Node(int data)
		:_data(data)
		, _next(NULL)
	{}
};


//1.判断链表是否带环，若带环求环长度，入口点
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
			while (cur->_next)
			{
				cur = cur->_next;
			}
			Node* node = new Node(data);
			cur->_next = node;
			node->_next = NULL;
		}
	}
	Node* Find(int data)
	{
		if (_root == NULL)
			return NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data == data)
				return cur;
			cur = cur->_next;
		}
		return NULL;
	}
	Node* IsCycle()   //判断是否带环，fast始终比slow快2个  
	{
		Node* fast = _root;
		Node* slow = _root;
		while ((fast->_next) && (fast!=NULL))
		{
			fast = fast->_next->_next;
			slow = slow->_next;
			if (fast == NULL)
			{
				return NULL;
			}
			else if (fast == slow)
			{
				return slow;
			}
		}
		return NULL;
	}
        Node* GetEntry(Node* meet)
	{
		Node* cur = _root;
		Node* meetnode=meet;
		while (cur != meetnode)
		{
			cur = cur->_next;
			meetnode = meetnode->_next;
		}
		return cur;
	}
	int GetCycleLength(Node* meet)
	{
		int count = 0;
		Node* cur = meet;
		do
		{
			count++;
			cur = cur->_next;
		} while (cur != meet);
		return count;
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


//2.不能继承的类
//将构造方法和析构设计为私有,使用静态方法使它可以实例化
class A
{
public:
	static A* get()
	{
		A* a = new A();
	}
	static void deleteA(A* a)
	{
		if (a!=NULL)
		delete a;
	}
private:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}

};

//3.设计一个类只能在堆上创建对象
//将类的构造函数声明为私有，使用静态方法创建对象和释放对象
class A
{
public:
	static A* get()
	{
		A* a = new A();
	}
	static void deleteA(A* a)
	{
		if (a != NULL)
			delete a;
	}
private:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}

};

//4.创建一个类只能在栈上创建对象
//不能在堆上创建，即不能在类外调用new方法，所以将new方法重载为私有
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	void* operator new (size_t size);
};

int main()
{
	List l;
	l.PushBack(1);
	l.PushBack(4);
	l.PushBack(6);
	l.PushBack(8);
	l.PushBack(3);
	l.PushBack(2);
	l.PushBack(0);
	l.PushBack(9);
	//l.Print();
	Node* ret1 = l.Find(3);
	Node* ret2 = l.Find(9);
	ret2->_next = ret1;
	Node* meet = l.IsCycle();
	if (meet!=NULL)
	cout << meet->_data<< endl;
	cout << l.GetEntry(meet) << endl;
	cout << l.GetCycleLength(meet) << endl;
	//l.Print();
}



