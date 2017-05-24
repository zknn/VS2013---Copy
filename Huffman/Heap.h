#include <vector>
template<class T>
struct Less
{
	bool operator()(const T& left, const T& right) const
	{
		return left < right;
	}
};
template<class T>
struct Greater
{
	bool operator()(const T& left, const T& right) const
	{
		return left > right;
	}
};

template <class T, class compare = Greater<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(T* a, size_t n)
	{
		_a.reserve(n);
		for (size_t i = 0; i < n; ++i)
		{
			_a.push_back(a[i]);
		}
		for (int i = ((_a.size() - 2) / 2); i >= 0; --i)  //找倒数第一个非叶子节点
		{
			AdjustDown(i);
		}
	}
	void AdjustDown(int index)  //向下调整算法
	{
		compare com;
	size_t  child = index * 2 + 1;
		int parent = index;
		while (child < _a.size())
		{
			if (child + 1 < _a.size() && com(_a[child + 1], _a[child])) //右孩子>左孩子
			{
				++child;
			}
			if (com(_a[child], _a[parent]))
			{
				swap(_a[child], _a[parent]);
				parent = child;
				child = child * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void Push(const T&  data)   //尾插
	{
		_a.push_back(data);
		AdjustUp(_a.size() - 1);
	}
	void Pop()
	{
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		AdjustDown(0);
	}
	void AdjustUp(int index)
	{
		compare com;
		int child = index;
		int parent = (index - 1) / 2;
		while (parent >= 0)
		{
			if (com(_a[child], _a[parent]))
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (parent - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	size_t size()
	{
		return _a.size();
	}
	bool empty()
	{
		return _a.empty();
	}
	T& Top()
	{
		assert(_a.size() > 0);
		return _a[0];
	}
	void IsHeap()
	{
		return _IsHeap(root);
	}
	bool _IsHeap()
	{
		if (root >= _a.size())
		{
			return true;
		}
		int left = 2 * root + 1;
		int right = 2 * root + 2;

		if (_left < _a.size())
		{
			if (_a[left]>_a[root])
			{
				return false;
			}
			if (right < _a.size())
			{
				if (_a[right]>_a[root])
				{
					return false;
				}
			}
		}
		return _IsHeap(left) && _IsHeap(right);
	}
protected:
	vector<T> _a;
};

//#include <vector> //堆为完全二叉树
//
//template <class T>
//struct Less                   //小堆
//{
//	bool operator()(const T& left,const T& right) const 
//	{
//		return left < right;
//	}
//};
//
//template <class T>
//struct Greater                //大堆
//{
//	bool operator()(const T& left, const T& right)const 
//	{
//		return left > right;
//	}
//};
//
//
//template<class T, class Compare = Greater<T>>
////template <class T>
//class Heap             //数组形式  //小堆
//{
//public:
//	Heap()
//	{}
//
//	Heap(T* a, size_t n)
//	{
//		_a.reserve(n);         //开辟n个字节的空间
//		for (size_t i = 0; i < n; ++i)
//		{
//			_a.push_back(a[i]);
//		}
//
//		//建堆    向下调整法
//		for (int i = (_a.size() - 2) / 2; i >= 0; --i)
//		{
//			AdjustDown(i);
//		}
//
//	}
//
//	void AdjustDown(int root)
//	{
//		Compare com;
//		int parent = root;
//		int child = parent * 2 + 1;       //左孩子
//		while (child<_a.size())
//		{
//			//if (child+1<_a.size()&&_a[child + 1] > _a[child])
//			if (child+1<_a.size()&&com(_a[child + 1],_a[child]))
//
//			{
//				++child;
//			}
//			//if (_a[child] > _a[parent])
//			if (com(_a[child],_a[parent]))
//			{
//				swap(_a[child], _a[parent]);
//				parent = child;
//				child = child * 2 + 1;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//
//	void Push(const T& x)
//	{
//		_a.push_back(x);
//		AdjustUp(_a.size()-1);
//	}
//
//	void Pop()
// 	{
//		swap(_a[0], _a[_a.size() - 1]);
//		_a.pop_back();
//		AdjustDown(0);
//	}
//
//	void AdjustUp(int child)
//	{
//		Compare com;
//		int parent = (child - 1) / 2;
//		while (parent >= 0)
//		{
//			//if (_a[child] > _a[parent])
//			if (com(_a[child] , _a[parent]))
//			{
//				swap(_a[parent], _a[child]);
//				child = parent;
//				parent = (child - 1) / 2;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//
//	size_t size()
//	{
//		return _a.size();
//	}
//
//	bool Empty()
//	{
//		return _a.empty();
//	}
//
//	T& Top()
//	{
//		assert(_a.size() > 0);
//		return _a[0];
//	}
//
//	bool IsHeap()
//	{
//		for (size_t i = 0; i <= ((_a.size() - 2) / 2); ++i)
//		{
//			if (_a[i] < _a[i * 2 + 1] || (i * 2 + 2) < _a.size() && _a[i] < _a[i * 2 + 2])
//			{
//				return false;
//			}
//		}
//			return true;
//		
//	}
//
//	bool _IsHeap(int root)
//	{
//		if (root >= _a.size())
//		{
//			return true;
//		}
//
//		int left = root * 2 + 1;
//		int right = root * 2 + 2;
//		if (left < _a.size())
//		{
//			if (_a[left]>_a[root])
//			{
//				return false;
//			}
//
//			if (right < _a.size())
//			{
//				if (_a[right]>_a[root])
//				{
//					return false;
//				}
//			}
//		}
//		return _IsHeap(left) && _IsHeap(right);
//	}
//protected:
//	vector<T> _a;
//};


//void TestHeap()
//{
//	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
//	Heap<int> s1(a, sizeof(a) / sizeof(a[10]));
//	Heap<int, Less<int>> s2(a, sizeof(a) / sizeof(a[0]));
//
//	/*cout << s1.IsHeap() << endl;
//	s1.Push(23);
//	cout << s1.IsHeap() << endl;
//	s1.Push(25);
//	cout << s1.IsHeap() << endl;
//	s1.Pop();
//	cout << s1.IsHeap() << endl;
//	*/
//
//}

//适配器
template<class T,class Container>
class Stack{};

//不是适配器

template<class T,class Compare=Greater<int>>
class PriorityQueue
{
	void Push(const T& x)
	{
		_hp.Push(x);
	}

	void Pop()
	{
		_hp.Pop();
	}

	T& Top()
	{
		return _hp.Top();
	}

protected:
	Heap<T, Compare> _hp;
};

//TopK问题
const size_t N = 10000;
const size_t k = 10;

void AdjustDown(int* heap, int n, int root)
{
	assert(heap);
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && heap[child + 1] > heap[child])
		{
			++child;
		}
		if (heap[child] > heap[parent])
		{
			swap(heap[child], heap[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void TopK()
{
	int a[N] = { 0 };
	for (size_t i = 0; i < N; ++i)
	{
		a[i] = rand() % N;
	}
	/*a[0] = N + 100;
	a[100] = N + 101;
	a[21] = N + 103;
	a[34] = N + 104;
	a[38] = N + 105;
	a[1000] = N + 103;
	a[2384] = N + 130;
	a[42] = N + 110;
	a[583] = N + 150;
	a[9999] = N + 121;*/

	int heap[k] = { 0 };
	for (size_t i = 0; i < k; ++i)
	{
		heap[i] = a[i];
	}
	//建堆
	for (int i = (k - 2) / 2; i >= 0; --i)
	{
		AdjustDown(heap, k, i);
	}

	for (size_t i = k; i < N; ++i)
	{
		if (a[i]>heap[0])
		{
			heap[0] = a[i];
			AdjustDown(heap, k, 0);
		}
		
	}
	for (size_t i = 0; i < k; ++i)
	{
		cout << heap[i] << " ";
	}
}

////堆排序
//void HeapSort(int* a, size_t n)
//{
//	assert(a);
//	//建堆
//	for (int i = (n - 2) / 2; i >= 0; --i)
//	{
//		AdjustDown(a, n, i);
//	}
//
//	/*for (int i = n; i >= 0; --i)
//	{
//		swap(a[1], a[i]);
//		AdjustDown(a, 1, i - 1);
//	}*/
//	//选择
//	int end = n - 1;
//	while (end > 0)
//	{
//		swap(a[0], a[end]);
//		AdjustDown(a, end, 0);
//		--end;
//	}
//}
//
//void Test()
//{
//	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
//	HeapSort(a, sizeof(a) / sizeof(a[10]));
//	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
//	{
//		cout << a[i] << " ";
//	}
//	cout << endl;
//}


