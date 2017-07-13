template <class T>
class SymmetricMatrix
{
private:
    size_t _N;
	vector<T> _a;
public:
	SymmetricMatrix(T* a, size_t N)
		:_N(N)
	{
		_a.reserve(N * 2 + 3);
		for (size_t i=0; i < N; ++i)
		{
			for (size_t j=0; j < N; ++j)
			{
				if (i >= j)
				{
					_a.push_back(a[i*N + j]);
				}
				else
				{
					break;
				}
			}
		}
	}
	T& Access(size_t i, size_t j)
	{
		if (i < j)
		{
			swap(i, j);
		}
		return _a[i*(i + 1) / 2 + j];
	}
	void Display()
	{
		for (size_t i = 0; i < _N; ++i)
		{
			for (size_t j=0; j < _N; ++j)
			{
				if (i >= j)
				{
					cout << Access(i, j) << " ";
				}
				else
				{
					cout << Access(j, i) << " ";
				}
			}
			cout << endl;
		}
	}

};

void TestS()
{
	int a[3][3] = { { 5, 8, 4 }, { 8, 3, 6 }, { 4, 6, 1 } };
	SymmetricMatrix<int> ma(((int* )a),3);
	ma.Display();
}