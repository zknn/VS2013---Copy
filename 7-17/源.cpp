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
	//删除无头单链表的非尾节点
	//单链表只有一个指向，所以无法或许要删除节点的前一个节点，所以可以将要删除的节点与其下一个节点交换，然后删除下一个节点
	void Erase(Node* del)
	{
		assert(del&&del->_next);
		Node* cur = del;
		Node* next = cur->_next;
		cur->_data = next->_data;
		cur->_next = next->_next;
		delete next;
	}
	//从尾到头打印单链表   借助栈来实现，根据栈的特性
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


//复杂链表
typedef int DataType;
typedef struct ComplexNode{

	DataType _data; // 数据 

	struct ComplexNode * _next; // 指向下一个节点的指针 

	struct ComplexNode * _random; // 指向随机节点（可以是链表中的任意节点 or 空） 

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
		cout << "节点数值为：" << head->_data << " ";
		if (head->_random)
		{
			cout << "节点的random节点的数值为：" << (head->_random)->_data << endl;
		}
		else
		{
			cout << "该节点的random指向为NULL" << endl;
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
	CopyNodeNext(head);  //复制节点
	CopyNodeRandom(head);  //复制随机指针的指向
	return Divide(head);  //分离好
}


//复杂链表的测试
void test()
{
	//生成复杂链表
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
	//复制复杂链表
	CNode* head=Copy(node1);
	cout << "复制后的复杂链表" << endl;
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
	//测试删除无头单链表的非尾节点
	cout << " 测试删除无头单链表的非尾节点" << endl;
	Node* ret =l. Find(3);
	l.Erase(ret);
	l.Print();
	//从尾到头打印单链表
	cout << "从尾到头打印单链表" << endl;
	l.RePrint();
	cout << "复杂链表的测试" << endl;
	test();
	return 0;
}

