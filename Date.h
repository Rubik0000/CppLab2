#pragma once
#include <string>
#include <fstream>

//структура "дата"
struct Date {
	int day;
	int month;
	int year;
};

//считывание даты из строки
Date* DateFromStr(std::string str);
//вывод даты в консоль
void DateToConsole(Date date);
//вывод даты в файл
void DateToFile(Date d, std::fstream *f);
//сравнение дат
int CompareDates(Date d1, Date d2);


