using namespace std;
template<class T>
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
	ListNode(const T& data)
		:_data(data)
		, _prev(NULL)
		, _next(NULL)
	{}
};
template<class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;
	Node* _node;
	ListIterator(Node* node)
		:_node(node)
	{}
	Ref operator*()
	{
		return _node->_data;
	}
	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}
	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}
};
template<class T>  //带头结点的双向循环链表
class List
{
	typedef ListNode<T> Node;
public:
	typedef ListIterator<T, T&, T*>  Iterator;
	typedef ListIterator<T, const T&, const T*> ConstIterator;
	List()
	{
		_head = GetNode(T());
		_head->_next = _head;
		_head->_prev = _head;
	}
	Node* GetNode(const T& data)
	{
		Node* node;
		return node = new Node(data);
	}
	void PushBack(const T& data)
	{
		Node* tail = _head->_prev;
		Node* temp = GetNode(data);
		tail->_next = temp;
		temp->_prev = tail;
		_head->_prev = temp;
		temp->_next = _head;
	}
	Iterator Begin()
	{
		return Iterator(_head->_next);
	}
	Iterator End()
	{
		return Iterator(_head);
	}
	Iterator Begin() const
	{
		 return Iterator(_head->_next);
	}
	 Iterator End() const
	{
		 return Iterator(_head);
	}
protected:
	Node* _head;
};

void PrintList(const List<int>& l)
{
	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void Test()
{
	List<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	PrintList(l);
}