template<class K,class V>
struct SearchBinaryTreeNode
{
	SearchBinaryTreeNode<K,V> *_left;
	SearchBinaryTreeNode<K,V> *_right;
	K _key;
	V _value;
	SearchBinaryTreeNode(const K& key,const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}

};

template <class K,class V>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K,V>  Node;
public:

	SearchBinaryTree()
		:_root(NULL)
	{}
	bool Inserch(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
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
		if (parent->_key < key)
		{
			parent->_right = new Node(key,value);
		}
		else
		{
			parent->_left = new Node(key,value);
		}
		return true;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}
	bool Remove(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
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
				//左为空或右为空
				Node* del = cur;
				if (cur->_left == NULL)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)
						{

							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;

						}
					}

				}
				else if (cur->_right == NULL)
				{
					if (parent == NULL)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
						{

							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;

						}
					}

				}
				else
				{
					//找右子树的最左节点
					Node* subright = cur->_right;
					Node* parent = cur;
					while (subright->_left)
					{
						parent = subright;
						subright = subright->_left;
					}
					swap(cur->_key, subright->_key);
					if (subright == parent->_left)
					{
						parent->_left = subright->_right;
					}
					else
					{
						parent->_right = subright->_right;
					}
				}
				delete del;
				return true;
			}
		}
		return false;
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
protected:
	Node* _root;
};

void TopK(vector<string> strs, size_t k)
{
	typedef SearchBinaryTreeNode<string, int> Node;
	SearchBinaryTree<string, int> t;
	for (size_t i=0; i < strs.size(); i++)
	{
		Node* ret = t.Find(strs[i]);
		if (ret)
		{
			ret->_value++;
		}
		else
		{
			t.Inserch(strs[i], 1);
		}
	}
	vector<Node*> v;

	struct NodeCompare
	{
		bool operator()(Node* l, Node *r)
		{
			return l->_value > r->_value;
		}
	};
	sort(v.begin(), v.end(), NodeCompare());
	//for (size_t i=0; i < v.size(); i++)
	//{
	//	cout << v[i]->_key << " ";
	//}
	//cout << endl;
}