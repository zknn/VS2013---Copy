#include "seqlist.h"
template<class T,class Container>
class Stack
{
public:
	void Push(const T& data)
	{
		_con.PushBack(data);
	}
	void Pop()
	{
		_con.PopBack();
	}
	T& Front()
	{
		return _con.Front();
	}
		const T& Top()
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

void TestStack()
{
	Stack<int, SeqList<int>> l;
	l.Push(0);
	l.Push(1);
	l.Push(2);
	l.Push(3);
	cout << l.Size() << endl;
	while (!l.Empty())
	{
		cout << l.Top() << " ";
		l.Pop();
	}
	cout << endl;
}