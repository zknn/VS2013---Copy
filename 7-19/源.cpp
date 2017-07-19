#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>

//使用数组建立一个栈
template<class T>
class Stack
{
public:
	Stack()
		:_a(NULL)
		, _size(0)
		, _capacity(0)
	{}
	void Push(T data)   //相当于尾插
	{
		checkcapacity();
		_a[_size++] = data;
	}
	void checkcapacity()
	{
		_capacity = _capacity * 2 + 3;
		T* tmp = new T[_capacity];
		if (_a)
		{
			for (int i = 0; i < _size; ++i)
			{
				tmp[i] = _a[i];
			}
			delete[] _a;
		}
		_a = tmp;
	}
	void Pop()   //相当于尾删
	{
		assert(_size);
		_size--;

	}
	T& Top()
	{
		return _a[_size - 1];
	}
	bool Empty()
	{
		return _size < 0 ? false : true;
	}
protected:
	T* _a;
	int _size;
	int _capacity;
};


#include <stack>
class MinStack
{
public:
	void Push(int data)
	{
		s1.push(data);
		if (s2.empty() == true)
		{
			s2.push(data);
		}
		else
		{
			if (data <= s2.top())
			{
				s2.push(data);
			}
		}
	}
	void Pop()
	{
		if (s1.empty() == true)
		{
			return;
		}
		if (s1.empty() == false && s2.top() == s1.top())
		{
			s2.pop();
		}
		s1.pop();
	}
	bool Empty()
	{
		return s1.empty();
	}
	int min()
	{
		return s2.top();
	}
protected:
	stack<int> s1;  //作为数据栈
	stack<int> s2;  // 作为最小栈
};


void testMinStack()
{
	MinStack s;
	s.Push(0);
	s.Push(1);
	s.Push(-1);
	s.Push(3);
	s.Push(4);
	cout << s.min() << endl;
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	cout << s.Empty() << endl;
}



char testchar(char* a)  //考虑哈希表的方式 借助一个数组，由于char类型共有256个，所以数组大小为256，根据下标找到每个字符对应位置，将其数值+1
{
	if (a == NULL)
		return '\0';
	const int length = 256;
	int ufs[length] = { 0 };
	int i = 0;
	char* s = a;
	while (*s != '\0')
	{
		ufs[*(s++)]++;
	}
	s = a;
	while (*s != '\0')
	{
		if (ufs[*s] == 2)
			return *s;
		++s;
	}
	return '\0';
}
int main()
{
	testMinStack();
	char a[] = "abcdefabcdefabc";
	cout << testchar(a) << endl;
	return 0;
}



