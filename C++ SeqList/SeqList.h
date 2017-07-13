#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<assert.h>
using namespace std;

typedef int DataType;
class SeqList
{
private:
	DataType* _a;
	size_t _size;
	size_t _capacity;
public:
	SeqList()
		:_a(NULL)
		, _size(0)
		, _capacity(0)
	{ 
	}
	~SeqList()
	{
		if (_a)
		{
			free(_a);
		}
	}
	SeqList(const SeqList& s)
	{
		if (_a)
		{
			_a = (DataType*)malloc(sizeof(DataType)*s._size);
			memcpy(_a, s._a, sizeof(DataType)*s._size);
		}
		else
		{
			_a = NULL;
		}
		_size = s._size;
		_capacity = s._capacity;
	}
	void PushBack(DataType data)
	{
		_CheckCapacity();
		_a[_size] = data;
		++_size ;
	}
	void _CheckCapacity()
	{
		if (_size == _capacity)
		{
			_capacity = _capacity * 2 + 3;
			_a = (DataType*)realloc(_a, _capacity*sizeof(DataType));
		}
	}
	void Print()
	{
		for (size_t i = 0; i < _size; i++)
		{
			cout << _a[i] << "->";
		}
		cout << "NULL";
		cout << endl;
	}
	void Insert(size_t pos,DataType data)
	{
		assert(pos < _size);
		_CheckCapacity();
		size_t i =0 ;
		for (i = _size; i>pos; i--)
		{
			_a[i] = _a[i - 1];
		}
		_a[pos] = data;
		_size++;

	}
	int Find(DataType data)
	{
		DataType i = 0;
		for (i = 0; i < _size; i++)
		{
			if (_a[i] == data)
			{
				printf("找到了\n");
				return i;
			}
		}
		return NULL;
	}
	void Erase(DataType pos)
	{
		assert(_a != NULL);
		if (_size == 0)
		{
			printf("当前顺序表为空，无法进行删除操作\n");
		}
		for (size_t i = pos; i < _size; i++)
		{
				_a[i] = _a[i +1];
				
		}
		_size--;
	}
};

void test()
{
	SeqList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.Insert(1, 4);
	s1.Insert(1, 0);
	//s1.Erase(1);
	s1.Print();
	int i =s1. Find(2);

}