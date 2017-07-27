#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>
#include <queue>
#include <stack>
struct BinaryTreeNode
{
	int _data;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	BinaryTreeNode(int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(int *a, int& size,const int& invalid)
	{
		assert(a);
		int index = 0;
		_root = CreateNode(a, size, invalid, index);
	}
	Node* CreateNode(int* a, int& size, const int& invalid, int& index)
	{
		Node* cur = NULL;
		if (index < size &&a[index] != invalid)
		{
			cur = new Node(a[index]);
			cur->_left = CreateNode(a, size, invalid, ++index);
			cur->_right = CreateNode(a, size, invalid, ++index);
		}
		return cur;
	}
	~BinaryTree()
	{
		if (_root!=NULL)
		destory(_root);
	}
	//销毁二叉树
	void destory(Node* root)
	{
		if (root != NULL)
		{
			destory(root->_left);
			destory(root->_right);
			delete root;
		}
	}
	//1.求叶子节点的个数
	void leafCount()
	{
		int count = 0;
		_leafCount(_root, count);
		cout << "该树中叶子节点的个数:" << count << endl;
	}
	void _leafCount(Node* root, int& count)
	{
		if (root->_left == NULL&&root->_right == NULL)
		{
			count++;
			return;
		}
		_leafCount(root->_left,count);
		_leafCount(root->_right,count);
	}

	//2.求第K层的节点个数
	void KCount(int k)
	{
		int count=_KCount(_root,k);
		cout << "第" << k << "层的节点个数是：" << count << endl;
	}
	int _KCount(Node* root,int k)
	{
		if (root == NULL || k < 0)
			return 0;
		if (root != NULL&&k == 1)
			return 1;
		else
			return _KCount(root->_left, k - 1) + _KCount(root->_right, k - 1);
	}
	//3.求二叉树的高度
	void height()
	{

		int count=_height(_root);
		cout << "该二叉树的高度为：" << count << endl;
	}
	int _height(Node* root)
	{
		if (root == NULL)
			return 0;
		int leftcount= _height(root->_left);
		int  rightcount = _height(root->_right);
		return leftcount >= rightcount ? leftcount + 1 : rightcount + 1;
	
	}
	//查找函数
	void Find(int data)
	{
		if (_Find(_root, data) == NULL)
		{
			cout << "树中没有这个节点" << endl;
			return;
		}
		cout << "找到了该节点,其数据为：" << _Find(_root,data)->_data << endl;
	}
	Node* _Find(Node* root,int data)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == data)
			return root;
		Node* ret=_Find(root->_left, data);
		if (ret)
			return ret;
		return _Find(root->_right, data);
	
	}
	//层序遍历二叉树
	void BFS()  //借助队列
	{
		if (_root == NULL)
		{
			cout << "该树为空树" << endl;
			return;
		}
		cout << "层序遍历：";
		queue<Node*> q;
		q.push(_root);
		while (q.empty() == false)
		{
			cout << q.front()->_data << " ";
			if (q.front()->_left != NULL)
				q.push(q.front()->_left);
			if (q.front()->_right != NULL)
				q.push(q.front()->_right);
			q.pop();
		}
		cout << endl;
	}
	//判断一棵树是否是平衡树
	void IsBalanceN()  //时间复杂度为O（n*n)
	{
		if (_root == NULL)
		{
			cout << "该树是一棵空树" << endl;
			return;
		}
		if (_root->_left == NULL&&_root->_right == NULL)    //只有一个节点时，认为是平衡树
		{
			cout << "该树只有一个节点，是平衡树" << endl;
		}
		int leftheight = _height(_root->_left);
		int rightheight = _height(_root->_right);
		if (abs(leftheight - rightheight) < 2)
			cout << "该树是平衡树" << endl;
		else
			cout << "该树不是平衡树" << endl;
	}
	void IsBalance()   //时间复杂度为O(n)
	{
		int depth = 0;
		if (_IsBalance(_root, depth) == true)
			cout << "该树为平衡树" << endl;
		else
			cout << "该树不是平衡树" << endl;
	}
	bool _IsBalance(Node* root, int& depth)
	{
		if (root == NULL)
			return true;
		int leftheight;
		int rightheight ;
		if (_IsBalance(root->_left, leftheight) == false)
			return false;
		if (_IsBalance(root->_right, rightheight) == false)
			return false;
		depth = leftheight > rightheight ? leftheight + 1 : rightheight + 1;
		return abs(leftheight - rightheight) < 2;
	}
	void PrevOrder()  //前序遍历 （递归）
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
		
	}
	void InOrder()  //中序遍历（递归）
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
	void  PostOrder() //后序遍历  （递归）
	{
		_PostOrder(_root);
		cout << endl;
	}
	void _PostOrder(Node* root)
	{
		if (root == NULL)
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}
	void PrevOrderNR()  //非递归实现前序遍历
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void InOrderNR()  //非递归实现中序遍历
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cout << top->_data << " ";
			cur = top->_right;
		}
		cout << endl;
	}
	void PostOrderNR()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		Node* prev = NULL;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << " ";
				prev = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}
	void Mirror() //二叉树的镜像
	{
		if (_root == NULL)
			return;
		_Mirror(_root);
	}
	void _Mirror(Node* root)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
			return;
		Node* tmp = root->_left;
		root->_left = root->_right;
		root->_right = tmp;
		_Mirror(root->_left);
		_Mirror(root->_right);
	}
private:
	Node* _root;
};

void testleafCount()  //测试叶子节点个数
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.leafCount();
}
void testKCount()   //测试第K层的节点个数
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.KCount(0);
	tree.KCount(1);
	tree.KCount(2);
	tree.KCount(3);
	tree.KCount(-1);
	tree.KCount(6);
}
void testheight()  //测试求高度的函数
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	 int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	 int size1 = sizeof(arr1) / sizeof(arr1[0]);
    BinaryTree t(arr1, size1, '#');
	tree.height();
	t.height();
}
void testFind()  //测试查找函数
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.Find(1);
	tree.Find(2);
	tree.Find(3);
	tree.Find(4);
	tree.Find(5);
	tree.Find(6);
	tree.Find(7);


}
void testBFS()  //测试层序遍历
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.BFS();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.BFS();
}
void testIsBalance()  //测试是否为平衡树的函数
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.IsBalanceN();
	tree.IsBalance();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.IsBalanceN();
	t.IsBalance();
}
void testPrevOrder()  //测试前序遍历
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.PrevOrder();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.PrevOrder();
}
void testInOrder()   //测试中序遍历
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.InOrder();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.InOrder();
}
void testPostOrder()  //测试后序遍历
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.PostOrder();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.PostOrder();
}
void testPrevOrderNR()  //测试前序遍历非递归
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.PrevOrderNR();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.PrevOrderNR();
}
void testInOrderNR()  //测试中序遍历非递归
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.InOrderNR();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.InOrderNR();
}
void testPostOrderNR()  //测试后序遍历非递归
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.PostOrderNR();
	int arr1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	BinaryTree t(arr1, size1, '#');
	t.PostOrderNR();
}
void testMirror()   //测试二叉树的镜像
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.Mirror();
	tree.BFS();

}
int main()
{
	//testleafCount();
	//testKCount();
	//testheight();
	testFind();
	//testBFS();
	//testIsBalance();
	//testPrevOrder();
	//testInOrder();
	//testPostOrder();
	//testPrevOrderNR();
	//testInOrderNR();
	//testPostOrderNR();
	//testMirror();
	return 0;
}