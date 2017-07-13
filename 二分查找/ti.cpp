#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

class AA
{
public:
	 AA(int a,int b)
		:_aa(a)
	{
		cout << "AA()" << endl;
	}
	AA(const AA& a)
	{
		cout << "AA(const AA& a)" << endl;
	}
protected:
	int _aa;
	int _bb;
};
int main()
{
	AA a1(1);
	AA a2 = 1;
	AA a3 = a2;
	return 0;
}