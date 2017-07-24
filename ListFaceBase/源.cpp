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
	void PushFront(int data)  //ͷ��
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
	void PushBack(int data)  //β��
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
	void PopBack()   //βɾ
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
	void PopFront()  //ͷɾ
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
	//��β��ͷ��ӡ������
	void Tail()
	{
		cout << "��β��ͷ��ӡ������ " ;
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
	//��ת������
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
	Node*  Find(int data)   //����
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
	void Erase(int data)  //ɾ����ͷ��β�ڵ�
	{
		Node* cur = _head;
		Node* node = Find(data);
		if (node == NULL)
		{
			cout << "û�иýڵ�" << endl;
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
	void Insert(int data, Node* pos)  //��һ���ڵ�ǰ����ڵ�
	{
		Node* node = new Node(data);
		Node* next = pos->_next;
		pos->_next = node;
		node->_next = next;
		swap(pos->_data, node->_data);
	}
	void Sort()//����     ����
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
	Node* _Merage(Node* head1,Node* head2)//�ϲ�������
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
	void JosephCycle(int k)//Լɪ��  ʱ�临�Ӷ�ΪO��kn)  
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
			cout << "ɾ���ڵ�" << cur->_data << endl;
			del = cur->_next;
			cur->_data = cur->_next->_data;
			cur->_next = cur->_next->_next;
			delete del;
		}
		cout << "ʣ��ڵ�Ϊ��" << cur->_data << endl;
	}
	void Joseph(int k)  //ʱ�临�Ӷ�ΪO(n)
	{
		int size = Size();
		if (k > size)
			return;
		int last = 0;
		for (int i = 2; i <= size; i++)
		{
			last = (last + k) % i;
		}
		cout << "ʣ����Ϊ�� " << last << endl;
	}
	//�����м�ڵ�
	void FindMid()  //����ָ��
	{
		Node* fast = _head;
		Node* slow = _head;
		while (fast->_next&&slow->_next)
		{
			fast = fast->_next->_next;
			slow = slow->_next;
		}
		cout << "�м�ڵ��� " << slow->_data << endl;
	}
	//���ҵ�����K���ڵ�
	void FindK(int k)  //ǰ��ָ��
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
		cout << "�ڵ�����" << k << "���ڵ��ǣ�" <<slow->_data<< endl;
	}

	//�ж����������ཻ
	void Cross(List l)  //����ջ
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
				cout << "������Ľ���Ϊ�� " << slow->_data << endl; 
				return;
			}
			fast = fast->_next;
			slow = slow->_next;
		}
		cout << "û�н���" << endl;
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
					cout << "��������Ľ���Ϊ��" << cur1->_data << endl;
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
					cout << "��������Ľ���Ϊ��" << cur2->_data << endl;
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
			cout << "��ǰ����Ϊ��" << endl;
		}
	}
private:
	Node* _head;
};

void testPushFront()  //����ͷ��
{
	List l;
	l.PushFront(5);
	l.PushFront(4);
	l.PushFront(3);
	l.PushFront(2);
	l.PushFront(1);
	l.Print();
}
void testPushBack()  //����β��
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
}
void testPopBack()//����βɾ
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
void testPopFront()  //����ͷɾ
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
void testTail()  //���Դ�β��ͷ��ӡ������
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
void testReverse()//���Է�ת������
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
void testFind()  //���Բ���
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	if (l.Find(5) == NULL)
		cout << "û�иýڵ�" << endl;
	else
		cout << "�ҵ��ˣ��ýڵ��� " << l.Find(5)->_data << endl;
}
void testErase()  //����ɾ��
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	int k;
	cout << "������Ҫɾ������ ";
	cin >> k;
	l.Erase(k);
	l.Print();
}
void testInsert()  //���Բ��뺯��
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
void testSort()  //��������
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	l.Sort();
	cout << "��������" << endl;
	l.Print();
}
void testMerage()//���Ժϲ�
{
	List l;
	l.PushBack(6);
	l.PushBack(1);
	l.PushBack(7);
	l.PushBack(3);
	l.PushBack(4);
	l.Sort();
	cout << "l1�����: ";
	l.Print();
	List s;
	s.PushFront(9);
	s.PushFront(0);
	s.PushFront(5);
	s.PushFront(2);
	s.PushFront(10);
	s.Sort();
	cout << "l2�����: ";
	s.Print();
	l.Merage(s);
	cout << "�ϲ��� ";
	l.Print();
}
void testJosephCycle()//����Լɪ��
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
void testFindMid()  //���Բ����м�ڵ�
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
void testFindK()//���Բ��ҵ�����K���ڵ�
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
void testCross()  //�������һ������
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