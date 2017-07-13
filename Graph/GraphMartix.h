template<class V,class W,bool IsDirected=false>   //给定默认模板参数表示图为无向图
class GraphMartix
{
public:
	GraphMartix()
	{}
	GraphMartix(V* vertex, size_t n)
	{
		_vertex.reserve(n);
		for (size_t i = 0; i < n; ++i)
		{
			_vertex.push_back(vertex[i]);
			_indexmap[vertex[i]] = i;
		}
		_martix.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			_martix[i].resize(n, W());
		}
	} 
	size_t GetVertexIndex(const V& v)
	{
		//for (size_t i = 0; i < _vertex.size(); ++i)
		//{
		//	if (_vertex[i] == v)
		//	{
		//		return i;
		//	}
		//}
		//assert(false);
		assert(_indexmap.count(v));
		return _indexmap[v];
	}
	void AddEdge(const V& src, const V& dst, const W& w)
	{
		int  srcIndex = GetVertexIndex(src);
		int dstIndex = GetVertexIndex(dst);
		_martix[srcIndex][dstIndex] = w;
		if (IsDirected == false)
		{
			_martix[dstIndex][srcIndex] = w;
		}
	}
		if (count == (_vertex.size() - 1))
		{
			return true;
		}
		return false;
	}
protected:
	vector<V> _vertex; //顶点集合
	vector<vector<W>> _martix;  //邻接矩阵  相当于一个二维数组
	map<string, size_t> _indexmap;
};


void testGrraphMartix()
{
	string city[] = { "西安", "上海", "成都", "拉萨", "杭州", "苏州" };
	int sz = sizeof(city) / sizeof(city[0]);
	GraphMartix<string, size_t, false> gm(city, sz);
	gm.AddEdge("西安", "成都", 20);
	gm.AddEdge("上海", "拉萨", 30);
	gm.AddEdge("西安", "上海", 40);
	gm.AddEdge("成都", "拉萨", 50);
	gm.AddEdge("西安", "杭州", 100);
	gm.AddEdge("杭州", "苏州", 60);
	gm.AddEdge("苏州", "拉萨", 80);
	gm.AddEdge("上海", "成都", 10);
	gm.AddEdge("杭州", "拉萨", 110);


}