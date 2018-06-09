#include <iostream>
#include <cstdlib>
#include "Date.h"

//�������� �� ���������� ���
bool LeapYear(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

//���������� ���-�� ���� � ������ 
int CountDayInMonth(int month, int year) {
	switch (month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		return LeapYear(year) ? 29 : 28;
	default:
		return 31;
	}
}

//��������� ����� �� ���������� ������������� ����
int GetNum(std::string str, int &num) {
	int p = str.find('.', 0);
	if (p == 1 || p == 2) {
		const char *ch = str.c_str();
		num = atoi(ch);
		return p;
	}
	return -1;
}

//�������� ���� �� ������
Date* DateFromStr(std::string str) {
	if (str == "") {
		return nullptr;
	}
	str += '.';
	Date d;
	int p = GetNum(str, d.day);
	if (p == -1) {
		return nullptr;
	}
	str = str.substr(p + 1);
	p = GetNum(str, d.month);
	if (p == -1) {
		return nullptr;
	}
	str = str.substr(p + 1);
	p = GetNum(str, d.year);
	if (p == -1) {
		return nullptr;
	}
	if (d.month >= 1 && d.month <= 12 && d.year > 0 &&
		d.day >= 1 && d.day <= CountDayInMonth(d.month, d.year)) 
	{
		return &d;
	}
	return nullptr;
}

//����� ���� � �������
void DateToConsole(Date date) {
	std::cout << date.day << '.' << date.month << '.' << date.year;
}

//����� ���� � ����
void DateToFile(Date d, std::fstream *f) {
	*f << d.day << '.' << d.month << '.' << d.year;
}

//��������� ���
int CompareDates(Date d1, Date d2) {
	if (d1.year > d2.year) 
		return 1;
	if (d1.year < d2.year) 
		return -1;
	if (d1.month > d2.month) 
		return 1;
	if (d1.month < d2.month) 
		return -1;
	if (d1.day > d2.day) 
		return 1;
	if (d1.day < d2.day) {
		return -1;
	}
	else {
		return 0;
	}
}
