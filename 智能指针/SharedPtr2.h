template <class T>
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
		if (--*_refCount == 0)
		{
			cout << "delete" << endl;
			delete _refCount;
		}
	}
	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _refCount(sp._refCount)
	{
		(*_refCount)++;
	}
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
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
};

void TestSharedPtr2()
{
	SharedPtr<int>ap1(new int(10));
	SharedPtr<int> ap2(ap1);
	SharedPtr<int> ap3(new int(20));
	ap2 = ap3;
}