#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
typedef void (*FUN)();  //º¯ÊýÖ¸Õë
 struct A
{
	FUN _fun;
	int _a;
};
struct B
{
	A _a;
	int b;
};

void A()
{
	printf("A£ºfun\n");
}
void B()
{
	printf("B:fun\n");
}

void testA()
{
	A a;
	B b;
	a.fun = A;
	b.fun = B;
	A* p1 = &a;
	p1->fun();
	p2 = (A*)&b;
	p2->fun();
}
int main()
{
	testA();
	return 0;
}

