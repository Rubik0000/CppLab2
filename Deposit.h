#pragma once
#include <string>
#include <fstream>
#include "Date.h"


//��������� "����"
struct Deposit {
	int number;
	int code;
	std::string fio;
	int sum;
	Date date;
	double percent;
};

//���� �����
bool InputNum(double &num);
bool InputNum(int &num);

//���� ����� � �������
bool DepositFromConsole(Deposit &dep);

//����� �� �������
void DepositToConsole(Deposit d);

//��������� � �������
bool ChangeDeposit(Deposit &dep);

//���� �� �����
bool DepositFromFile(Deposit &dep, std::fstream *f);

//����� � ����
void DepositToFile(Deposit dep, std::fstream *f);


