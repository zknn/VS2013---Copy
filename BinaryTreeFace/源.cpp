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
	//���ٶ�����
	void destory(Node* root)
	{
		if (root != NULL)
		{
			destory(root->_left);
			destory(root->_right);
			delete root;
		}
	}
	//1.��Ҷ�ӽڵ�ĸ���
	void leafCount()
	{
		int count = 0;
		_leafCount(_root, count);
		cout << "������Ҷ�ӽڵ�ĸ���:" << count << endl;
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

	//2.���K��Ľڵ����
	void KCount(int k)
	{
		int count=_KCount(_root,k);
		cout << "��" << k << "��Ľڵ�����ǣ�" << count << endl;
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
	//3.��������ĸ߶�
	void height()
	{

		int count=_height(_root);
		cout << "�ö������ĸ߶�Ϊ��" << count << endl;
	}
	int _height(Node* root)
	{
		if (root == NULL)
			return 0;
		int leftcount= _height(root->_left);
		int  rightcount = _height(root->_right);
		return leftcount >= rightcount ? leftcount + 1 : rightcount + 1;
	
	}
	//���Һ���
	void Find(int data)
	{
		if (_Find(_root, data) == NULL)
		{
			cout << "����û������ڵ�" << endl;
			return;
		}
		cout << "�ҵ��˸ýڵ�,������Ϊ��" << _Find(_root,data)->_data << endl;
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
	//�������������
	void BFS()  //��������
	{
		if (_root == NULL)
		{
			cout << "����Ϊ����" << endl;
			return;
		}
		cout << "���������";
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
	//�ж�һ�����Ƿ���ƽ����
	void IsBalanceN()  //ʱ�临�Ӷ�ΪO��n*n)
	{
		if (_root == NULL)
		{
			cout << "������һ�ÿ���" << endl;
			return;
		}
		if (_root->_left == NULL&&_root->_right == NULL)    //ֻ��һ���ڵ�ʱ����Ϊ��ƽ����
		{
			cout << "����ֻ��һ���ڵ㣬��ƽ����" << endl;
		}
		int leftheight = _height(_root->_left);
		int rightheight = _height(_root->_right);
		if (abs(leftheight - rightheight) < 2)
			cout << "������ƽ����" << endl;
		else
			cout << "��������ƽ����" << endl;
	}
	void IsBalance()   //ʱ�临�Ӷ�ΪO(n)
	{
		int depth = 0;
		if (_IsBalance(_root, depth) == true)
			cout << "����Ϊƽ����" << endl;
		else
			cout << "��������ƽ����" << endl;
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
	void PrevOrder()  //ǰ����� ���ݹ飩
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
	void InOrder()  //����������ݹ飩
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
	void  PostOrder() //�������  ���ݹ飩
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
	void PrevOrderNR()  //�ǵݹ�ʵ��ǰ�����
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
	void InOrderNR()  //�ǵݹ�ʵ���������
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
	void Mirror() //�������ľ���
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

void testleafCount()  //����Ҷ�ӽڵ����
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BinaryTree tree(arr, size, '#');
	tree.leafCount();
}
void testKCount()   //���Ե�K��Ľڵ����
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
void testheight()  //������߶ȵĺ���
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
void testFind()  //���Բ��Һ���
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
void testBFS()  //���Բ������
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
void testIsBalance()  //�����Ƿ�Ϊƽ�����ĺ���
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
void testPrevOrder()  //����ǰ�����
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
void testInOrder()   //�����������
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
void testPostOrder()  //���Ժ������
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
void testPrevOrderNR()  //����ǰ������ǵݹ�
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
void testInOrderNR()  //������������ǵݹ�
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
void testPostOrderNR()  //���Ժ�������ǵݹ�
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
void testMirror()   //���Զ������ľ���
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