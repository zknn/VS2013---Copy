#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//1.借助数组实现栈
template<class T>
class StackArr
{
public:
	StackArr()
	:_a(NULL)
	, _size(0)
	, _capacity(0)
   {}
	void Push(T data)
	{
		checkcapacity();
		_a[_size] = data;
		_size++;
	}
	void Pop()
	{
		if (_size)
		{
			_size--;
			return;
		}
		cout << "栈为空" << endl;
	}

	void checkcapacity()
	{
		_capacity = _capacity * 2 + 3;
		T* tmp = new T[_capacity];
		if (_a)
		{
			
			for (int i = 0; i < _size; i++)
			{
				tmp[i] = _a[i];
			}
			delete[] _a;
		}
		_a = tmp;
	}
	int Size()
	{
		return _size ;
	}
	bool Empty()
	{
		return _size > 0 ? true : false;
	}
	T Top()
	{
		return _a[--_size];
	}
protected:
	T* _a;
	int _size;
	int _capacity;
};
void testStackArr()
{
	StackArr<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	cout << s.Size() << endl;
	cout << s.Empty() << endl;
	cout << s.Top() << endl;
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	cout << s.Empty() << endl;

}

#include <stack>
//2.包含min函数的栈
class StackMin
{
public:
	void Push(int data)
	{
		data_stack.push(data);
		if (min_stack.empty() == true)
		{
			min_stack.push(data);
		}
		else if (min_stack.empty() == false && min_stack.top()>=data)
		{
			min_stack.push(data);
		}
	}
	void Pop()
	{
		if (data_stack.empty() == true)
		{
			cout << "栈为空" << endl;
			return;
		}
		if (min_stack.empty() == false && min_stack.top() == data_stack.top())
		{
			data_stack.pop();
			min_stack.pop();
		}
		else
		{
			data_stack.pop();
		}
	}
	int Min()
	{
		return min_stack.top();
	}
protected:
	stack<int> data_stack;
	stack<int> min_stack;
};
void testStackMin()
{
	StackMin s;
	s.Push(7);
	s.Push(-1);
	s.Push(2);
	s.Push(0);
	s.Push(4);
	cout << s.Min() << endl;
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
}

//3.栈的压入和弹出序列
bool IsPoporder(const int* pushorder, const int* poporder, int length)
{
	bool possible = false;
	if (pushorder != NULL&&poporder != NULL&&length > 0)
	{
		const int* pushnext = pushorder;
		const int* popnext = poporder;
		stack<int> data_stack;
		while (popnext - poporder < length)
		{
			while (data_stack.empty() || data_stack.top() != *popnext)
			{
				if (pushnext - pushorder == length)
					break;
				data_stack.push(*pushnext);
				pushnext++;
			}
			if (data_stack.top() != *popnext)
				break;
			data_stack.pop();
			popnext++;
		}
		if (data_stack.empty() && popnext - poporder == length)
		{
			possible = true;
		}
	}
	return possible;
}

void testIspoporder()
{
	int push[] = { 1, 2, 3, 4, 5 };
	int pop[] = { 4, 5, 3, 2, 1 };
	cout << IsPoporder(push, pop, sizeof(push) / sizeof(push[0])) << endl;   //1 true
	int pop1[] = { 4, 3, 5, 1, 2 };
	cout << IsPoporder(push, pop1, sizeof(push) / sizeof(push[0])) << endl;   //0 false
}

//4.用两个栈模拟实现一个队列
class SQueue
{
public:
	void Push(int data)
	{
		pushstack.push(data);
	}
	void Pop()  //为检测删除是否正确
	{
		if (pushstack.empty() == true && popstack.empty() == true)
		{
			cout << "当前队列为空" << " ";
			return ;
		}
		if (popstack.empty() == true)
		{
			while (pushstack.empty() == false)
			{
				popstack.push(pushstack.top());
				pushstack.pop();
			}
		}
		cout << "删除" << popstack.top() << endl;
		popstack.pop();
	}
private:
	stack<int> pushstack;
	stack<int> popstack;
};
void testSQueue()
{
	SQueue q;
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

#include <queue>
//5.两个队列实现一个栈
class QStack
{
public:
	void Push(int data)
	{
		q1.push(data);
	}
	void Pop()
	{
		if (q1.empty() == true && q2.empty() == true)
		{
			cout << "当前栈为空" << endl;
			return;
		}
		if (!q1.empty())
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			cout << "删除" << q1.front() << endl;
			q1.pop();
			while (q2.empty() == false)
			{
				q1.push(q2.front());
				q2.pop();
			}
		}
	}
private :
	queue<int>  q1;
	queue<int> q2;
};

void testQStack()
{
	QStack s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Pop();  //4
	s.Pop();  //3
	s.Pop();   //2
	s.Pop();//1
	s.Pop();  //空
}

