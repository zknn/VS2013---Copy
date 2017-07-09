template<class W>
struct GraphLinkTableEdge
{
	W _w;
	GraphLinkTableEdge<W>* _next;
	int _dst;
	int _src;
	GraphLinkTableEdge(const int dst, const int src, const W& w)
		:_next(NULL)
		, _w(w)
		, _dst(dst)
		, _src(src)
	{}
};

template<class V,class W,bool IsDirected=false>
class GraphLinkTable
{
public:
	GraphLinkTable()
	{}
	GraphLinkTable(V* vertex, size_t n)
	{
		_vertex.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			_vertex.push_back(vertex[i]);
			_indexmap[vertex[i]] = i;
		}
		_linktable.resize(n, NULL);
	}
	size_t GetIndex(const V& v)
	{
		assert(_indexmap.count(v));
		return _indexmap[v];
	}
	void _AddEdge(size_t srcindex, size_t dstindex, const W& w)
	{
		Edge* edge = new Edge(srcindex, dstindex, w);
		edge->_next = _linktable[srcindex];
		_linktable[srcindex] = edge;
	}
	void AddEdge(const V& src, const V& dst, const W& w)
	{
		size_t srcindex = GetIndex(src);
		size_t dstindex = GetIndex(dst);
		_AddEdge(srcindex, dstindex, w);
		if (IsDirected == false)
		{
			_AddEdge(dstindex, srcindex, w);
		}
	}
	void DFS()//深度优先搜索
	{

	}
protected:
	typedef  GraphLinkTableEdge<W> Edge;
	vector<V> _vertex;
	vector<Edge*> _linktable;
	map<string, size_t> _indexmap;
};

void testGraphLinkTable()
{
	string city[] = { "西安", "上海", "成都", "拉萨" };
	int sz = sizeof(city) / sizeof(city[0]);
	GraphLinkTable<string, int, true> gm(city, sz);
	gm.AddEdge("西安", "成都", 20);
	gm.AddEdge("上海", "拉萨", 30);
	gm.AddEdge("西安", "上海", 40);
	gm.AddEdge("成都", "拉萨", 50);

}