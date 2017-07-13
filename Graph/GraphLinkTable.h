template<class W>
struct GraphLinkTableEdge
{
	W _w;
	GraphLinkTableEdge<W>* _next;
	int _dst;
	int _src;
	GraphLinkTableEdge(const int src, const int dst, const W& w)
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
	void DFS()//�����������
	{
		vector<bool> visited;
		visited.resize(_vertex.size(), false);
		_DFS(0, visited);
		cout << "NULL" << endl;
	}
	void _DFS(int src,  vector<bool>& visited)   //���������������÷�ʽ����
	{
		cout << _vertex[src] << "[" << src << "]" <<"->";
		visited[src] = true;            //�����ʹ��Ľڵ�ķ��ʱ�־λ��Ϊtrue
		Edge* edge = _linktable[src];  //���ʵ�ǰ�ڵ���ڽӱ�
		while (edge)
		{
			if (visited[edge->_dst] == false)
			{
				_DFS(edge->_dst, visited);//�ݹ�������
			}
			edge = edge->_next;
		}
	}

	void BFS()//������ȱ���
	{
		queue<int>   q;  //��������
		vector<bool> visited;   //��־����
		visited.resize(_vertex.size(), false);
		q.push(0);
		while (!q.empty())
		{
			int front = q.front();
			q.pop();
			if (visited[front] == false)
			{
				cout << _vertex[front] << "[" << front << "]" << "->";
				visited[front] = true;
				Edge* edge = _linktable[front];  
				while (edge)
				{
					if (visited[edge->_dst] == false)     
					{
						q.push(edge->_dst);  //����־Ϊfalse�������
					}
					edge = edge->_next;
				}
			}
		}
		cout << "NULL" << endl;
	}
	//��С������
	//��³˹�����㷨

	bool Kruskal(GraphLinkTable<V, W> & minTree)
	{
		minTree._vertex = _vertex;
		minTree._linktable.resize(_vertex.size(), NULL);
		minTree._indexmap = _indexmap;
		struct EdgeCompare
		{
			bool operator()(const Edge* l, const Edge* r) const
			{
				return l->_w > r->_w;
			}
		};
		priority_queue<Edge*, vector<Edge*>, EdgeCompare>  q;
		for (size_t i = 0; i<_linktable.size();++i)
		{
			Edge* edge = _linktable[i];
			while (edge)
			{
				if (edge->_src>edge->_dst)
				{
					q.push(edge);
				}
				edge = edge->_next;
			}
		}
		//ѡ�߹�����С������
		UnionFindSet ufs(_vertex.size());//�������鼯
		size_t N = _vertex.size()-1;
		while (!q.empty())
		{
			Edge* min = q.top();
			//�ж�src��dst�Ƿ���ͬһ����
			if (ufs.IsInOneSet(min->_src, min->_dst) == false)
			{
				minTree._AddEdge(min->_src, min->_dst, min->_w);
				minTree._AddEdge(min->_dst, min->_src, min->_w);
				ufs.Union(min->_src, min->_dst);
				if (--N == 0)
				{
					return true;
				}
			}
			q.pop();
		}
		return false;
	}
protected:
	typedef  GraphLinkTableEdge<W> Edge;
	vector<V> _vertex;
	vector<Edge*> _linktable;
	map<string, size_t> _indexmap;
};

void testGraphLinkTable()
{
	string city[] = { "����", "�Ϻ�", "�ɶ�", "����","����","����" };
	int sz = sizeof(city) / sizeof(city[0]);
	GraphLinkTable<string, size_t, false> gm(city, sz);
	gm.AddEdge("����", "�ɶ�", 20);
	gm.AddEdge("�Ϻ�", "����", 30);
	gm.AddEdge("����", "�Ϻ�", 40);
	gm.AddEdge("�ɶ�", "����", 50);
	gm.AddEdge("����", "����", 100);
	gm.AddEdge("����", "����", 60);
	gm.AddEdge("����", "����",80);
	gm.AddEdge("�Ϻ�", "�ɶ�", 10);
	gm.AddEdge("����", "����", 110);

	gm.DFS();
	gm.BFS();
	GraphLinkTable<string, size_t, false> min;
	cout << gm.Kruskal(min) << endl;
}