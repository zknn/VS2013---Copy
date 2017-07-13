#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

typedef int DataType;
template <typename T>
class SeqList
{
public:
	SeqList()
		:_a(NULL)
		, _size(0)
		, _capacity(0)
	{
		_a = new T[_size];
		_capacity = _size;
	}
	~SeqList()
	{
		if (_a)
		{
			delete[] _a;
			_a = NULL;
			_size = _capacity = 0;
		}
	}
	SeqList(const SeqList<T>& s)
	{
		_a = new T[s._szie];
		_size = s._size;
		_capacity = s._size;
	}
	SeqList& operator=(SeqList<T> s)
	{
		swap(_a, s._a);
		swap(_size, s._size);
		swap(_capacity, s._cpapcity);
		return *this;
	}
	void _checkcapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = _capacity * 2 + 3;
			T* tmp = new T[_capacity];
			if (_a)
			{
				for (DataType i=0; i < _size; i++)
				{
					tmp[i] = _a[i];
				}
				delete[] _a;
				_a = tmp;
			}
		}
	}
	void PushBack(const T& data)
	{
		_checkcapacity();
		_a[_size] = data;
		++_size;
	}
	void PopBack()
	{
		if (_a)
		{
			--_size;
		}
	}
	void PushFront(const T& data)
	{
		DataType i = _size;
		++_size;
		_checkcapacity();
		if (_a)
		{
			for (; i>=0; i--)
			{
				_a[i] = _a[i - 1];
			}
			_a[0] = data;
			
		}
	}
	void PopFront()
	{
		if (_a)
		{
			DataType i = 0;
			for (i = 0; i < _size; i++)
			{
				_a[i] = _a[i + 1];
			}
			--_size;
		}
	}
	int find(T data)
	{
		if (_a)
		{
			for (DataType i = 0; i < _size; i++)
			{
				if (_a[i] == data)
				{
					return i;
				}
			}
		}
	}
	void Insert(DataType pos, T data)
	{
		assert(pos < _size);
		_checkcapacity();
		if (_a)
		{
				for (DataType i =_size; i >pos; i--)
				{
					_a[i] = _a[i - 1];
				}
				_a[pos] = data;
				++_size;
		}
	}
	void Erase(DataType pos)
	{
		assert(pos < _size);
		if (_a)
		{
			for (DataType i = pos; i < _size; i++)
			{
				_a[i] = _a[i + 1];
			}
			--_size;
		}
	}

	T& Back()
	{
		assert(_size > 0);
		return _a[_size - 1];
	}

	size_t Size()
	{
		return _size;
	}

	bool Empty()
	{
		return _size == 0;
	}

	void print();
	
private:
	T* _a;
	DataType _size;
	DataType _capacity;
};
template<class T>
void SeqList<T>::print()
{
	for (size_t i = 0; i < _size; ++i)
	{
		cout << _a[i] << " ";
	}
	cout << endl;
}

//PushBack、PopBack
void Test1()
{
	SeqList<int> s1;
	s1.PushBack(0);
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.print();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.print();

}
//PopFront 、PushFront、find
void Test2()
{
	//SeqList<string> s1;
	//s1.PushBack("1111111111111111111111111111111111111111111111111111111111111111111111");
	//s1.PushBack("22");
	//s1.PushBack("33");
	//s1.PushBack("44");
	//s1.print();
	SeqList<int> s1;
	s1.PushBack(3);
	s1.PushFront(2);
	s1.PushFront(1);
	s1.PushFront(0);
	s1.print();
	//s1.PopFront();
	//s1.PopFront();
	//s1.PopFront();
	//s1.PopFront();
	//s1.PopFront();
	//s1.print();
	DataType i=s1.find(4);
	cout << i << endl;
}

//Insert、Erase
void Test3()
{
	SeqList<int> s1;
	s1.PushBack(0);
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.print();
	DataType i = s1.find(2);
	s1.Insert(2, 4);
	s1.print();
	s1.Erase(2);
	s1.print();
}