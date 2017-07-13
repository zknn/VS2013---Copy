#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include "TypeTraits.h"
using namespace std;



int main()
{
	string s1[10] = { "1", "2", "3", "444444444444444444444444444444444444444444444" };
	string s2[10] = { "11", "22", "33" };
	Copy(s1, s2, 10);
	Copy(s1, s2, 10);

	int a1[10] = { 1, 2, 3 };
	int a2[10] = { 0 };
	Copy(a1, a2, 10, TypeTraits<int>::__IsPODType());
	Copy(a1, a2, 10);
	return 0;
}