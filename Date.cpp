#include <iostream>
#include <cstdlib>
#include "Date.h"

//проверка на высокосный год
bool LeapYear(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

//возвращает кол-во дней в месяце 
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

//выделение числа из строкового представления даты
int GetNum(std::string str, int &num) {
	int p = str.find('.', 0);
	if (p == 1 || p == 2) {
		const char *ch = str.c_str();
		num = atoi(ch);
		return p;
	}
	return -1;
}

//вделение даты из строки
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

//вывод даты в консоль
void DateToConsole(Date date) {
	std::cout << date.day << '.' << date.month << '.' << date.year;
}

//вывод даты в файл
void DateToFile(Date d, std::fstream *f) {
	*f << d.day << '.' << d.month << '.' << d.year;
}

//сравнение дат
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
