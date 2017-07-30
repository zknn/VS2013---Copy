#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>
void InsertSort(int* a, int size)
{
	assert(a);
	for (int i=0; i < size-1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
			for (; end >= 0; end--)
			{
				if (a[end]>tmp)
					a[end + 1] = a[end];
				else
					break;
			}
			a[end + 1] = tmp;
	}
}

void ShellSort(int* a, int size)
{
	assert(a);
	int grp = size;
	while (grp > 1)
	{
		grp = grp / 3 + 1;
		for (int i = 0; i < size - grp; i++)
		{
			int end = i;
			int tmp = a[end + grp];
			for (; end >= 0; end-=grp)
			{
				if (a[end]>tmp)
					a[end + grp] = a[end];
				else
					break;
			}
			a[end + grp] = tmp;
		}
	}
}
void Print(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
int main()
{
	int arr[] = { 2, 8, 1, 6, 3, 0, 9 };
	int size = sizeof(arr) / sizeof(arr[0]);
	/*InsertSort(arr, size);
	cout << "InsertSort()" << endl;*/
	ShellSort(arr, size);
	cout << "ShellSort()";
	Print(arr, size);
}