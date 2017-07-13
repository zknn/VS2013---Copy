#include <stdio.h>
template<class T>
class Delete
{
public:
	void operator()(T* ptr)
	{
		cout << "Delete" << endl;
		delete ptr;
		ptr = NULL;
	}
};
template<class T>
class DeleteArray
{
public:
	void operator()(T* ptr)
	{
		cout << "DeleteArray" << endl;
		delete[] ptr;
	}
};
template<class T>
class Free
{
public:
	void operator()(T* ptr)
	{
		cout << "Free" << endl;
		free(ptr);
	}
};
template<class T>
class Fclose
{
public:
	void operator()(T*& ptr)
	{
		cout << "Fclose" << endl;
		fclose(ptr);
		ptr = NULL;
	}
};
template<class T,class Del=Delete<T> >
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		, _refCount(new int(1))
	{}
	~SharedPtr()
	{
		Release();
	}
	T& operator*()
	{
		return *_ptr;
	}
	T*operator->()
	{
		return _ptr;
	}
	inline void Release()
	{
		if (--*_refCount==0)
		{
			_del(_ptr);
			delete _refCount;
			_refCount = NULL;
			
		}
	}
	SharedPtr(const SharedPtr<T, Del>& sp)
		:_ptr(sp._ptr)
		, _refCount(sp._refCount)
	{
		(*_refCount)++;
	}
	SharedPtr<T,Del>& operator=(const SharedPtr<T, Del>& sp)
	{
		if (_ptr != sp._ptr)
		{
			Release();
			_ptr = sp._ptr;
			_refCount = sp._refCount;
			(*_refCount)++;
		}
		return *this;
	}
protected:
	T* _ptr;
	int* _refCount;
	Del _del;
};

void TestSharedPtr()
{
	SharedPtr<int> ap1(new int(10));
	SharedPtr<int> ap2 ( ap1);
	SharedPtr<int> ap3(new int(20));
	ap2=ap3;
	SharedPtr<FILE, Fclose<FILE>> sp2(fopen("test.txt", "rb"));

}