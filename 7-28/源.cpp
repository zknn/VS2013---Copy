#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

struct Node
{
	int _data;
	Node* _left;
	Node* _right;
	Node(int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
//重建二叉树
Node* Construct(int* StartPrevOrder, int* EndPrevOrder, int* StartInOrder, int* EndInOrder);
Node* ConstructBinary(int* PrevOrder, int* InOrder,int length)
{
	if (PrevOrder == NULL || InOrder == NULL || length < 0)
		return NULL;
	return Construct(PrevOrder, PrevOrder + length - 1, InOrder, InOrder + length - 1);
}
Node* Construct(int* StartPrevOrder, int* EndPrevOrder, int* StartInOrder, int* EndInOrder)
{
	int rootdata = StartPrevOrder[0];
	Node* root = new Node(rootdata);
	if (StartPrevOrder == EndPrevOrder)
	{
		if (StartInOrder == EndInOrder&&*StartPrevOrder == *StartInOrder)
			return root;
		else
		{
			cout << "输入数据出错" << endl;
			return NULL;
		}
	}
	int* rootInOrder = StartInOrder;
	while (rootInOrder <= EndInOrder&&*rootInOrder != rootdata)
	{
		++rootInOrder;
	}
	if (rootInOrder == EndInOrder&&*rootInOrder != rootdata)
	{
		cout << "输入数据出错" << endl;
		return NULL;
	}
	int leftlength = rootInOrder - StartInOrder;
	int* leftPrevOrderEnd = StartPrevOrder + leftlength;
	if (leftlength > 0)
		root->_left = Construct(StartPrevOrder + 1, leftPrevOrderEnd, StartInOrder, rootInOrder - 1);
	if (leftlength < EndPrevOrder - StartPrevOrder)
		root->_right = Construct(leftPrevOrderEnd + 1, EndPrevOrder, rootInOrder + 1, EndInOrder);
	return root;
}

void test()
{
	int prev[] = { 1, 2, 3, 4, 5, 6, 7 };
	int In[] = { 3, 2, 4, 1, 6, 5, 7 };
	int size = sizeof(prev) / sizeof(prev[0]);
	Node* root = ConstructBinary(prev, In, size);
}

int main()
{
	test();
	return 0;
}
