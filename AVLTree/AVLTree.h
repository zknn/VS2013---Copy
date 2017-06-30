template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;
	AVLTreeNode<K, V> *_right;
	AVLTreeNode<K, V> * _left;
	AVLTreeNode<K, V> *_parent;
	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root== NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node * cur = _root;
		Node * parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		 //平衡调节
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)  //当前平衡因子等于1或-1时，需要向上查看其父节点的平衡因子
			{
				cur = parent;
				parent = cur->_parent;
			}
			else//平衡因子等于2或者-2，此时需要进行调节
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else
					{
						RotateRL(parent);
					}
				}
				else
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else
					{
						RotateLR(parent);
					}
				}
				break;
			}
		}
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
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
			subL->_bf = parent->_bf = 0;
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		if (ppNode == NULL)
		{
			_root = subR;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
		parent->_bf = subR->_bf = 0;
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			subR->_bf = parent->_bf = 0;
		}
		subRL->_bf = 0;
	}
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else
		{
			subL->_bf = parent->_bf = 0;
			subLR->_bf = 0;
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool  IsBalance()  //判断平衡树   
	{
		//return   _IsBalance(_root);
		int depth = 0;
		return _IsBalance(_root, depth);

	}
	bool _IsBalance(Node* root) //时间复杂度为O（n^2)
	{
		if (root == NULL)
		{
			return true;
		}
		int left = Depth(root->_left);
		int right = Depth(root->_right);
		return abs(right - left) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}
	bool _IsBalance(Node* root, int& depth)  //时间复杂度为O(n)
	{
		if (root == NULL)
			return true;
		int leftdepth, rightdepth;
		if (_IsBalance(root->_left, leftdepth) == false)
			return false;
		if (_IsBalance(root->_right, rightdepth) == false)
			return false;
		if (rightdepth - leftdepth != root->_bf)
		{
			cout << "bf异常" << root->_key << endl;
			return false;
		}
		depth = rightdepth > leftdepth ? rightdepth + 1 : leftdepth + 1;
		return abs(rightdepth - leftdepth) < 2;
	}
	int Depth(Node* root)
	{
		if (root == NULL)
			return 0;
		int left = Depth(root->_left);
		int right = Depth(root->_right);
		return left>right ? left + 1 : right + 1;
	}
protected:
	Node* _root;
};

void test()
{
	AVLTree<int,int> tree;
	int a[] = { 8,1,4,9,2,6,3,0,5,7 };
	size_t size = sizeof(a) / sizeof(a[0]);
	for (size_t i = 0; i < size; i++)
	{
		tree.Insert(a[i],i);
	}
	tree.InOrder();
	if(tree.IsBalance())
	{
		cout << "是平衡树" << endl;
	}
	else
	{
		cout << "不是平衡树" << endl;
	}
	

}
	
