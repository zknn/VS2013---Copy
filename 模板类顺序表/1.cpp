#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
int sum=0;
int i=0;
class num
{
public:
	num()
		
	{
		sum += ++i;
	}

};
//int main()
//{
//	num* a=new num[100];
//	cout << sum << endl;
//	return 0;
//}