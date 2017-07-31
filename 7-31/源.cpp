#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>
#include <map>
#include <string>
#include <set>

void Print(const int* a, const int size)
{
	assert(a);
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void AdjustDown(int* a, const int size, int i)
{
	int parent = i;
	int child = 2*parent + 1;
	while(child < size)
	{
		if (child + 1 < size&&a[child + 1] > a[child])
			++child;
		if (a[child]>a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
void HeapSort(int* a,const int size)   //堆排序
{
	assert(a);
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, size, i);
	}
	int end = size - 1;
	while (end > 0)
	{
		swap(a[0], a[end]);
		AdjustDown(a, end, 0);
		--end;
	}
}

void testHeapSort()
{
	int arr[] = { 2, 1, 9, 0, 4, 7, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	cout << "堆排序前： ";
	Print(arr, size);
	HeapSort(arr, size);
	cout << "堆排序后： ";
	Print(arr, size);
}

void SelectSort(int* a, const int size)   //选择排序
{
	assert(a);
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		int min = left;
		int max = left;
		for (int i = left; i <= right; i ++)
		{
			if (a[min]>a[i])
				min = i;
			if (a[max] < a[i])
				max = i;
		}
		swap(a[min], a[left]);
		if (max == left)
			max = min;
		swap(a[max], a[right]);
		++left;
		--right;
	}
}

void testSelectSort()
{
	int arr[] = { 2, 1, 9, 0, 4, 7, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	cout << "选择排序前： ";
	Print(arr, size);
	SelectSort(arr, size);
	cout << "选择排序后： ";
	Print(arr, size);
}

//TopK问题

void CalculateCount(map<string, int>& m, string s[], int size)
{
	for (int i = 0; i < size; i++)
	{
		pair<map<string, int>::iterator, bool> ret;
		ret = m.insert(make_pair(s[i], 1));
		if (ret.second == false)   //考虑map的特性，当数据存在时，不再插入
			ret.first->second++;
	}
}
#include <vector>
#include <algorithm>
#include <queue>
void TopK(map<string, int>& m,int K)  //优先级队列
{
	struct Compare
	{
		bool operator()(map<string, int>::iterator l, map<string, int>::iterator r)
		{
			return l->second<r->second;   
		}
	};
	priority_queue<map<string, int>::iterator, vector<map<string, int>::iterator>, Compare> q;
	map<string, int>::iterator it = m.begin();
	while (it != m.end())
	{
		q.push(it);
		++it;
	}
	for (int i = 0; i < K;i++)
	{
		cout << q.top()->first << " ";
		q.pop();
	}
	cout << endl;

}
void TopK(map<string, int>& m,int size, vector<map<string, int>::iterator>& v)  
{
	map<string, int>::iterator it = m.begin();
	while(it!= m.end())
	{
		v.push_back(it);
		it++;
	}

	struct Compare
	{
		bool operator()(map<string, int>::iterator l, map<string, int>::iterator r)
		{
			return l->second>r->second;   //小堆
		}
	};
	make_heap(v.begin(), v.end(), Compare());  //堆排
	while (it != m.end())
	{
		if (it->second >v.front()->second)
		{
			pop_heap(v.begin(), v.end(), Compare());
			v.pop_back();
			v.push_back(it);
			push_heap(v.begin(), v.end(), Compare());
		}
		it++;
	}
	//sort(v.begin(), v.end(), Compare());  //直接在vector排序
}

struct Compare  //用set (有bug，当存在数据相等时会出现bug）
{
	bool operator()(map<string, int>::iterator l, map<string, int>::iterator r)
	{
		return l->second>r->second;
	}
};
void TopK(map<string, int>& m,  set<map<string, int>::iterator,Compare>& v)
{
	map<string, int>::iterator it = m.begin();
	while (it != m.end())
	{
		v.insert(it);
		it++;
	}
}
void testTopK()
{
	string s[] = { "苹果", "香蕉", "梨", "苹果", "葡萄", "葡萄", "梨", "苹果","苹果","葡萄","香蕉"};  //苹果、葡萄、梨、香蕉
	int size = sizeof(s) / sizeof(s[0]);
	map<string, int> m;
	CalculateCount(m, s, size);
	vector<map<string, int>::iterator> v;
	set<map<string, int>::iterator,Compare> it;
	TopK(m, it);  //用set的测试
	set<map<string, int>::iterator, Compare>::iterator its = it.begin();
	while (its != it.end())
	{
		cout << (*its)->first << " ";
		++its;
	}
	cout << endl;
	//TopK(m, size, v);  //用堆排和用vector直接排序的测试用例,堆排时使用逆序的迭代器打印比较方便
	//vector<map<string, int>::iterator>::reverse_iterator itv = v.rbegin();
	//while (itv != v.rend())
	//{
	//	cout << (*itv)->first << " ";
	//	itv++;
	//}
	//cout << endl;
	//int k;
	//cout << "请输入K值";
	//cin >> k;
	//TopK(m, k);
}
int main()
{
	//testHeapSort();
	//testSelectSort();
	testTopK();
	return 0;
}