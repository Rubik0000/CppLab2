#pragma once
#include <string>
#include <fstream>
#include "Date.h"


//структура "счет"
struct Deposit {
	int number;
	int code;
	std::string fio;
	int sum;
	Date date;
	double percent;
};

//ввод числа
bool InputNum(double &num);
bool InputNum(int &num);

//ввод счета с консоли
bool DepositFromConsole(Deposit &dep);

//вывод на консоль
void DepositToConsole(Deposit d);

//изменение в консоли
bool ChangeDeposit(Deposit &dep);

//ввод из файла
bool DepositFromFile(Deposit &dep, std::fstream *f);

//вывод в файл
void DepositToFile(Deposit dep, std::fstream *f);