//6.用数组实现队列(实现尾插头删)
template<class T>
class QueueArr
{
public:
	QueueArr()
		:_a(NULL)
		, _size(0)
		, _capacity(0)
	{}
	void Push(T data)
	{
		checkcapacity();
		_a[_size] = data;
		++_size;
	}
	void Pop()
	{
		if (_size==0)
		{
			cout << "当前队列为空" << endl;
			return;
		}
		if (_size>0)
		{
			int i = 0;
			for (int i = 0; i < _size; ++i)
			{
				_a[i] = _a[i - 1];
			}
			--_size;
		}
	
	}
	void checkcapacity()
	{
		_capacity = _capacity * 2 + 3;
		T* tmp = new T[_capacity];
		if (_size>0)
		{
			for (int i = 0; i < _size; i++)
			{
				tmp[i] = _a[i];
			}
			delete[] _a;
		}
		_a = tmp;
	}
private:
	T* _a;
	int _size;
	int _capacity;
};
void testQueueArr()
{
	QueueArr<int> q;
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
#include <assert.h>
 //7.一个数组实现两个栈


template<class T>
class ArrayStack
{
public:
	ArrayStack()
		:_arr1(new T[1])
		, _size1(0)
		, _size2(0)
		, _capacity(1)
		, _sz(_capacity-1)
		
	{
		assert(_arr1);
		_arr2 = &_arr1[_capacity - 1];
	}
	~ArrayStack()
	{
		if (!_arr1)
		{
			delete[] _arr1;
			_size1 = 0;
			_capacity = 0;
			_size2 = 0;
			_sz = 0;
		}
	}
	void arr1_Push(T data)
	{
		checkcapacity();
		_arr1[_size1] = data;
		_size1++;
	}
	void arr2_Push(T data)
	{
		checkcapacity();
		_arr1[_capacity-_size2-1] = data;
		_size2++;
	}
	void arr1_Pop()
	{
		if (_size1 > 0)
		{
			_size1--;
		}
		else
		{
			cout << "栈1为空" << endl;
		}
	}
	void arr2_Pop()
	{
		if (_size2)
		{
			_size2--;
		}
		else
		{
			cout << "栈2为空" << endl;
		}
	}
	void arr1_Display()
	{
		for (int i = 0; i < _size1; i++)
		{
			cout << _arr1[i] << " ";
		}
		cout << "NULL"<<endl;
	}
	void arr2_Display()
	{
		for (int i = _capacity-1; i >_capacity-_size2-1; i--)
		{
			cout << _arr1[i] << " ";
		}
		cout <<"NULL"<< endl;
	}
	void Display()
	{
		for (int i = 0; i < _capacity; i++)
		{
			cout << _arr1[i] << " ";
		}
		cout << "NULL" << endl;
	}
	void checkcapacity()
	{
		if (&_arr1[_size1]==&_arr1[_capacity-_size2-1])
		{
			int s = _size2;
			int t_capacity = _capacity * 2 + 3;
			int t =t_capacity;
			T* tmp = new T[t_capacity];
			for (int i = 0; i < _size1; i++)
			{
				tmp[i] = _arr1[i];
			}
			while (s--)
			{
				tmp[t - 1] = _arr1[_capacity - 1];
				t--;
				_capacity--;
			}
			delete[] _arr1;
			_arr1 = tmp;
			_capacity = t_capacity;
			_arr2 = &_arr1[_capacity - 1];
			_sz = _capacity - 1;
		}
	}
private:
	T* _arr1;
	T* _arr2;
	int _size1;
	int _size2;
	int _capacity;   //两个栈共用的容量
	int _sz;
};

void testArrayStack()
{
	ArrayStack<int>  s;
	cout << "第一个栈" << endl;
	s.arr1_Push(1);
	s.arr1_Push(2);
	s.arr1_Push(3);
	s.arr1_Push(4);
	s.arr1_Display();   
	s.arr1_Pop();
	s.arr1_Pop();
	s.arr1_Pop();
	s.arr1_Display();   
	s.arr1_Pop();
	s.arr1_Pop();
	s.arr1_Pop();



	cout << endl << endl;

	cout << "第二个栈" << endl;
	s.arr2_Push(4);
	s.arr2_Push(3);
	s.arr2_Push(2);
	s.arr2_Push(1);
	s.arr2_Display();   //4  3  2  1 
	s.arr2_Pop();
	s.arr2_Pop();
	s.arr2_Pop();
	s.arr2_Display();   // 4
	s.arr2_Pop();
	s.arr2_Pop();
	s.arr2_Pop();

	cout << endl << endl;
}
int main()
{
	//testStackArr();
	//testStackMin();
	//testIspoporder();
	//testSQueue();
	//testQStack();
	//testQueueArr();
	testArrayStack();
	return 0;
}