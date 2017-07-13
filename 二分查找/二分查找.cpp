#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
void  Seek(int a[], int left, int right, int find)      //�ǵݹ�ʵ��     ʱ�临�Ӷ�O��lgN)     �ռ临�Ӷ�O��1��
{
	 
	while (left <= right)
	{
		int mid = left + (right - left) / 2; //mid=left+(right-left)>>1           ��λ����ȳ�2Ч�ʸ�
		if (find == a[mid])
		{
			cout << "�ҵ��˸������������е��±��ǣ�" << mid<<endl;
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
	cout << "�������в����ڸ���" << endl;
}
int  Seek_Recursion(int *a,int find,int left,int right)      //ʱ�临�Ӷ�O��lgN)    �ռ临�Ӷ� O��lgN)
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
	cout << "��������Ҫ���ҵ�����";
	cin >> find;
	int begin = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	int end = sz - 1;
	//Seek(arr, begin, end, find);
	int result = Seek_Recursion(arr,find, begin, end);
	if(result>=0)
	{
		cout << "�ҵ��������±�Ϊ��" << result << endl;
	}
	else
	{
		cout << "��������û�и���" << endl;
	}
	return 0;
}
