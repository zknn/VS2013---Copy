#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//#include "SearchTree.h"
#include <algorithm>
#include <vector>
#include <string>
#include "Top.h"

int main()
{
	vector<string> strs = { "apple", "apple","apple","water" };
	TopK(strs,4);
	//testR();
	return 0;

}