enum Color
{
	RED,
	BLACK,
};

template <class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Color _col;
	RBTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _col(RED)
	{}
};

template <class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		//插入节点
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		//调节
		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)       //父节点是左孩子
			{
				Node* uncle = grandfather->_right;
				if (uncle&&uncle->_col == RED)//uncle存在且为红色
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else    //uncle不存在或为黑色
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					RotateR(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
			else  //父节点是右孩子
			{
				Node* uncle = grandfather->_left;
				if (uncle&&uncle->_col == RED)
				{
					uncle->_col = BLACK;
					parent->_col = BLACK;
					grandfather->_col = RED;
				}
				else  //uncle不存在或为黑色
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}

			subL->_parent = ppNode;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
		}
		else
		{
			if (parent == ppNode->_left)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
		}

		subR->_parent = ppNode;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool IsBalance()
	{
		if (_root == NULL)
			return true;
		if (_root&&_root->_col == RED)
			return false;
		int blacknum = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_col == BLACK)
			{
				++blacknum;
			}
			left = left->_left;
		}
		int num = 0;
		return _IsBalance(_root, num, blacknum);
	}
	bool _IsBalance(Node* root, int num, const int blacknum)
	{
		if (root == NULL)
			return true;
		if (root->_col == RED&&root->_parent->_col == RED)
			return false;
		//计算黑色节点的个数
		if (root->_col == BLACK)
			++num;
		if (root->_left == NULL&&root->_right == NULL)
		{
			if (num != blacknum)
			{
				cout << "黑色节点个数不相等" <<root->_key << endl;
				return false;
			}
			else
				return true;
		}
		return  _IsBalance(root->_left, num, blacknum) && _IsBalance(root->_right, num, blacknum);
	}
protected:
	Node* _root;
};


void test()
{
	RBTree<int, int> t;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t.Insert(a[i], i);
	
	}
	t.InOrder();
	if (t.IsBalance() == true)
	{
		cout << "该树是红黑树" << endl;
	}
}