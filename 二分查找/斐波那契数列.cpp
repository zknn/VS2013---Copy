#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
int i = 0;
int ret = 0;
int FIB(int N)
{
	return	N > 1 ? FIB(N - 1) + FIB(N - 2) : N;
}
int Fib(int N,int* a)
{
	if (N == 0)
	{
		return 0;
	}
	if (N < 2)
	{
		return 1;
	}
	int first = 0;
	int second = 1;
	for (int j = 2; j <= N; j++)
	{
	    ret = first + second;
		first = second;
		second = ret;
	}
	return ret;
}
int main()
{
	int N;
	int arr[] = { 0 };
	int first = 1;
	int second = 2;
	cout << "请输入需要计算的数：";
	cin >> N;
	for (int j = 0; j <= N; j++)
	{
		int print=Fib(j, arr);
		cout << print << " ";

	}
	cout << endl;
	cout << FIB(N) << endl;
	return 0;
}