#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <stack>
#include <queue>

//����ջʵ��һ������
class Queue
{
public:
	void Push(int data)
	{
		s1.push(data);
	}
	void Pop()
	{
		if (!s2.empty())
		{
			s2.pop();
		}
		else
		{
			if (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
			else
			{
				return;
			}
		}
		s2.pop();
	}
protected:
	stack<int> s1;
	stack<int> s2;
};

void testQueue()
{
	Queue q;
	q.Push(0);
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
}

//��������ʵ��һ��ջ

class Stack
{
public:
	void Push(int data)
	{
		q1.push(data);
	}
	void Pop()   //��q2��Ϊ��ת,q1���в����ɾ��
	{
		int tmp;
		if (!q1.empty())
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			tmp = q1.front();
			q1.pop();
			while (!q2.empty())
			{
				q1.push(q2.front());
				q2.pop();
			}
		}
	}

protected:
	queue<int> q1;
	queue<int> q2;
};
void testStack()
{
	Stack s;
	s.Push(0);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();

}

//�滻�ַ����еĿո�Ϊ$$$
//1.ͨ�������µ��ַ���
void changeblack(char* s1, char* s2)
{
	while (*s1)
	{
		if (*s1 != ' ')
		{
			*s2 = *s1;
			s2++;
		}
		else
		{
			strcpy(s2, "$$$");
			s2 += 3;
		}
		s1++;
	}
	*s2 = '\0';
}

//��ԭ�����ַ����Ͻ����޸�
void change(char* s, int length)
{
	if (s == NULL || length <= 0)
	{
		return;
	}
	int Olength = 0;  //ԭ���ַ����ĳ���
	int numberblack = 0;    //��¼�ո���Ŀ
	int i = 0;
	while (s[i] != '\0')
	{
		++Olength;
		if (s[i] == ' ')
		{
			++numberblack;
		}
		++i;
	}
	int newlength = Olength + numberblack * 2;  //���ַ����е��ַ�����
	if (newlength >length)
		return;
	int Oindex = Olength;    //ԭ���ַ������±�
	int Nindex = newlength;  //���ַ������±�
	while ((Oindex >= 0) && (Nindex>Oindex))
	{
		if (s[Oindex] == ' ')
		{
			s[Nindex--] = '$';
			s[Nindex--] = '$';
			s[Nindex--] = '$';
		}
		else
		{
			s[Nindex--] = s[Oindex];
		}
		--Oindex;
	}
}

int main()
{
	const int length = 50;
	char arr[length] = "hello world ";
	char s[100];
	changeblack(arr, s);
	cout << s << endl;
	change(arr, length);
	cout << arr << endl;
	testQueue();
	testStack();
	return 0;
}