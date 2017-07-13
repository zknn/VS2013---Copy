#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
void  Seek(int a[], int left, int right, int find)      //非递归实现     时间复杂度O（lgN)     空间复杂度O（1）
{
	 
	while (left <= right)
	{
		int mid = left + (right - left) / 2; //mid=left+(right-left)>>1           移位运算比除2效率高
		if (find == a[mid])
		{
			cout << "找到了该数，在数组中的下标是：" << mid<<endl;
			return;
		}
		else if (find < a[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	cout << "此数组中不存在该数" << endl;
}
int  Seek_Recursion(int *a,int find,int left,int right)      //时间复杂度O（lgN)    空间复杂度 O（lgN)
{
	 int mid = left + (right - left) / 2;
	 if (find == a[mid])
	 {
		 return mid;
	 }
	 else
	 {
		 return (find < a[mid]) ? Seek_Recursion(a, find, left, mid - 1) : Seek_Recursion(a, find, mid + 1, right);
	 }
}

int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9 };
	int find = 0;
	cout << "请输入需要查找的数：";
	cin >> find;
	int begin = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	int end = sz - 1;
	//Seek(arr, begin, end, find);
	int result = Seek_Recursion(arr,find, begin, end);
	if(result>=0)
	{
		cout << "找到该数，下标为：" << result << endl;
	}
	else
	{
		cout << "该数组中没有该数" << endl;
	}
	return 0;
}
