
template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}
	~AutoPtr()
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
	AutoPtr(AutoPtr<T>& ap)
	{
		//转移管理权
		_ptr = ap._ptr;
		ap._ptr = NULL;
	}
	AutoPtr<T>& operator = (AutoPtr<T>&  ap)
	{
	
			delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
			return *this;
		
	}
	void display()
	{
		cout << *_ptr << endl;
	}
protected:
	T* _ptr;
};


void TestAutoPtr()
{
	AutoPtr<int> ap1(new int(10));
	AutoPtr<int> ap2 = ap1;
	AutoPtr<int> ap3(new int(20));
	ap3 = ap2;

}