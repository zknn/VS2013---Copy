#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>
#define N 100
void Print(int* a, int size)
{
	assert(a);
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
void sort(int* a, const int size)
{
	if (a == NULL || size < 0)
		return;
	int b[N] = { 0 };
	for (int i = 0; i < size; ++i)
	{
		int key = a[i];
		++b[key];
	}
	int index = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < b[i]; ++j)
		{
			a[index] = i;
			++index;
		}
	}
}
struct compare
{
	bool operator()(int x, int y)
	{
		return x > y;   //x,小的优先级高
	}
};

#include <queue>
#include <vector>
void HeapSort(int* arr, int len)
{
	assert(arr);
	int newlen;
	if (len % 2 != 0)  //数组元素为奇数时
	{
		newlen = (len + 1) / 2;
	}   //用数组的一半多1长度建堆
	else  //数组元素为偶数时
		newlen = ((len + 1) / 2) + 1;
	priority_queue<int, vector<int>, compare> tty;    //建小堆  
	for (int i = 0; i < newlen; i++)
	{
		tty.push(arr[i]);
	}
	//此时数组中一半+1的元素已经建成小堆，需要比较数组后面元素
	for (int j = newlen; j < len; ++j)
	{
		//拿数组后半部分依次和堆顶比较，大于堆顶时入堆
		if (arr[j]>tty.top())
		{
			tty.pop();    //要保持堆内元素个数不变
			tty.push(arr[j]);
		}
	}
	if (len%2!=0&&!tty.empty())
	{
		cout << "中位数为： " << tty.top() << " ";
	}
	if (len % 2 == 0 && !tty.empty())
	{
		cout << "中位数为： " << tty.top() << " ";
		tty.pop();
		cout << tty.top();
	}
	cout << endl;
}

int main()
{
	int arr[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1 };
	int size = sizeof(arr) / sizeof(arr[0]);
	//sort(arr, size);
	Print(arr, size);
	int arr2[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	HeapSort(arr, size);
	Print(arr2, size2);
	HeapSort(arr2, size2);
}

void QuickSortThink(int *arr, int left, int right, int n)
{
	queue<pair<int, int>> q;
	q.push(make_pair(left, right));				  //插入0---9
	int objNumber = (n % 2 == 0) ? 2 : 1;  //余0返回2
	int count = 0;
	int temp[2] = { 0 };
	while (!q.empty())
	{
		int begin = q.front().first;
		int end = q.front().second;
		int key = begin;
		int mid = (end - begin) / 2 + begin;
		if (arr[begin] > arr[end])
		{
			if (arr[mid] > arr[begin])
				key = begin;
			else
			{
				if (arr[end] > arr[mid])
					key = end;
				else
					key = mid;
			}
		}
		else
		{
			if (arr[mid] > arr[end])
				key = end;
			else
			{
				if (arr[begin] > arr[mid])
					key = begin;
				else
					key = mid;
			}
		}
		swap(arr[key], arr[end]);
		key = end;
		//调优

		int slow = begin - 1;
		int fast = begin;
		while (fast < end)
		{
			while (fast < end&&arr[fast] > arr[end])
			{
				fast++;
			}
			slow++;
			if (fast != slow)
				swap(arr[slow], arr[fast]);
			fast++;
		}
		if (fast == end)
		{
			slow++;
			swap(arr[end], arr[slow]);
		}
		//根据slow的位置排除一部分
		if (objNumber == 1)
		{
			if (slow == n / 2)
			{
				cout << arr[slow] << endl;
				return;
			}
			else if (slow < n / 2)
			{
				q.push(make_pair(slow + 1, end));
			}
			else
			{
				q.push(make_pair(begin, slow - 1));
			}
		}
		else
		{
			if (slow == n / 2)
			{
				temp[1] = arr[slow];
				count++;
				if (count == objNumber)
					break;
				q.push(make_pair(begin, slow - 1));
			}
			else if (slow == n / 2 - 1)
			{
				temp[0] = arr[slow];
				count++;
				if (count == objNumber)
					break;
				q.push(make_pair(slow + 1, end));
			}
			else if (slow < n / 2 || slow < n / 2 - 1)
			{
				q.push(make_pair(slow + 1, end));
			}
			else
			{
				q.push(make_pair(begin, slow - 1));
			}
		}
		q.pop();
	}
	cout << temp[0] << " " << temp[1] << endl;
	return;
}


void FindMidNumber(int* arr, int n)
{
	if (arr == NULL)
		return;
	if (n <= 2)
	{
		for (int i = 0; i < n; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	QuickSortThink(arr, 0, n - 1, n);
}