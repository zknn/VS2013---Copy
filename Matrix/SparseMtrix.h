
template<class T>
struct Triple
{
	T _value;
	size_t _row;
	size_t _col;
};
template<class T,size_t M,size_t N>
class SparseMatrix
{
	friend SparseMatrix<T, N, M>;
public:
	SparseMatrix()
	{}
	SparseMatrix<T,M,N>(T a[M][N], const T& invalid)
		:_invalid(invalid)
	{
		for (size_t i = 0; i < M; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				if (a[i][j] != invalid)
				{
					Triple<T> t;
					t._value = a[i][j];
					t._row = i;
					t._col = j;
					_a.push_back(t);
				}
			}
		}
	}
	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < M; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				if ((index < _a.size())&&(_a[index]._row == i)&&(_a[index]._col == j))
				{
					cout << _a[index]._value << " ";
					++index;
				}
				else
				{
					cout << _invalid <<" ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	//矩阵转置
	SparseMatrix<T,N,M> Transport()
	{
		SparseMatrix<T,N,M> sm;
		sm._invalid = _invalid;
		for (size_t i = 0; i < N; ++i)
		{
			size_t index = 0;
			while (index < _a.size())
			{
				if (_a[index]._col == i)
				{
					Triple<T> t;
					t._value = _a[index]._value;
					t._row = _a[index]._col;
					t._col = _a[index]._row;
					sm._a.push_back(t);
				}
				++index;
			}
		}
		return sm;
	}
	//快速转置
	SparseMatrix<T, N, M> FastTransport()
	{
		SparseMatrix<T, N, M>  sm;
		sm._invalid = _invalid;
		int rows[N] = { 0 };
		size_t index = 0;
		while (index < _a.size())
		{
			rows[_a[index]._col]++;
			++index;
		}
		int starts[N] = { 0 };
		starts[0]=0;
		for (size_t i = 1; i < N; ++i)
		{
			starts[i] = starts[i - 1] + rows[i - 1];
		}
			index = 0;
			sm._a.resize(_a.size());
			while (index < _a.size())
			{
				size_t row = _a[index]._col;
				Triple<T> t;
				t._value = _a[index]._value;
				t._col = _a[index]._row;
				t._row = _a[index]._col;
				sm._a[starts[row]++] = t;
				++index;
			}
		return sm;
	}
protected:
	vector<Triple<T>> _a;
	T _invalid;
};

void TestSp()
{
	int array[3][4] = { { 0, 0, 4,0}, { 8, 0, 6 ,0}, { 1, 0, 0,0} };
	SparseMatrix<int, 3, 4> sm(array, 0);
	sm.Display();
	SparseMatrix<int, 4, 3> tsm;
	tsm=sm.Transport();
	tsm.Display();
	SparseMatrix<int, 4, 3> Ftsm;
	Ftsm = sm.FastTransport();
	Ftsm.Display();
}