#include <iostream>
#include "Deposit.h"
#include "Date.h"

//���� �����
bool InputNum(double & num) {
	std::cin >> num;
	bool OK = std::cin.good();
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return OK;
}

bool InputNum(int &num) {
	std::cin >> num;
	bool OK = std::cin.good();
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return OK;
}

//���� � �������
bool DepositFromConsole(Deposit &dep) {
	std::cout << "������� ����� �����: ";
	if (!InputNum(dep.number) || dep.number < 0) {
		return false;
	}
	std::cout << "������� ���: ";
	if (!InputNum(dep.code) || dep.code < 0) {
		return false;
	}
	std::cout << "������� ���: ";
	std::cin >> dep.fio;
	if (dep.fio == "") {
		return false;
	}
	std::cout << "������� �����: ";
	if (!InputNum(dep.sum) || dep.sum < 0) {
		return false;
	}
	std::string str;
	std::cout << "������� ���� �������� �����: ";
	std::cin >> str;
	Date *d = DateFromStr(str);
	if (d == nullptr) {
		return false;
	}
	dep.date = *d;
	std::cout << "������� ������� �����������: ";
	if (!InputNum(dep.percent) || dep.percent < 0 || dep.percent > 1) {
		return false;
	}
	return true;
}

//����� �� �������
void DepositToConsole(Deposit d) {
	std::cout << "����� �����: " << d.number << std::endl;
	std::cout << "���: " << d.code << std::endl;
	std::cout << "���: " << d.fio << std::endl;
	std::cout << "�����: " << d.sum << std::endl;
	std::cout << "���� ��������: ";
	DateToConsole(d.date);
	std::cout << std::endl;
	std::cout << "������� �����������: " << d.percent << std::endl;
}

//��������� � �������
bool ChangeDeposit(Deposit &dep) {
	int ans, num;
	do{
		std::cout << "1 - ����� �����" << std::endl;
		std::cout << "2 - ��� �����" << std::endl;
		std::cout << "3 - ���" << std::endl;
		std::cout << "4 - ����� �� �����" << std::endl;
		std::cout << "5 - ���� �������� �����" << std::endl;
		std::cout << "6 - ������� �����������:" << std::endl;
		std::cout << "0 - ������" << std::endl;
		std::cin >> ans;
	} while (ans < 0 || ans > 6);
	if (ans == 0) {
		return false;
	}
	std::cout << "������� ����� ��������: ";
	std::string str;
	Date *d;
	switch (ans)
	{
	case 1:
		if (InputNum(num) && num >= 0) {
			dep.number = num;
			return true;
		}
		return false;
	case 2:
		if (InputNum(num) && num >= 0) {
			dep.code = num;
			return true;
		}
		return false;
	case 3:
		std::cin >> str;
		if (str != "") {
			dep.fio = str;
			return true;
		}
		return false;
	case 4:
		if (InputNum(num) && num >= 0) {
			dep.sum = num;
			return true;
		}
		return false;
	case 5:
		std::cin >> str;
		d = DateFromStr(str);
		if (d != nullptr) {
			dep.date = *d;
			return true;
		}
		return false;
	case 6:
		double per;
		if (InputNum(per) && per >= 0 && per <= 1) {
			dep.percent = per;
			return true;
		}
		return false;
	}
}

//���������� ����� �� �����
bool DepositFromFile(Deposit &dep, std::fstream *f) {
	Deposit d;
	if (!f->is_open()) {
		return false;
	}
	std::string str;
	try {
		*f >> d.number;
		*f >> d.code;
		*f >> d.fio;
		*f >> d.sum;
		*f >> str;
		Date *dat = DateFromStr(str);
		if (dat == nullptr) {
			return false;
		}
		d.date = *dat;
		*f >> d.percent;
		if (d.percent < 0 || d.percent > 1) {
			return false;
		}
		dep = d;
		return true;
	}
	catch (...) {
		throw "�� ������� ������� �� �����";
	}
}

//����� � ����
void DepositToFile(Deposit dep, std::fstream *f) {
	*f << dep.number << '\n';
	*f << dep.code << '\n';
	*f << dep.fio << '\n';
	*f << dep.sum << '\n';
	DateToFile(dep.date, f);
	*f << '\n' << dep.percent << '\n';
	*f << '\n';
}




