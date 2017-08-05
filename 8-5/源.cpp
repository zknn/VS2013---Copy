#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
#include <vector>
using namespace std;

//Î»Í¼ÊµÏÖ
class BitMap
{
public:
	BitMap(size_t range)
	{
		_bitmap.resize(range / 8 + 1, 0);
	}
	void Set(int value)
	{
		size_t index = value >> 3;
		size_t pos = value % 8;
		_bitmap[index] |= (1 << pos);
	}
	void RetSet(size_t value)
	{
		size_t index = value >> 3;
		size_t pos = value % 8;
		_bitmap[index] &= (~(1 << pos));
	}
	bool test(size_t value)
	{
		size_t index = value >> 3;
		size_t pos = value % 8;
		return _bitmap[index] & (1 << pos);
	}
private:
	vector<char> _bitmap;
};

void test()
{
	BitMap bt(-1);
	bt.Set(1);
	bt.Set(155);
	bt.Set(99999);
	bt.Set(400);
	cout << bt.test(1) << endl;    //1
	cout << bt.test(2) << endl;   //0
	cout << bt.test(155) << endl;   //1
	cout << bt.test(99999)<< endl;  //1
	cout << bt.test(400) << endl;  //1
	cout << bt.test(0) << endl;   //0
	cout << bt.test(500) << endl;  //0
}
int main()
{
	test();
	return 0;
}