#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include <stack>

//1.Ԫ�س�ջ����ջ˳��ĺϷ���

bool IsPopOrder(const int* pushorder, const int* poporder, int length)
{
	if (pushorder != NULL&&poporder != NULL&&length > 0)
	{
		stack<int> data_stack;    
		const int* pushnext = pushorder;
		const int* popnext = poporder;
		while (popnext - poporder < length)
		{
			while (data_stack.empty() || data_stack.top() != *popnext)
			{
				if (pushnext-pushorder==length)
					break;
				data_stack.push(*pushnext);
				pushnext++;
			}
			if (data_stack.top() != *popnext)
				break;
			data_stack.pop();
			popnext++;
		}
		if (data_stack.empty() && popnext - poporder == length)
		{
			return true;
		}
	}
	return false;
}

void testIsPopOrder()
{
	int push[] = { 1, 2, 3, 4, 5 };
	int pop[] = { 4, 5, 3, 2, 1 };
	cout << IsPopOrder(push, pop, sizeof(push) / sizeof(push[0])) << endl;   //1 true
	int pop1[] = { 4, 3, 5, 1, 2 };
	cout << IsPopOrder(push, pop1, sizeof(push) / sizeof(push[0])) << endl;   //0 false
}

//2.����һ������������λ��1�ĸ�����Ҫ��Ч�ʾ����ܵĸߡ�������ȷ�������͸����Ķ�������1�ĸ���

int OneCount1(int data)   //���븺��ʱ��bug
{
	int count=0;
	while (data)
	{
		if (data & 1)
			count++;
		data = data >> 1;
	}
	return count;
}
int OneCount2(int data)  //Ч��̫�ͣ���Ҫ����32��
{
	int count=0;
	size_t flag = 1;
	while (flag)
	{
		if (data&flag)
			count++;
		flag = flag << 1;
	}
	return count;
}
int OneCount(int data)
{
	int count = 0;
	while (data)
	{
		count ++;
		data = (data - 1)&data;
	}
	return count;
}


int main()
{
	//testIsPopOrder();
	cout << OneCount1(3) << endl;   //2
	cout << OneCount1(0) << endl;    //0
	//cout << OneCount1(-4) << endl;   //30
	cout << OneCount2(3) << endl;   //2
	cout << OneCount2(0) << endl;    //0
	cout << OneCount2(-4) << endl;   //30
	cout << OneCount(3) << endl;   //2
	cout << OneCount(0) << endl;    //0
	cout << OneCount(-4) << endl;   //30

	return 0;
}