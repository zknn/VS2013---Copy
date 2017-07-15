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


//1.�ж������Ƿ�������������󻷳��ȣ���ڵ�
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
	Node* IsCycle()   //�ж��Ƿ������fastʼ�ձ�slow��2��  
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
	int GetEntry(Node* meet)
	{
		Node* cur = meet;
		int count = 0;
		do
		{
			count++;
			cur = cur->_next;
		} while (cur != meet);
		return count;
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


//2.���ܼ̳е���
//�����췽�����������Ϊ˽��,ʹ�þ�̬����ʹ������ʵ����
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

//3.���һ����ֻ���ڶ��ϴ�������
//����Ĺ��캯������Ϊ˽�У�ʹ�þ�̬��������������ͷŶ���
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

//4.����һ����ֻ����ջ�ϴ�������
//�����ڶ��ϴ��������������������new���������Խ�new��������Ϊ˽��
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



