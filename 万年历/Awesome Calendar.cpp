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
	ofstream tempFile("record\\temp.txt");
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
	cout << endl << endl << "��¼�Ѿ����棡����" << endl << endl;
	system("pause");
}