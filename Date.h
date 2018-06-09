#pragma once
#include <string>
#include <fstream>

//��������� "����"
struct Date {
	int day;
	int month;
	int year;
};

//���������� ���� �� ������
Date* DateFromStr(std::string str);
//����� ���� � �������
void DateToConsole(Date date);
//����� ���� � ����
void DateToFile(Date d, std::fstream *f);
//��������� ���
int CompareDates(Date d1, Date d2);


