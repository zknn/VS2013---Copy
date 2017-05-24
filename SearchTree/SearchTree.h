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
				  if (cur == parent->_left)
				  {

					  parent->_left = cur->_right;
				  }
				  else
				  {
					  parent->_right = cur->_right;

				  }
			  }
			  else if (cur->_right == NULL)
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
	 t.Remove(2);
	 t.InOrder();
	 t.Remove(4);
	 
 }