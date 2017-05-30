  template<class K>
  struct SearchBinaryTreeNode
  {
	  SearchBinaryTreeNode<K> *_left;
	  SearchBinaryTreeNode<K> *_right;
	  K _key;
	  SearchBinaryTreeNode(const K& key)
		  :_key(key)
		  , _left(NULL)
		  , _right(NULL)
	  {}

  };

  template <class K>
  class SearchBinaryTree
  {
	  typedef SearchBinaryTreeNode<K>  Node;
  public:

   SearchBinaryTree()
	  :_root(NULL)
  {}
  bool Inserch(const K& key)
  {
	  if (_root == NULL)
	  {
		  _root = new Node(key);
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
		  parent->_right = new Node(key);
	  }
	  else
	  {
		  parent->_left = new Node(key);
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
  //递归实现
  bool InsertR(const K& key)
  {
	  return _InsertR(_root, key);
  }
  bool _InsertR(Node* root, const K& key)
  {
	  if (root == NULL)
	  {
		  root = new Node(key);
		  return true;
	  }
	  if (root->_key < key)
	  {
		  return _Insert(root->_right, key);
	  }
	  else if (root->_key>key)
	  {
		  return _Insert(root->_left, key);
	  }
	  else
	  {
		  return false;
	  }
  }
  Node* FindR(const K& key)
  {
	  if (root == NULL)
		  return NULL;
	  if (root->_key > key)
	  {
		  return _FindR(root->_left);
	  }
	  else if (root->_key < key)
	  {
		  return _FindR(root->_right);
	  }
	  else
	  {
		  return root;
	  }
  }
  bool RemoveR(const K& key)
  {
	  return _RemoveR(_root, key);
  }
  bool _Remove(Node* root, const K& key)
  {
	  if (root == NULL)
		  return false;
	  if (root->_key > key)
	  {
		  return _Remove(root->_left, key);
	  }
	  else if (root->_key < key)
	  {
		  return _Remove(root->_right, key);
	  }
	  else
	  {
		  Node* del = root;
		  if (root->_left == NULL)
		  {
			  root = root->_right;
		  }
		  else if (root->_right == NULL)
		  {
			  root = root->_left;
		  }
		  else
		  {
			  //法一
			  /*  Node* parent = NULL;
				Node* left = root->_right;
				while (left->_left)
				{
				parent = left;
				left = left->_left;
				}
				root->_key = left->_key;
				del = left;
				if (parent->_left == left)
				{
				parent->_left = left->_right;
				}
				else
				{
				parent->_right = left->_right;
				}
				}
				delete del;*/
			  //方法二
			  Node* left = left->_right;
			  while (left->_left)
			  {
				  left = left->_left;
			  }
			  root->_key = left->_key;
			  _Remove(root->_right, left->_key);
		  }
		  if (root->_left == NULL)
		  {
			  delete del;
			  return true;
		  }
	  }
  }
	protected:
		Node* _root;
 };

 void test()
 {
	 SearchBinaryTree<int> t;
	 int a[] = { 5, 3, 4, 1, 7, 8, 2, 0, 6, 9 };
	 for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	 {
		 t.Inserch(a[i]);
	 }
	 t.InOrder();
	 t.Remove(0);
	 t.Remove(1);
	 t.InOrder();
	 t.Remove(2);
	 t.Remove(3);
	 t.Remove(4);
	 t.InOrder();
	 t.Remove(5);
	 t.Remove(6);
	 t.Remove(7);
	 t.Remove(8);
	 t.Remove(9);
	 t.Remove(4);

	 
 }
 void testR()
 {
	 SearchBinaryTree<int> t;
	 int a[] = { 5, 3, 4, 1, 7, 8, 2, 0, 6, 9 };
	 for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	 {
		 t.Inserch(a[i]);
	 }
	 t.InOrder();
	 t.Remove(0);
	 t.Remove(1);
	 t.InOrder();
	 t.Remove(2);
	 t.Remove(3);
	 t.Remove(4);
	 t.InOrder();
	 t.Remove(5);
	 t.Remove(6);
	 t.Remove(7);
	 t.Remove(8);
	 t.Remove(9);
	 t.Remove(4);
 }