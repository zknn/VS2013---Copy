#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"

//���캯��
rebook::rebook()
{
	_where = "xxx";  //�ص�
	_things = "xxx"; //�¼�
	_what = "xxx"; //�¼�����
	_signs = "xxx"; //����
	_date = "xxx"; //����
}

//�½�����¼
void rebook::new_book()
{
	system("cls");
	cout << endl << "���£��ԡ�#����ʾ������" << endl;
	time_t timer;
	time(&timer);
	cout << endl << "ʱ�䣺 " << asctime(localtime(&timer)) << endl;
	cout << "���⣺";
	cin >> _signs;
	ofstream tempFile("recordtemp.txt");
	time(&timer);
	tempFile << "ʱ�䣺 " << asctime(localtime(&timer)) << endl << "���⣺ " << _signs << endl << endl << "���ݣ� ";
	cout << endl << "���ݣ� " << endl;
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
	cout << endl << endl << "��¼�Ѿ����棡����" << endl << endl;
	system("pause");
}

//�޸ı���¼

void rebook::alter_book()
{
	while (1)
	{
		system("cls");
		cout << endl << "��ѡ�������޸ĵı��⣺ " << endl << endl;
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
		cout << endl << i << ".\t����" << endl << endl;
		cout << "ѡ�� ";
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
				cout << endl << "����Ҫ�޸ĵ��������£�" << endl << endl;
				cout << reFile3.rdbuf();
				reFile3.close();
				ofstream tempFile("recordtemp.txt");
				cout << endl << endl << "�������������µ����ݣ��ԡ�#��������:" << endl << endl;
				tempFile << "���⣺ " << _signs << endl << endl;
				tempFile << "���ݣ� ";
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
				cout << endl << endl << "���ݸ�����ɣ�����" << endl << endl;
				system("pause");
				break;
			}
			i++;
		}
		reFile2.close();
	}
}

//ɾ������¼
void rebook::delete_book()
{
	while (1)
	{
		system("cls");
		cout << endl << "��ѡ������Ҫɾ���ı��⣺ " << endl << endl;
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
		cout << endl << i << ".\t����" << endl << endl;
		int select;
		cout << "ѡ�� ";
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
				cout << endl << endl << "����Ҫɾ���ı���¼�������£�" << endl << endl;
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
		cout << endl << endl << "�ñ���¼�ѱ�ɾ��������" << endl << endl;
		system("pause");
	}
}

