#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>
#include "Sort.h"

int main()
{
	testInsertSort();
	testShellSort();
	testSelectSort();
	testHeapSort();
	testBubbleSort();
	testFastSort();
	testFastSortN();
	testMergeSort();
	return 0;
}