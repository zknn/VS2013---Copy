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
	ofstream tempFile("recordtemp.txt");
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
			str[str.length() - 1] = ' ';
			tempFile << str << endl << endl;
			break;
		}
		tempFile << str << endl << endl;
	}
	tempFile.close();
	ofstream reFile1("recordtitle.txt", ios::app);
	reFile1 << _signs << endl << asctime(localtime(&timer)) << endl;
	reFile1.close();
	string fname = "record" + _signs + ".txt";
	ofstream reFile(fname.c_str());
	ifstream tempFile1("recordtemp.txt");
	assert(tempFile1);
	reFile << tempFile.rdbuf();
	tempFile1.close();
	reFile.close();
	cout << endl << endl << "记录已经保存！！！" << endl << endl;
	system("pause");
}

//修改备忘录

void rebook::alter_book()
{
	while (1)
	{
		system("cls");
		cout << endl << "请选择你想修改的标题： " << endl << endl;
		int i = 1;
		ifstream reFile("recordtitle.txt");
		if (!reFile)
		{
			ofstream reFile1("recordtitle.txt");
			reFile1.close();
			ifstream reFile("recordtitle.txt");
		}
		while (reFile >> _signs)
		{
			reFile.get();
			getline(reFile, _date);
			cout << i << ".\t" << setiosflags(ios::left) << setw(30) << _signs << " "
				<< _date << endl << endl;
			i++;
		}
		reFile.close();
		cout << endl << i << ".\t返回" << endl << endl;
		cout << "选择： ";
		int select;
		cin >> select;
		if (select == i)
			return;
		ifstream reFile2("recordtitle.txt");
		assert(reFile2);
		i = 1;
		while (reFile2 >> _signs)
		{
			reFile2.get();
			getline(reFile2, _date);
			if (i == select)
			{
				string fname = "record" + _signs + ".txt";
				system("cls");
				ifstream reFile3(fname.c_str());
				assert(reFile3);
				cout << endl << "你想要修改的内容如下：" << endl << endl;
				cout << reFile3.rdbuf();
				reFile3.close();
				ofstream tempFile("recordtemp.txt");
				cout << endl << endl << "请在下面输入新的内容（以‘#’结束）:" << endl << endl;
				tempFile << "标题： " << _signs << endl << endl;
				tempFile << "内容： ";
				string str;
				while (1)
				{
					cin >> str;
					if (str[str.length() - 1] == '#')
					{
						str[str.length() - 1] == ' ';
						tempFile << str << endl;
						break;
					}
					tempFile << str << endl;
				}
				tempFile.close();
				ifstream tempFile1("recordtemp.txt");
				assert(tempFile1);
				ofstream reFile4(fname.c_str());
				reFile4 << tempFile1.rdbuf();
				tempFile1.close();
				reFile4.close();
				cout << endl << endl << "内容更新完成！！！" << endl << endl;
				system("pause");
				break;
			}
			i++;
		}
		reFile2.close();
	}
}

//删除备忘录
void rebook::delete_book()
{
	while (1)
	{
		system("cls");
		cout << endl << "请选择你想要删除的标题： " << endl << endl;
		ifstream reFile("recordtitle.txt");
		if (!reFile)
		{
			ofstream reFile1("recordtitle.txt");
			reFile1.close();
			ifstream reFile("recordtitle.txt");
		}
		int i = 1;
		while (reFile >> _signs)
		{
			reFile.get();
			getline(reFile, _date);
			cout << i << ".\t" << setiosflags(ios::left) << setw(30) << _signs << " "
				<< _date << endl << endl;
			i++;
		}
		reFile.close();
		cout << endl << i << ".\t返回" << endl << endl;
		int select;
		cout << "选择： ";
		cin >> select;
		if (select == i)
			return;
		ifstream reFile2("recordtitle.txt");
		assert(reFile2);
		ofstream tempFile("recordtemp.txt");
		i = 1;
		while (reFile2 >> _signs)
		{
			reFile2.get();
			getline(reFile2, _date);
			if (i != select)
				tempFile << _signs << endl << _date << endl << endl;
			else
			{
				system("cls");
				cout << endl << endl << "你想要删除的备忘录内容如下：" << endl << endl;
				string fname = "record" + _signs + ".txt";
				ifstream reFile3(fname.c_str());
				assert(reFile3);
				cout << reFile3.rdbuf();
				reFile3.close();
			}
			getline(reFile2, _date);
			i++;
		}
		reFile2.close();
		tempFile.close();
		ifstream tempFile1("recordtemp.txt");
		assert(tempFile1);
		ofstream reFile4("recordtitle.txt");
		reFile4 << tempFile1.rdbuf();
		tempFile1.close();
		reFile4.close();
		cout << endl << endl << "该备忘录已被删除！！！" << endl << endl;
		system("pause");
	}
}

