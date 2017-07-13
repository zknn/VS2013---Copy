#include "list.h"
#include <iostream>
using namespace std;
template<class T, class Container>
class Queue
{
public:
	void Push(const T& data)
	{
		_con.PushBack(data);
	}
	void Pop()
	{
		_con.PopFront();
	}
	T& Front()
	{
		return _con.Front();
	}
	T& Back()
	{
		return _con.Back();
	}
	size_t Size()
	{
		return _con.Size();
	}
	bool Empty()
	{
		return _con.Empty();
	}
protected:
	Container _con;
};

void TestQueue()
{
	Queue<int, List<int>> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	cout << q.Size() << endl;
	while (!q.Empty())
	{
		cout << q.Front() << " ";
		q.Pop();
	}
	cout << endl;
}