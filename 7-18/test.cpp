#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <stack>
#include <queue>

//两个栈实现一个队列
class Queue
{
public:
	void Push(int data)
	{
		s1.push(data);
	}
	void Pop()
	{
		if (!s2.empty())
		{
			s2.pop();
		}
		else
		{
			if (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
			else
			{
				return;
			}
		}
		s2.pop();
	}
protected:
	stack<int> s1;
	stack<int> s2;
};

void testQueue()
{
	Queue q;
	q.Push(0);
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
}

//两个队列实现一个栈

class Stack
{
public:
	void Push(int data)
	{
		q1.push(data);
	}
	void Pop()   //以q2做为中转,q1进行插入和删除
	{
		int tmp;
		if (!q1.empty())
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			tmp = q1.front();
			q1.pop();
			while (!q2.empty())
			{
				q1.push(q2.front());
				q2.pop();
			}
		}
	}

protected:
	queue<int> q1;
	queue<int> q2;
};
void testStack()
{
	Stack s;
	s.Push(0);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();

}

//替换字符串中的空格为$$$
//1.通过创建新的字符串
void changeblack(char* s1, char* s2)
{
	while (*s1)
	{
		if (*s1 != ' ')
		{
			*s2 = *s1;
			s2++;
		}
		else
		{
			strcpy(s2, "$$$");
			s2 += 3;
		}
		s1++;
	}
	*s2 = '\0';
}

//在原本的字符串上进行修改
void change(char* s, int length)
{
	if (s == NULL || length <= 0)
	{
		return;
	}
	int Olength = 0;  //原本字符串的长度
	int numberblack = 0;    //记录空格数目
	int i = 0;
	while (s[i] != '\0')
	{
		++Olength;
		if (s[i] == ' ')
		{
			++numberblack;
		}
		++i;
	}
	int newlength = Olength + numberblack * 2;  //新字符串中的字符长度
	if (newlength >length)
		return;
	int Oindex = Olength;    //原本字符串的下标
	int Nindex = newlength;  //新字符串的下标
	while ((Oindex >= 0) && (Nindex>Oindex))
	{
		if (s[Oindex] == ' ')
		{
			s[Nindex--] = '$';
			s[Nindex--] = '$';
			s[Nindex--] = '$';
		}
		else
		{
			s[Nindex--] = s[Oindex];
		}
		--Oindex;
	}
}

int main()
{
	const int length = 50;
	char arr[length] = "hello world ";
	char s[100];
	changeblack(arr, s);
	cout << s << endl;
	change(arr, length);
	cout << arr << endl;
	testQueue();
	testStack();
	return 0;
}