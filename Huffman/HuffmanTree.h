
template <class W>
struct HuffmanTreeNode
{
	W _w;
	HuffmanTreeNode<W> * _left;
	HuffmanTreeNode<W> * _right;
	HuffmanTreeNode<W> * _parent;
	HuffmanTreeNode(const W w)
		:_w(w)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};
template <class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
	struct NodeCompare
	{
		bool operator()(const  Node* left,const  Node* right)
		{
			return left->_w < right->_w;
		}
	};
	
public:
	HuffmanTree()
		:_root(NULL)
	{}
	HuffmanTree(W* a, size_t n, const W& invalid)
	{
		Heap<Node*, NodeCompare> minHeap;
		for (size_t i = 0; i < n; ++i)
		{
			if (a[i] != invalid)
			{
				minHeap.Push(new Node(a[i]));
			}
		}
		while (minHeap.size()>1)
		{
			Node*  left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();
			Node* parent = new Node(left->_w + right->_w);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;
			minHeap.Push(parent);
		}
		_root = minHeap.Top();
	}
	Node* GetRoot()
	{
		return _root;
	}
protected:
	Node* _root;
};
//
//void test()
//{
//	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	HuffmanTree<int> t(a, sizeof(a) / sizeof(a[0]),'#');
//
//}