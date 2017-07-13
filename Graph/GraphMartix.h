template<class V,class W,bool IsDirected=false>   //����Ĭ��ģ�������ʾͼΪ����ͼ
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
	vector<V> _vertex; //���㼯��
	vector<vector<W>> _martix;  //�ڽӾ���  �൱��һ����ά����
	map<string, size_t> _indexmap;
};


void testGrraphMartix()
{
	string city[] = { "����", "�Ϻ�", "�ɶ�", "����", "����", "����" };
	int sz = sizeof(city) / sizeof(city[0]);
	GraphMartix<string, size_t, false> gm(city, sz);
	gm.AddEdge("����", "�ɶ�", 20);
	gm.AddEdge("�Ϻ�", "����", 30);
	gm.AddEdge("����", "�Ϻ�", 40);
	gm.AddEdge("�ɶ�", "����", 50);
	gm.AddEdge("����", "����", 100);
	gm.AddEdge("����", "����", 60);
	gm.AddEdge("����", "����", 80);
	gm.AddEdge("�Ϻ�", "�ɶ�", 10);
	gm.AddEdge("����", "����", 110);


}