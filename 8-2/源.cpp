#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>

void Print(int*a, int size)
{
	assert(a);
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void Merge(int* a, int* tmp, int begin1, int end1, int begin2, int end2)
{
	assert(a&&tmp);
	int pos=begin1;
	int i = begin1;
	while (begin1 <= end1&&begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[i++] = a[begin1++];
		else
			tmp[i++] = a[begin2++];
	}
	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}
	memcpy(a + pos, tmp + pos, sizeof(int)*(end2 - pos + 1));
}
void _MergeSort(int* a, int* tmp,int begin,int end)
{
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;
	_MergeSort(a, tmp, begin, mid);
	_MergeSort(a, tmp, mid + 1, end);

	Merge(a, tmp, begin, mid, mid + 1, end);
}
void MergeSort(int* a, int size)
{
	assert(a);
	int begin = 0;
	int end = size - 1;
	int* tmp = new int[size];
	_MergeSort(a, tmp,begin, end);
	delete[] tmp;
}

void testMerge()
{
	int arr[] = { 2, 4, 1, 7, 5, 0, 4, 3 };
	int size = sizeof(arr) / sizeof(arr[0]);
	cout << "ÅÅÐòÇ°£º ";
	Print(arr, size);
	MergeSort(arr, size);
	cout << "ÅÅÐòºó£º ";
	Print(arr, size);
}
int main()
{
	testMerge();
	return 0;
}