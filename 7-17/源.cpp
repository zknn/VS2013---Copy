#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
using namespace std;
#include <assert.h>
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
			while (cur->_next)
			{
				cur = cur->_next;
			}
			cur->_next = new Node(data);
			cur->_next->_next = NULL;
		}
	}
	Node* Find(int data)
	{
		Node* cur = _root;
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
	void Print()
	{
		Node* cur = _root;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << "NULL" << endl;
	}
	//ɾ����ͷ������ķ�β�ڵ�
	//������ֻ��һ��ָ�������޷�����Ҫɾ���ڵ��ǰһ���ڵ㣬���Կ��Խ�Ҫɾ���Ľڵ�������һ���ڵ㽻����Ȼ��ɾ����һ���ڵ�
	void Erase(Node* del)
	{
		assert(del&&del->_next);
		Node* cur = del;
		Node* next = cur->_next;
		cur->_data = next->_data;
		cur->_next = next->_next;
		delete next;
	}
	//��β��ͷ��ӡ������   ����ջ��ʵ�֣�����ջ������
	void RePrint()
	{
		stack<Node*> s;
		Node* cur = _root;
		while (cur)
		{
			s.push(cur);
			cur = cur->_next;
		}
		while (!s.empty())
		{
			cout << (s.top())->_data << " ";
			s.pop();
		}
		cout << "NULL" << endl;
	}
protected:
	Node* _root;
};


//��������
typedef int DataType;
typedef struct ComplexNode{

	DataType _data; // ���� 

	struct ComplexNode * _next; // ָ����һ���ڵ��ָ�� 

	struct ComplexNode * _random; // ָ������ڵ㣨�����������е�����ڵ� or �գ� 

}CNode;

CNode* CreateNode(DataType data)
{
	CNode* node = new CNode();
	node->_data = data;
	node->_next = NULL;
	node->_random = NULL;
	return node;
}
void BulidNode(CNode* node, CNode* next, CNode* random)
{
	assert(node);
	node->_next = next;
	node->_random = random;
}

void Print(CNode* head)
{
	assert(head);
	while (head)
	{
		cout << "�ڵ���ֵΪ��" << head->_data << " ";
		if (head->_random)
		{
			cout << "�ڵ��random�ڵ����ֵΪ��" << (head->_random)->_data << endl;
		}
		else
		{
			cout << "�ýڵ��randomָ��ΪNULL" << endl;
		}
		head = head->_next;
	}
}
void CopyNodeNext(CNode* head)
{
	CNode* cur = head;
	while (cur)
	{
		CNode* copy = new CNode();
		copy->_data = cur->_data;
		copy->_next = cur->_next;
		copy->_random = NULL;
		cur->_next = copy;
		cur = copy->_next;
	}
}
void CopyNodeRandom(CNode* head)
{
	CNode* cur = head;
	while (cur)
	{
		CNode* copy = cur->_next;
		if (cur->_random)
		{
			copy->_random = cur->_random->_next;
		}
		cur = copy->_next;
	}
}
CNode* Divide(CNode* head)
{
	CNode* cur = head;
	CNode* copy = NULL;
	CNode* node = NULL;
	if (cur)
	{
		copy = node = cur->_next;
		cur->_next = node->_next;
		cur = cur->_next;
	}
	while (cur)
	{
		node->_next = cur->_next;
		node = node->_next;
		cur->_next = node->_next;
		cur = cur->_next;
	}
	return copy;
}

CNode* Copy(CNode* head)
{
	CopyNodeNext(head);  //���ƽڵ�
	CopyNodeRandom(head);  //�������ָ���ָ��
	return Divide(head);  //�����
}


//��������Ĳ���
void test()
{
	//���ɸ�������
	CNode* node1 = CreateNode(0);
	CNode* node2 = CreateNode(1);
	CNode* node3 = CreateNode(2);
	CNode* node4 = CreateNode(3);
	CNode* node5 = CreateNode(4);
	BulidNode(node1, node2, NULL);
	BulidNode(node2, node3, node4);
	BulidNode(node3, node4, node5);
	BulidNode(node4, node5, NULL);
	BulidNode(node5, NULL, NULL);
	//      |------->|
	//  0 - 1 - 2 - 3 - 4 - NULL
	//          |------->|
	Print(node1);
	//���Ƹ�������
	CNode* head=Copy(node1);
	cout << "���ƺ�ĸ�������" << endl;
	Print(head);
}
int main()
{
	List l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	//����ɾ����ͷ������ķ�β�ڵ�
	cout << " ����ɾ����ͷ������ķ�β�ڵ�" << endl;
	Node* ret =l. Find(3);
	l.Erase(ret);
	l.Print();
	//��β��ͷ��ӡ������
	cout << "��β��ͷ��ӡ������" << endl;
	l.RePrint();
	cout << "��������Ĳ���" << endl;
	test();
	return 0;
}

