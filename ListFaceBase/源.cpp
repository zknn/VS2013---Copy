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
		:_head(NULL)
	{}
	void PushFront(int data)  //头插
	{
		if (_head == NULL)
		{
			_head = new Node(data);
			return;
		}
		else
		{
			Node* cur = new Node(data);
			cur->_next = _head;
			_head = cur;
		}
	}
	void PushBack(int data)  //尾插
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
	void PopBack()   //尾删
	{
		if (_head == NULL)
		{
			return;
		}
		if (_head->_next == NULL)
		{
			delete _head;
			_head = NULL;
			return;
		}
			Node* cur = _head;
			Node* prev = NULL;
			while (cur->_next)
			{
				prev = cur;
				cur = cur->_next;
			}
			delete cur;
			cur = NULL;
			prev->_next = NULL;
	}
	void PopFront()  //头删
	{
		if (_head == NULL)
			return;
		if (_head->_next == NULL)
		{
			delete _head;
			_head = NULL;
			return;
		}
		Node* cur = _head->_next;
		delete _head;
		_head = cur;
	}
	//从尾到头打印单链表
	void Tail()
	{
		cout << "从尾到头打印单链表： " ;
		Node* cur = _head;
		stack<Node*> s;
		while (cur)
		{
			s.push(cur);
			cur = cur->_next;
		}
		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->_data << " ";
			s.pop();
		}
		cout << endl;
	}
	//反转单链表
	void Reverse()
	{
		Node* cur = _head;
		Node* end = _head;
		while (end->_next)
		{
			end = end->_next;
		}
		Node* prev = NULL;
		Node* stop = end->_next;
		while (cur != stop)
		{
			Node* next = cur->_next;
			cur->_next = prev;
			prev = cur;
			cur = next;
		}
		_head = end;
	}
	Node*  Find(int data)   //查找
	{
		Node* cur = _head;
		while (cur)
		{
			if (cur->_data == data)
				return cur;
			cur = cur->_next;
		}
		return NULL;
	}
	void Erase(int data)  //删除无头非尾节点
	{
		Node* cur = _head;
		Node* node = Find(data);
		if (node == NULL)
		{
			cout << "没有该节点" << endl;
			return;
		}
		Node* next = node->_next;
		while (cur->_next != node)
		{
			cur = cur->_next;
		}
		cur->_next = next;
		delete node;
	}
	void Insert(int data, Node* pos)  //在一个节点前插入节点
	{
		Node* node = new Node(data);
		Node* next = pos->_next;
		pos->_next = node;
		node->_next = next;
		swap(pos->_data, node->_data);
	}
	void Sort()//排序     降序
	{
		Node* cur = _head;
		Node* next = NULL;
		Node* end = NULL;
		if (_head == NULL || _head->_next == NULL)
			return;
		while (cur->_next!=end)
		{
			while (cur->_next!=end)
			{
				next = cur->_next;
				if (cur->_data < next->_data)
				{
					swap(cur->_data, next->_data);
				}
				cur = cur->_next;
			}
			end = cur;
			cur = _head;
		}
	}
	Node* Gethead()
	{
		return _head;
	}
	void Merage(List l)
	{
		Node* head1 = l.Gethead();
		Node* head = _Merage(_head, head1);
		_head = head;
	}
	Node* _Merage(Node* head1,Node* head2)//合并单链表
	{
		/*if (head1 == NULL&&head2 == NULL)
			return NULL;*/
		if (head1 == NULL )
			return head2;
		if (head2 == NULL)
			return head1;
		Node* root = NULL;
		if (head1->_data < head2->_data)
		{
			root = head2;
			root->_next = _Merage(head1, head2->_next);
		}
		else
		{
			root = head1;
			root->_next = _Merage(head1->_next, head2);
		}
		return root;
	}
	int Size()
	{
		int count = 0;
		Node* cur = _head;
		while (cur)
		{
			count++;
			cur = cur->_next;
		}
		return count;
	}
	void JosephCycle(int k)//约瑟夫环  时间复杂度为O（kn)  
	{
		Node* cur = _head;
		Node* del = NULL;
		while (1)
		{
			if (cur->_next == cur)
			{
				break;
			}
			for (int i = 0; i < k - 1; i++)
			{
				cur = cur->_next;
			}
			cout << "删除节点" << cur->_data << endl;
			del = cur->_next;
			cur->_data = cur->_next->_data;
			cur->_next = cur->_next->_next;
			delete del;
		}
		cout << "剩余节点为：" << cur->_data << endl;
	}
	void Joseph(int k)  //时间复杂度为O(n)
	{
		int size = Size();
		if (k > size)
			return;
		int last = 0;
		for (int i = 2; i <= size; i++)
		{
			last = (last + k) % i;
		}
		cout << "剩余数为： " << last << endl;
	}
	//查找中间节点
	void FindMid()  //快慢指针
	{
		Node* fast = _head;
		Node* slow = _head;
		while (fast->_next&&slow->_next)
		{
			fast = fast->_next->_next;
			slow = slow->_next;
		}
		cout << "中间节点是 " << slow->_data << endl;
	}
	//查找倒数第K个节点
	void FindK(int k)  //前后指针
	{
		if (_head == NULL || k == 0)
			return;
		Node* fast = _head;
		Node* slow = _head;
		for (int i = 0; i < k - 1; i++)
		{
			if (fast->_next)
				fast = fast->_next;
			else
				return;
		}
		while (fast->_next)
		{
			slow = slow->_next;
			fast = fast->_next;
		}
		cout << "第倒数第" << k << "个节点是：" <<slow->_data<< endl;
	}

	//判断两个链表相交
	void Cross(List l)  //借助栈
	{
		Node* head = l.Gethead();
		//Node* cur1 = _head;
		//Node* cur2 = head;
		Node* fast = _head;
		Node* slow = head;
		int size1 = Size();
		int size2 = l.Size();
		int size = size1 - size2;
		if (size2 > size1)
		{
			fast = head;
			slow = _head;
			size = size2 - size1;
		}
		for (int i = 0; i < size; i++)
		{
			fast = fast->_next;
		}
		while (slow&&fast)
		{
			if (fast->_data == slow->_data)
			{
				cout << "两链表的交点为： " << slow->_data << endl; 
				return;
			}
			fast = fast->_next;
			slow = slow->_next;
		}
		cout << "没有交点" << endl;
		/*if (size > 0)
		{
			for (int i = 0; i < size; i++)
			{
				cur1 = cur1->_next;
			}
			while (cur1&&cur2)
			{
				if (cur1->_data== cur2->_data)
				{
					cout << "两个链表的交点为：" << cur1->_data << endl;
					return;
				}
				cur1 = cur1->_next;
				cur2 = cur2->_next;
			}
		}
		else
		{
			for (int i = 0; i < abs(size); i++)
			{
				cur2 = cur2->_next;
			}
			while (cur1&&cur2)
			{
				if (cur1->_data == cur2->_data)
				{
					cout << "两个链表的交点为：" << cur2->_data << endl;
					return;
				}
				cur1 = cur1->_next;
				cur2 = cur2->_next;
			}
		}*/

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
		if (_head==NULL)
		{
			cout << "当前链表为空" << endl;
		}
	}