//浏览记事本
void rebook::scanf_book()
{
	while (1)
	{
		system("cls");
		cout << endl << "记事本查询" << endl << endl;
		ifstream reFile("recordtitle.txt");
		if (!reFile)
		{
			ofstream reFile1("recordtitle.txt");
			reFile1.close();
			ifstream reFile("recordtitle.txt");
		}
		int i = 1;
		cout << "序号\t" << setiosflags(ios::left) << setw(30) << "标题" << "\t日期" << endl << endl;
		while (reFile >> _signs)
		{
			reFile.get();
			getline(reFile, _date);
			cout << i << ".\t" << setiosflags(ios::left) << setw(30) << _signs << " "
				<< _date << endl << endl;
			i++;
		}
		reFile.close();
		cout << i << ".\t返回";
		int select;
		cout << endl << endl << "选择： ";
		cin >> select;
		if (select == i)
			return;
		i = 1;
		ifstream reFile2("recordtitle.txt");
		assert(reFile2);
		while (reFile2 >> _signs)
		{
			reFile2.get();
			getline(reFile2, _date);
			if (i == select)
			{
				system("cls");
				string fname = "record" + _signs + ".txt";
				ifstream reFile3(fname.c_str());
				assert(reFile3);
				cout << reFile3.rdbuf();
				reFile3.close();
				cout << endl << endl;
				system("pause");
				break;
			}
			getline(reFile, _date);
			i++;
		}
		reFile2.close();
	}
}

//默认构造函数
whatdate::whatdate():_book()
{
	_week = "xxx";
	_month = "xxx";
	_day = "xxx";
	_year = "xxx";
}

//首页
char whatdate::inter_face()
{
	system("cls");
	char choose;
	cout << endl;
	cout << endl;
	cout << "\t  ●                   日历记事本                       ●  " << endl
		 << "\t ===========================================================" << endl
	     << "\t ※                                                       ※"<<endl
		 << "\t ※                   1.  记事                            ※" << endl
		 << "\t ※                                                       ※" << endl
		 << "\t ※                   2.  浏览                            ※" << endl
		 << "\t ※                                                       ※" << endl
		 << "\t ※                   3.  管理                            ※" << endl
		 << "\t ※                                                       ※" << endl
		 << "\t ※                   4.  日历查询                        ※" << endl
		 << "\t ※                                                       ※" << endl
		 << "\t ※                   5.  关闭记事本                      ※" << endl
		 << "\t ※                                                       ※" << endl
		 << "\t ※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※" << endl << endl << "\t\t";
	choose = getchar();
	return choose;
}

//日历查询

void whatdate::search_date()
{
	while (1)
	{
		system("cls");
		cout << endl << "\t\t 万年历查询" << endl << endl;
		cout << "\t●\t 1. 日历查询 " << endl << endl
			<< "\t●\t 2. 月历查询 " << endl << endl
			<< "\t●\t 3. 返回 " << endl << endl;
		char select = getchar();
		switch (select)
		{
		case '1':
			select_day();//日查询
			break;
		case '2':
			select_month();//月查询
			break;
		case '3':
			return;
		default:
			break;
		}
	}
}

//备忘录管理
void whatdate::book_manage()
{
	char choose;
	while (1)
	{
		system("cls");
		cout << endl << "\t\t管理备忘录！！！" << endl << endl;
		cout << endl << "\t●\t\t 1. 修改备忘录 " << endl
			<< endl << "\t●\t\t 2. 删除备忘录 " << endl
			<< endl << "\t●\t\t 3. 返回首页 " << endl << endl << "\t\t\t";
		choose = getchar();
		switch (choose)
		{
		case '1':
			_book.alter_book(); //修改备忘录
			break;
		case '2':
			_book.delete_book();//删除备忘录
			break;
		case '3':
			return;
			break;
		default:
			break;
		}
	}
}
//日历查询
void whatdate::select_day()
{
	system("cls");
	cout << endl << "\t\t万年历之日历查询 " << endl << endl;
	cout << "\t\t 请输入年月日（例如：2017 8 11）： ";
	cin >> _year >> _month >> _day;
	int days = 0;
	int i;
	for (i = 1; i < atoi(_year.c_str()); i++)
	{
		if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
			days += 366;
		else
			days += 365;
		days = days % 7;
	}
	if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
		month1[1] = 29;
	for (i = 0; i < atoi(_month.c_str()) - 1; i++)
		days += month1[i];
	days += atoi(_day.c_str());
	days = days % 7;
	month1[1] = 28;
	cout << endl << endl << "阳历： ";
	cout << _year << " 年 " << _month << " 月 "
		<< _day << " 日 \t" << week1[days - 1] << endl << endl;
	cout << "阴历： ";
	int Y2, M2, D2;
	GetLunar(atoi(_year.c_str()), atoi(_month.c_str()), atoi(_day.c_str()), Y2, M2, D2);
	cout << Y2 << " 年 " << M2 << " 月 " << D2 << " 日 " << endl << endl;
	system("pause");
}

