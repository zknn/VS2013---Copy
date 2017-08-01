




void Print(int* arr, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void InsertSort(int* a, size_t n)    //直接插入排序
{
	for (size_t i = 0; i < n - 1; i++)
	{
		int tail = i;
		int next = a[tail + 1];
		while (tail >= 0)
		{
			if (a[tail]>next)
			{
				swap(a[tail + 1], a[tail]);
				--tail;
			}
			else
			{
				break;
			}
		}
	}
}

void testInsertSort()
{
	int arr[] = { 11, 2, 5, 7, 1, 9, 0 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	InsertSort(arr, sz);
	cout << "InsertSort()" << endl;
	Print(arr, sz);

}
void ShellSort(int* a, size_t n)  //按升序排列     希尔排序
{
	assert(a);
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (size_t i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end]>tmp)
				{
					swap(a[end + gap], a[end]);//交换
					end -= gap;
				}
				else
				{
					break;
				}
			}
		}
	}
}
void testShellSort()
{
	int arr[] = { 11, 2, 5, 7, 1, 9, 0 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	cout << "ShellSort" << endl;
	ShellSort(arr, sz);
	Print(arr, sz);
}

void SelectSort(int* a, int n)      //选择排序
{
	int left = 0;
	int right = n - 1;
	while (left <= right)
	{
		int min = left;
		int max = left;
		for (int i = left; i <= right; ++i)
		{
			if (a[i] > a[max])
			{
				max = i;
			}
			if (a[i] < a[min])
			{
				min = i;
			}
		}
		swap(a[min], a[left]);
		if (max == left)   //避免将已经排好的两数再次交换（处理当最大数在最小位置最小数在最大位置时出现的bug）
			max = min;
		swap(a[max], a[right]);
		left++;
		right--;
	}
}
void  testSelectSort()
{
	int arr[] = { 11, 2, 5, 7, 1, 9, 0 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	cout << "SelecSort" << endl;
	SelectSort(arr, sz);
	Print(arr, sz);
}


void AdjustDown(int* a, size_t n, size_t root)   //n=7
{
	size_t parent = root;
	size_t child = (parent * 2) + 1;
	while (child < n)
	{
		//选出大孩子
		if ((child + 1<n) && (a[child + 1]>a[child]))  //右孩子大于左孩子
		{
			++child;//变为右孩子
		}
		if (a[child]>a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;  //向下调整     
			child = (parent * 2) + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int *a, size_t n)   //堆排序
{
	assert(a);
	for (int i = (n - 2) / 2; i >= 0; --i)    //从根节点开始调整
	{
		AdjustDown(a, n, i);   //调整
	}
	size_t end = n - 1;
	while (end>0)
	{
		swap(a[0], a[end]);
		AdjustDown(a, end, 0);
		--end;
	}

}

void testHeapSort()
{
	int arr[] = { 11, 2, 5, 7, 1, 9, 0 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	cout << "HeapSort" << endl;
	HeapSort(arr, sz);
	Print(arr, sz);
}

void BubbleSort(int* a, size_t n)   //冒泡排序
{
	assert(a);
	size_t end = n - 1;
	while (end > 0)
	{
		for (size_t i = 0; i < end; ++i)
		{
			if (a[i + 1] < a[i])
			{
				swap(a[i + 1], a[i]);
			}
		}
		--end;
	}
}
void testBubbleSort()
{
	int arr[] = { 11, 2, 5, 7, 1, 9, 0 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	cout << "BubbleSort" << endl;
	BubbleSort(arr, sz);
	Print(arr, sz);
}


int PartSort1(int* a, int left, int right)  //左右指针法
{
	int key = right;
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while ((a[begin] <= a[key]) && (begin < end))
		{
			++begin;
		}
		while ((a[end] >= a[key]) && (begin < end))
		{
			--end;
		}
		if (begin<end)
		{
			swap(a[begin], a[end]);
		}
	}
	swap(a[begin], a[key]);
	return begin;
}
int PartSort2(int* a, int left, int right)   //挖坑法
{
	assert(a);
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
int PartSort3(int* a, int left, int right)   //前后指针法
{
	int key = a[right];
	int prev = left - 1;
	int cur = left;
	while (cur < right)
	{
		if (a[cur] < key &&++prev != cur)
		{
			swap(a[prev], a[cur]);
		}
		++cur;
	}
	swap(a[++prev], a[right]);
	return prev;
}
int GetMidIndex(int* a, int left, int right)
{
	int mid = left + (right - left) / 2;
	// left mid right
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
			return mid;
		else if (a[left] > a[right])
			return left;
		else
			return right;
	}
	else // left > mid  right
	{
		if (a[mid] > a[right])
			return mid;
		else if (a[left] < a[right]) // right > mid
			return left;
		else
			return right;
	}
}
void FastSort(int *a, int left, int right)   //快速排序
{
	assert(a);
	if (left >= right)
		return;
	if (left < right)
	{
		int div = PartSort3(a, left, right);
		FastSort(a, left, div - 1);
		FastSort(a, div + 1, right);
	}
}

void testFastSort()
{
	int arr[] = { 11, 2, 5, 7, 1, 0, 9 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	cout << "FastSort" << endl;
	FastSort(arr, 0, sz - 1);
	Print(arr, sz);
}

#include <stack>
void FastSortN(int* a, int left, int right)  //快速排序的非递归实现
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
		int begin = s.top();
		s.pop();
		int end = s.top();
		s.pop();
		int div = PartSort1(a, begin, end);
		if (begin < div - 1)
		{
			s.push(div - 1);
			s.push(begin);
		}
		if (div + 1 < end)
		{
			s.push(end);
			s.push(div + 1);
		}
	}
}

void testFastSortN()
{
	int arr[] = { 11, 2, 5, 7, 1, 0, 9 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	cout << "FastSortN" << endl;
	FastSortN(arr, 0, sz - 1);
	Print(arr, sz);
}

void _Merge(int* a, int* tmp, int begin1, int end1, int begin2, int end2)
{
	int pos = begin1;
	int index = begin1;
	while (begin1 <= end1&&begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
			tmp[index++] = a[begin2++];
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	memcpy(a + pos, tmp + pos, sizeof(int)*(end2 - pos + 1));
}

void _MergeSort(int* a, int *tmp, int left, int right)
{
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;
	_MergeSort(a, tmp, left, mid);
	_MergeSort(a, tmp, mid + 1, right);
	_Merge(a, tmp, left, mid, mid + 1, right);
}
void MergeSort(int* a, int size)
{
	assert(a);
	int *tmp = new int[size];
	_MergeSort(a, tmp, 0, size - 1);
	delete[] tmp;
}

void testMergeSort()
{
	int arr[] = { 11, 2, 5, 7, 1, 0, 9 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	cout << "MergeSort" << endl;
	MergeSort(arr, sz);
	Print(arr, sz);
}