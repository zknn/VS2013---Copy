#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>

void Print(int* a, int size)
{
	for (int i = 0; i < size;i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void BubbleSort(int* a, int size)  //冒泡排序
{
	assert(a);
	int end = size;
	while (end > 0)
	{
		bool exchange = false;
		for (int i = 0; i < end; i++)
		{
			if (a[i-1]>a[i])
			{
				swap(a[i - 1], a[i]);
				exchange = true;
			}
		}
		if (exchange == false)
		{
			break;
		}
		--end;
	}
}

void testBubbleSort()
{
	int arr[] = { 2, 7, 1, 5, 3, 9, 0, 4 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, size);
	cout << "冒泡排序";
	Print(arr, size);
}
int GetMidIndex(int *a, int left, int right)
{
	int mid = left + (right-left) / 2;
	if (a[left] < a[mid])
	{
		if (a[right]>a[mid])
			return mid;
		else if (a[left] > a[right])
			return left;
		else
			return right;
	}
	else
	{
		if (a[mid] > a[right])
			return mid;
		else if (a[left] < a[right])
			return left;
		else
			return right;
	}
}
int PartSort1(int* a, int left, int right)  //左右指针法
{
	int key = a[right];
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while (begin < end&&a[begin] <= key)
		{
			++begin;
		}
		while (begin<end&&a[end]>=key)
		{
			--end;
		}
		if (begin<end)
			swap(a[begin], a[end]);
	}
	swap(a[begin], a[right]);
	return begin;
}
int PartSort2(int* a, int left, int right)   //挖坑法（同时选取最大的和最小的）
{
	int key = a[right];
	while (left < right)
	{
		while (left<right&&a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];
		while (left < right&&a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

int PartSort3(int* a, int left, int right)  //前后指针法  
{
	int key = a[right];
	int Prev = left-1;
	int cur = left;
	while (cur< right)
	{
		if (a[cur] < key&&(++Prev)!=cur)
		{
			swap(a[Prev], a[cur]);
		}
		++cur;
	}
	swap(a[++Prev], a[right]);
	return Prev;
}
void FastSort(int* a,int left,int right)  //快速排序 当每次选取到的Key值都是最大或最小时，会使时间复杂度为最坏，所以应每次尽量选取到中位数
{
	assert(a);
	if (left>=right)
		return;
	int mid = GetMidIndex(a, left, right);
	swap(a[mid], a[right]);
	//int div = PartSort1(a, left, right);
	//int div = PartSort2(a, left, right);
	int div = PartSort1(a, left, right);
	FastSort(a, left, div-1);
	FastSort(a, div+1, right);
}
void testFastSort()
{
	int arr[] = { 6, 7, 1, 3, 0, 9, 2, 8 };
	int left = 0;
	int right = sizeof(arr) / sizeof(arr[0]) - 1;
	int size = right + 1;
	FastSort(arr, left, right);
	cout << "快速排序";
	Print(arr, size);
}
#include <stack>
void FastSortN(int* a, int left, int right)  //快速排序非递归
{
	assert(a);
	stack<int> s;
	if (left < right)
	{
		s.push(right);
		s.push(left);
	}
	while (!s.empty())
	{
		int left = s.top();
		s.pop();
		int right = s.top();
		s.pop();
		int div = PartSort1(a, left, right);
		//int div = PartSort2(a, left, right);
		//int div = PartSort3(a, left, right);
		if (left < div - 1)
		{
			s.push(div - 1);
			s.push(left);
		}
		if (div + 1 < right)
		{
			s.push(right);
			s.push(div + 1);
		}
	}
}
void testFastSortN()
{
	int arr[] = { 6, 7, 1, 3, 0, 9, 2, 8 };
	int left = 0;
	int right = sizeof(arr) / sizeof(arr[0]) - 1;
	int size = right + 1;
	FastSort(arr, left, right);
	cout << "快速排序(非递归实现）";
	Print(arr, size);
}
int main()
{
	//testBubbleSort();
	//testFastSort();
	testFastSortN();
	return 0;
}