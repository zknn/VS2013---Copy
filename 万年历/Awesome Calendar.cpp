#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"

//构造函数
rebook::rebook()
{
	_where = "xxx";  //地点
	_things = "xxx"; //事件
	_what = "xxx"; //事件描述
	_signs = "xxx"; //标题
	_date = "xxx"; //日期
}

//新建备忘录
void rebook::new_book()
{
	system("cls");
	cout << endl << "记事（以‘#’表示结束）" << endl;
	time_t timer;
	time(&timer);
	cout << endl << "时间： " << asctime(localtime(&timer)) << endl;
	cout << "标题：";
	cin >> _signs;
	ofstream tempFile("record\\temp.txt");
	time(&timer);
	tempFile << "时间： " << asctime(localtime(&timer)) << endl << "标题： " << _signs << endl << endl << "内容： ";
	cout << endl << "内容： " << endl;
	tempFile << endl << endl;
	string str;
	while (1)
	{
		cin >> str;
		if (str[str.length() - 1] == '#')
		{
			str[str.length() - 1] == ' ';
			tempFile << str << endl << endl;
			break;
		}
		tempFile << str << endl << endl;
	}
	tempFile.close();
	ofstream reFile1("record\\title.txt", ios::app);
	reFile1 << _signs << endl << asctime(localtime(&timer)) << endl;
	reFile1.close();
	string fname = "record\\" + _signs + ".txt";
	ofstream reFile(fname.c_str());
	ifstream tempFile1("record\\temp.txt");
	assert(tempFile1);
	reFile << tempFile.rdbuf();
	tempFile1.close();
	reFile.close();
	cout << endl << endl << "记录已经保存！！！" << endl << endl;
	system("pause");
}