private:
	Node* _head;
};

void testPushFront()  //测试头插
{
	List l;
	l.PushFront(5);
	l.PushFront(4);
	l.PushFront(3);
	l.PushFront(2);
	l.PushFront(1);
	l.Print();
}
void testPushBack()  //测试尾插
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
}
void testPopBack()//测试尾删
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	l.PopBack();
	l.Print();
	l.PopBack();
	l.Print();
	l.PopBack();
	l.Print();
	l.PopBack();
	l.Print();
	l.PopBack();
	l.Print();
	l.PopBack();
	l.Print();
}
void testPopFront()  //测试头删
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	l.PopFront();
	l.Print();
	l.PopFront();
	l.Print();
	l.PopFront();
	l.Print();
	l.PopFront();
	l.Print();
	l.PopFront();
	l.Print();
	l.PopFront();
	l.Print();
}
void testTail()  //测试从尾到头打印单链表
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	l.Tail();
}
void testReverse()//测试反转单链表
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	l.Reverse();
	l.Print();
}
void testFind()  //测试查找
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	if (l.Find(5) == NULL)
		cout << "没有该节点" << endl;
	else
		cout << "找到了，该节点是 " << l.Find(5)->_data << endl;
}
void testErase()  //测试删除
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	int k;
	cout << "请输入要删除的数 ";
	cin >> k;
	l.Erase(k);
	l.Print();
}
void testInsert()  //测试插入函数
{

	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	Node* node=l.Find(2);
	l.Insert(5, node);
	l.Print();
}
void testSort()  //测试排序
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	l.Sort();
	cout << "降序排序" << endl;
	l.Print();
}
void testMerage()//测试合并
{
	List l;
	l.PushBack(6);
	l.PushBack(1);
	l.PushBack(7);
	l.PushBack(3);
	l.PushBack(4);
	l.Sort();
	cout << "l1排序后: ";
	l.Print();
	List s;
	s.PushFront(9);
	s.PushFront(0);
	s.PushFront(5);
	s.PushFront(2);
	s.PushFront(10);
	s.Sort();
	cout << "l2排序后: ";
	s.Print();
	l.Merage(s);
	cout << "合并： ";
	l.Print();
}
void testJosephCycle()//测试约瑟夫环
{
	List l;
	l.PushBack(6);
	l.PushBack(1);
	l.PushBack(7);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(0);
	l.PushBack(8);
	l.Print();
	Node* end = l.Find(8);
	Node* begin = l.Find(6);
	end->_next = begin;
	l.JosephCycle(3);
	List s;
	s.PushBack(6);
    s.PushBack(1);
	s.PushBack(7);
	s.PushBack(3);
	s.PushBack(4);
	s.PushBack(0);
	s.PushBack(8);
	s.Joseph(3);
}
void testFindMid()  //测试查找中间节点
{
	List l;
	l.PushBack(6);
	l.PushBack(1);
	l.PushBack(7);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(0);
	l.PushBack(8);
	l.Print();
	l.FindMid();
}
void testFindK()//测试查找倒数第K个节点
{
	List l;
	l.PushBack(6);
	l.PushBack(1);
	l.PushBack(7);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(0);
	l.PushBack(8);
	l.Print();
	l.FindK(2);
	l.FindK(3);
}
void testCross()  //测试求第一个交点
{
	List l;
	l.PushBack(6);
	l.PushBack(1);
	l.PushBack(7);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(0);
	l.PushBack(8);
	l.Print();
	List s;
	s.PushBack(2);
	s.PushBack(1);
	s.PushBack(4);
	s.PushBack(0);
	s.PushBack(8);
	s.Print();
	l.Cross(s);
	s.Cross(l);
}
int main()
{
	//testPushFront();
	//testPushBack();
	//testPopBack();
	//testPopFront();
	//testTail();
	//testReverse();
	//testFind();
	//testErase();
	//testInsert();
	//testSort();
	//testMerage();
	//testJosephCycle();
	//testFindMid();
	//testFindK();
	testCross();
	return 0;
}