//月历查询
void whatdate::select_month()
{
	system("cls");
	cout << endl << "\t\t 万年历之月历查询 " << endl << endl;
	cout << "\t 请输入某年某月（例如： 2017 8）：";
	cin >> _year >> _month;
	cout << endl << endl << _year << " 年 " << _month << " 月 ";
	if ((atoi(_year.c_str()) % 4 == 0 && atoi(_year.c_str()) % 100 != 0) || (atoi(_year.c_str()) % 400 == 0))
	{
		month1[1] = 29;
		cout << "\t\t\t\t\t    闰年" << endl;
	}
	else
		cout << "\t\t\t\t\t    平年" << endl;
	cout << "=================================================================" << endl << endl;
	cout << "星期日   星期一    星期二    星期三    星期四    星期五    星期六" << endl << endl;
	int days = 0;
	int i;
	int j;
	for (i = 1; i < atoi(_year.c_str()); i++)
	{
		if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
			days += 366;
		else
			days += 365;
		days = days % 7;
	}
	for (i = 0; i < atoi(_month.c_str()) - 1; i++)
		days += month1[i];
	days = (days + 1) % 7;
	for (j = 0; i < days; j++)
		cout << setw(10) << " ";
	cout << setw(3) << 1;

	for (j = 2; j <= month1[atoi(_month.c_str()) - 1]; j++)
	{
		days++;
		if (days % 7 == 0)
			cout << endl << endl << setw(3) << j;
		else
			cout << setw(10) << j;
	}
	cout << endl << endl << "===================================================================" << endl << endl;
	month1[1] = 28;
	fflush(stdin);
	system("pause");
}
//判断输入的公历年份是否为闰年，闰年则函数返回1，否则返回0
int whatdate::IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	else
		return 0;
}

//计算输入公历年份的1月1日为哦哦那个公元1年1月1日以来的第几天，返回天数
long whatdate::YearDays(int year)
{
	year--;
	return (year * 365 + year / 4 - year / 100 + year / 400 + 1);
}

//计算输入的公历日期为从公元1年1月1日以来的第几天,返回总天数 Total
long whatdate::TotalDays(int year, int month, int day)
{
	const int MonthDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	long Days = 0L;
	int i;
	if (month <= 0)
		month = 1;
	if (month > 12)
	{
		month--;
		year += month / 12;
		month %= 12;
		month++;
	}
	for (i = 1; i < month; i++)
		Days += 1;
	Days += YearDays(year);
	return Days + day - 1;
}

//   输入公历年月日,返回农历年月日,函数返回1表示成功,0表示失败     
//   如果M2返回负值,则说明是农历的闰月,月份值为其绝对值.
int whatdate::GetLunar(int Y1, int M1, int D1, int &Y2, int &M2, int &D2)
{
	short MBits[13] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 };
	long TDays;
	int Sum, Lest, i, Offset;
	Offset = Y1 - BEGINYEAR;
	if (Offset<0 || Offset>YEARCOUNT)
		return 0;
	TDays = TotalDays(Y1, M1, D1);
	Y2 = Y1;
	if (LunarIndex[Offset]._days > TDays)
	{
		if (Offset == 0)
			return 0;
		Offset--;
		Y2--;
	}
	Lest = (int)(TDays - LunarIndex[Offset]._days);
	for (Sum = i = 0; i < 13; i++)
	{
		if ((LunarIndex[Offset]._mon13&MBits[i]) != 0)
		{
			Sum += 30;
			if (Sum>Lest)
			{
				Sum -= 30;
				break;
			}
		}
		else
		{
			Sum += 29;
			if (Sum > Lest)
			{
				Sum -= 29;
				break;
			}
		}
	}
	if (i == 13)
		return 0;
	i++;
	if (i > LunarIndex[Offset]._leap)
	{
		i--;
		if (i == LunarIndex[Offset]._leap)
			i = -i;
	}
	M2 = i;
	D2 = Lest - Sum + 1;
	return 1;
}

int main()
{
	whatdate object;
	rebook abook;
	char select;
	while (select = object.inter_face())
	{
		switch (select)
		{
		case '1':
			abook.new_book();  //新建记事本
			break;
		case'2':
			abook.scanf_book();  //浏览
			break;
		case '3':
			object.book_manage();  //备忘录管理
			break;
		case '4':
			object.search_date();  //日历查询
			break;
		case '5':
			cout << endl << "\t谢谢使用！！！" << endl << endl << "\t";
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}