template<class T>
class ScopedPtr
{
public:
	ScopedPtr()
	{}
	~ScopedPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}
	T& operator*()
	{
		return *_ptr;
	}
	T*operator->()
	{
		return _ptr;
	}
protected:
	ScopedPtr(ScopedPtr<T>& s);
	ScopedPtr<T> operator=(ScopedPtr<T>& s);
protected:
	T* _ptr;
};

void TestScopedPtr()
{
	ScopedPtr<int> sp1;
	//ScopedPtr<int> sp2(sp1);
}