//������±�
void rebook::scanf_book()
{
	while (1)
	{
		system("cls");
		cout << endl << "���±���ѯ" << endl << endl;
		ifstream reFile("recordtitle.txt");
		if (!reFile)
		{
			ofstream reFile1("recordtitle.txt");
			reFile1.close();
			ifstream reFile("recordtitle.txt");
		}
		int i = 1;
		cout << "���\t" << setiosflags(ios::left) << setw(30) << "����" << "\t����" << endl << endl;
		while (reFile >> _signs)
		{
			reFile.get();
			getline(reFile, _date);
			cout << i << ".\t" << setiosflags(ios::left) << setw(30) << _signs << " "
				<< _date << endl << endl;
			i++;
		}
		reFile.close();
		cout << i << ".\t����";
		int select;
		cout << endl << endl << "ѡ�� ";
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

//Ĭ�Ϲ��캯��
whatdate::whatdate():_book()
{
	_week = "xxx";
	_month = "xxx";
	_day = "xxx";
	_year = "xxx";
}

//��ҳ
char whatdate::inter_face()
{
	system("cls");
	char choose;
	cout << endl;
	cout << endl;
	cout << "\t  ��                   �������±�                       ��  " << endl
		 << "\t ===========================================================" << endl
	     << "\t ��                                                       ��"<<endl
		 << "\t ��                   1.  ����                            ��" << endl
		 << "\t ��                                                       ��" << endl
		 << "\t ��                   2.  ���                            ��" << endl
		 << "\t ��                                                       ��" << endl
		 << "\t ��                   3.  ����                            ��" << endl
		 << "\t ��                                                       ��" << endl
		 << "\t ��                   4.  ������ѯ                        ��" << endl
		 << "\t ��                                                       ��" << endl
		 << "\t ��                   5.  �رռ��±�                      ��" << endl
		 << "\t ��                                                       ��" << endl
		 << "\t ������������������������������������������������������������" << endl << endl << "\t\t";
	choose = getchar();
	return choose;
}

//������ѯ

void whatdate::search_date()
{
	while (1)
	{
		system("cls");
		cout << endl << "\t\t ��������ѯ" << endl << endl;
		cout << "\t��\t 1. ������ѯ " << endl << endl
			<< "\t��\t 2. ������ѯ " << endl << endl
			<< "\t��\t 3. ���� " << endl << endl;
		char select = getchar();
		switch (select)
		{
		case '1':
			select_day();//�ղ�ѯ
			break;
		case '2':
			select_month();//�²�ѯ
			break;
		case '3':
			return;
		default:
			break;
		}
	}
}

//����¼����
void whatdate::book_manage()
{
	char choose;
	while (1)
	{
		system("cls");
		cout << endl << "\t\t������¼������" << endl << endl;
		cout << endl << "\t��\t\t 1. �޸ı���¼ " << endl
			<< endl << "\t��\t\t 2. ɾ������¼ " << endl
			<< endl << "\t��\t\t 3. ������ҳ " << endl << endl << "\t\t\t";
		choose = getchar();
		switch (choose)
		{
		case '1':
			_book.alter_book(); //�޸ı���¼
			break;
		case '2':
			_book.delete_book();//ɾ������¼
			break;
		case '3':
			return;
			break;
		default:
			break;
		}
	}
}
//������ѯ
void whatdate::select_day()
{
	system("cls");
	cout << endl << "\t\t������֮������ѯ " << endl << endl;
	cout << "\t\t �����������գ����磺2017 8 11���� ";
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
	cout << endl << endl << "������ ";
	cout << _year << " �� " << _month << " �� "
		<< _day << " �� \t" << week1[days - 1] << endl << endl;
	cout << "������ ";
	int Y2, M2, D2;
	GetLunar(atoi(_year.c_str()), atoi(_month.c_str()), atoi(_day.c_str()), Y2, M2, D2);
	cout << Y2 << " �� " << M2 << " �� " << D2 << " �� " << endl << endl;
	system("pause");
}

//������ѯ
void whatdate::select_month()
{
	system("cls");
	cout << endl << "\t\t ������֮������ѯ " << endl << endl;
	cout << "\t ������ĳ��ĳ�£����磺 2017 8����";
	cin >> _year >> _month;
	cout << endl << endl << _year << " �� " << _month << " �� ";
	if ((atoi(_year.c_str()) % 4 == 0 && atoi(_year.c_str()) % 100 != 0) || (atoi(_year.c_str()) % 400 == 0))
	{
		month1[1] = 29;
		cout << "\t\t\t\t\t    ����" << endl;
	}
	else
		cout << "\t\t\t\t\t    ƽ��" << endl;
	cout << "=================================================================" << endl << endl;
	cout << "������   ����һ    ���ڶ�    ������    ������    ������    ������" << endl << endl;
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
//�ж�����Ĺ�������Ƿ�Ϊ���꣬������������1�����򷵻�0
int whatdate::IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	else
		return 0;
}

//�������빫����ݵ�1��1��ΪŶŶ�Ǹ���Ԫ1��1��1�������ĵڼ��죬��������
long whatdate::YearDays(int year)
{
	year--;
	return (year * 365 + year / 4 - year / 100 + year / 400 + 1);
}

//��������Ĺ�������Ϊ�ӹ�Ԫ1��1��1�������ĵڼ���,���������� Total
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

//   ���빫��������,����ũ��������,��������1��ʾ�ɹ�,0��ʾʧ��     
//   ���M2���ظ�ֵ,��˵����ũ��������,�·�ֵΪ�����ֵ.
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
			abook.new_book();  //�½����±�
			break;
		case'2':
			abook.scanf_book();  //���
			break;
		case '3':
			object.book_manage();  //����¼����
			break;
		case '4':
			object.search_date();  //������ѯ
			break;
		case '5':
			cout << endl << "\tллʹ�ã�����" << endl << endl << "\t";
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}