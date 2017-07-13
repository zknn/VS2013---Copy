#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

typedef int DataType;
struct SListNode
{
	DataType _data;
	SListNode* _next;
	SListNode(DataType x)
		:_data(x)
		, _next(NULL)
	{}
};

class SList
{
	typedef SListNode Node;
public:
	SList()
		:_head(NULL)
		, _tail(NULL)
	{
	}
	~SList()
	{
		Node* cur=_head;
		while (cur)
		{
			Node* del = cur;
			cur = cur->_next;
			delete del;
			del = NULL;
		}
		
	}
	SList(const SList& l)
	{
		Node* cur = l._head;
		while (cur)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}
	SList& operator=(SList l)
	{
		if (this != &l)
		{
			SList tmp = l;
			l = *this;
			*this = tmp;
		}
		return *this;
	}
	void PushBack(DataType data)
	{
		if (_head == NULL)
		{
			_head = new Node(data);
			_tail = _head;
		}
		else
		{
			Node* cur = new Node(data); 
			_tail->_next = cur;
			_tail = cur;
		}
	}
	void PopBack()
	{
		if (_head == _tail)
		{
			if (_head == _tail == NULL)
			{
				return;
			}
			else
			{
				delete _head;
				_head = NULL;
				_tail = NULL;
			}
		}
		else
		{
			Node* cur = _head;
			while (cur)
			{
				Node* next = cur->_next;
				if (next == _tail)
				{
					delete _tail;
					_tail = NULL;
					_tail = cur;
					_tail->_next = NULL;
				}
				cur = cur->_next;
			}
		}
	}
	void PushFront(DataType data)
	{
		if (_head ==  NULL)
		{
			_head = _tail = new Node(data);
			return;
		}
		else
		{
			Node* cur = new Node(data);
			cur->_next = _head;
			_head = cur;
		}
	}
	Node* Find(DataType data)
	{
		Node* cur = _head;
		while (cur)
		{
			if (cur->_data == data)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}
	void Insert(Node* pos, DataType data)
	{
		if (_head == NULL)
		{
			PushFront(data);
		}
		else
		{
			Node* cur = new Node(data);
			Node* tmp = _head;
			while (tmp)
			{
				if (tmp->_next == pos)
				{
					tmp->_next = cur;
					cur->_next = pos;
				}
				tmp = tmp->_next;
			}
		}
	}
	void PopFront()
	{
		if (_head == NULL)
		{
			return;
		}
		else if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node* cur = _head;
			_head = cur->_next;
		     delete cur;
		}
	}
	void Erase(Node* pos)
	{
		
		if (_head == NULL)
		{
			return;
		}
		if (_head == _tail)
		{
			PopBack();
		}
		else
		{
			Node* tmp = _head;
			while (tmp->_next != pos)
			{
				tmp = tmp->_next;
			}
			tmp->_next = pos->_next;
			delete pos;
		}


	}
	void Destory()
	{
		Node* cur = _head;
		while (cur)
		{
			Node* del = cur;
			cur = cur->_next;
			delete del;
			del = NULL;
		}
		_head = NULL;
	}
	void Print()
	{
		Node* cur = _head;
		while (cur)
		{
			cout << cur->_data << "->";
			cur = cur->_next;
		}
		cout <<"NULL"<< endl;
	}
private:
	Node* _head;
	Node* _tail;

};

int main()
{
	SList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushFront(0);
	SListNode* node = s1.Find(2);
	//s1.Insert(node, 3);
	s1.Erase(node);
	//s1.PopFront();
	//s1.PopBack();
	s1.Print();
	//SList s2 = s1;;
	//s2.Print();

	return 0;
}