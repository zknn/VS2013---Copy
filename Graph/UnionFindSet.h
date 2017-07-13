
class UnionFindSet
{
public:
	UnionFindSet(size_t n)
	{
		_ufs.resize(n, -1);
	}
	int FindRoot(int x)
	{
		int root=x ;
		while(_ufs[root] >= 0)
		{
			root = _ufs[root];
			
		}
		return root;
	}
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 != root2)
		{
			_ufs[root1] += _ufs[root2];
			_ufs[root2] = root1;
		}
	}
	bool IsInOneSet(int x1,int x2)
	{
		return  FindRoot(x1)== FindRoot(x2);
	}
	size_t GetSetSize()
	{
		size_t count = 0;
		for (size_t i = 0; i < _ufs.size(); ++i)
		{
			if (_ufs[i] < 0)
			{
				++count;
			}
		}
		return count;
	}
protected:
	vector<int>  _ufs;
};

//int friends(int n, int m, int r[][2])
//{
//	UnionFindSet ufs(n + 1);
//	for (size_t i = 0; i < m; ++i)
//	{
//		ufs.Union(r[i][0], r[i][1]);
//	}
//	return ufs.GetSetSize()-1;
//}
//
//void test()
//{
//	int n = 5;
//	const int m = 3;
//	int r[m][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };
//	cout << friends(n, m, r) << endl;
//}
