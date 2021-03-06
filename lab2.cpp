#include <iostream>
#include "Date.h"
#include "Deposit.h"
#include "MyContainer.h"

//меню
void Menu(MyContainer<Deposit> &cont) {
	int ans, num;
	Deposit dep, crit, res;
	std::fstream file;
	std::string fileName, str;
	MyContainer<Deposit> subSet;
	bool(*linerF)(Deposit d, Deposit crit);
	for (;;) {
		do {
			std::cout << "Выберите пункт меню" << std::endl;
			std::cout << "1 - Ввести с консоли" << std::endl;
			std::cout << "2 - Загрузить из файла" << std::endl;
			std::cout << "3 - Добавить запись" << std::endl;
			std::cout << "4 - Удалить запись" << std::endl;
			std::cout << "5 - Изменить запись" << std::endl;
			std::cout << "6 - Вывести на консоль" << std::endl;
			std::cout << "7 - Записать в файл" << std::endl;
			std::cout << "8 - Линейный поиск" << std::endl;
			std::cout << "9 - Бинарный поиск" << std::endl;
			std::cout << "10 - Очистить" << std::endl;
			std::cout << "0 - Выход" << std::endl;
			std::cin >> ans;
		} while (ans < 0 || ans > 12);
		switch (ans) {
		case 1:
			//-----------считать с консоли-------------
			cont.FromConsole(DepositFromConsole);
			break;
		case 2:
			//-----------загрузить из файла------------
			std::cout << "Введите имя файла ";
			std::cin >> fileName;
			file.open(fileName, std::fstream::in);
			if (cont.FromFile(DepositFromFile, &file)) {
				std::cout << "Данные загружены" << std::endl;
			}
			else {
				std::cout << "Не удалось загрузить данные" << std::endl;
			}
			file.close();
			break;
		case 3:
			//----------добавить запись--------
			if (DepositFromConsole(dep)) {
				cont.Add(dep);
			}
			else {
				std::cout << "Введены неверные данные" << std::endl;
			}
			break;
		case 4:
		case 5:
			//----------изменить или удалить запись---------
			if (cont.Count() == 0) {
				std::cout << "В контейнере отсутствуют данные" << std::endl;
				break;
			}
			//ввод номера записи
			do {
				std::cout << "Введите номер записи от 1 до " << cont.Count() << ' ' << std::endl;
				std::cin >> num;
			} while (num < 1 || num > cont.Count());
			//удаление записи
			if (ans == 4) {
				if (cont.RemoveInd(num - 1)) {
					std::cout << "Запись успешно удалена" << std::endl;
				}
				else {
					std::cout << "Не удалось удалить запись" << std::endl;
				}
			}
			//изменение записи
			else {
				if (cont.Change(ChangeDeposit, num - 1)) {
					std::cout << "Запись успешно изменена" << std::endl;
				}
				else {
					std::cout << "Не удалось изменить запись" << std::endl;
				}
			}
			break;
		case 6:
			//---------------вывод на консоль------------
			cont.ToConsole(DepositToConsole);
			break;
		case 7:
			//---------------запись в файл------------------
			std::cout << "Введите имя файла ";
			std::cin >> fileName;
			file.open(fileName, std::fstream::out);
			if (file.is_open()) {
				cont.ToFile(DepositToFile, &file);
			}
			else {
				std::cout << "Не удалось открыть файл" << std::endl;
			}
			file.close();
			break;

		case 8:
		case 9:
			//------------------------поиск по критерию----------------------------
			int anst;
			//ввод критерия
			do {
				std::cout << "1 - Поиск по номеру счета" << std::endl;
				std::cout << "2 - Поиск по дате" << std::endl;
				std::cout << "3 - Поиск по владельцу" << std::endl;
				std::cout << "0 - Отмена" << std::endl;
				std::cin >> anst;
			} while (anst < 0 || anst > 3);
			Date *date;
			if (anst == 0){
				break;
			}
			switch (anst) {
			case 1:
				//--------------поиск по номеру счета--------------
				std::cout << "Введите номер счета ";
				int num;
				std::cin >> num;
				crit.number = num;
				bool OK;
				//линейный поиск
				if (ans == 8) {
					subSet = cont.LinearSearch([](Deposit d, Deposit crit) {
						return d.number == crit.number; }, crit);
				}
				//бинарный поиск
				else {
					subSet = cont.BinarySearch(
						[](Deposit d, Deposit crit) {
							if (d.number == crit.number)
								return 0;
							else if (d.number < crit.number)
								return -1;
							else
								return 1; 
						},
						crit,
						[](Deposit d1, Deposit d2) {
							return d1.number < d2.number; 
						});
				}
				if (subSet.Count() == 0) {
					std::cout << "Данных не найдено" << std::endl;
					break;
				}
				do {
					std::cout << "1 - Вывести в файл" << std::endl;
					std::cout << "2 - Вывести на консоль" << std::endl;
					std::cout << "0 - Отмена" << std::endl;
					std::cin >> anst;
				} while (anst < 0 || anst > 2);
				if (anst == 0)
					break;

				//вывод подмножества на консоль
				if (anst == 2) {
					subSet.ToConsole(DepositToConsole);
					break;
				}
				//вывод подмножества в файл в файл
				std::cout << "Введите имя файла ";
				std::cin >> fileName;
				file.open(fileName, std::fstream::out);
				if (file.is_open()) {
					subSet.ToFile(DepositToFile, &file);
					std::cout << "Данные загружены" << std::endl;
				}
				else {
					std::cout << "Не удалось открыть файл" << std::endl;
				}
				file.close();
				break;

			case 2:
				//-------------поиск по дате-------------- 
				std::cout << "Введите дату ";
				std::cin >> str;
				date = DateFromStr(str);
				if (date == nullptr) {
					std::cout << "Некорреткная дата" << std::endl;
					break;
				}
				crit.date = *date;
				//линейный поиск
				if (ans == 8) {
					subSet = cont.LinearSearch([](Deposit d, Deposit crit) {
						return CompareDates(d.date, crit.date) == 0; }, crit);
				}
				//бинарный поиск
				else {
					subSet = cont.BinarySearch(
						[](Deposit d, Deposit crit) {
							return CompareDates(d.date, crit.date);
						},
						crit,
						[](Deposit d1, Deposit d2) {
							return CompareDates(d1.date, d2.date) < 0;
						});
				}
				if (subSet.Count() == 0) {
					std::cout << "Данных не найдено" << std::endl;
					break;
				}
				do {
					std::cout << "1 - Вывести в файл" << std::endl;
					std::cout << "2 - Вывести на консоль" << std::endl;
					std::cout << "0 - Отмена" << std::endl;
					std::cin >> anst;
				} while (anst < 0 || anst > 2);
				if (anst == 0){
					break;
				}
				//вывод подмножества на консоль
				if (anst == 2) {
					subSet.ToConsole(DepositToConsole);
					break;
				}
				//вывод подмножества в файл в файл
				std::cout << "Введите имя файла ";
				std::cin >> fileName;
				file.open(fileName, std::fstream::out);
				if (file.is_open()) {
					subSet.ToFile(DepositToFile, &file);
					std::cout << "Данные загружены" << std::endl;
				}
				else {
					std::cout << "Не удалось открыть файл" << std::endl;
				}
				file.close();
				break;

			case 3:
				//------------поиск по владельцу--------------
				std::cout << "Введите имя владельца ";
				std::cin >> str;
				crit.fio = str;
				//линейный поиск
				if (ans == 8) {
					subSet = cont.LinearSearch([](Deposit d, Deposit crit) {
						return d.fio == crit.fio; }, crit);
				}
				//бинарный поиск
				else {
					subSet = cont.BinarySearch(
						[](Deposit d, Deposit crit) {
							
							if (d.fio < crit.fio)
								return -1;
							else if (d.fio > crit.fio)
								return 1;
							else
								return 0;
						},
						crit,
						[](Deposit d1, Deposit d2) {
							return d1.fio < d2.fio;
						});
				}
				//вывод подмножества на консоль
				if (anst == 2) {
					subSet.ToConsole(DepositToConsole);
					break;
				}
				if (subSet.Count() == 0) {
					std::cout << "Данных не найдено" << std::endl;
					break;
				}
				do {
					std::cout << "1 - Вывести в файл" << std::endl;
					std::cout << "2 - Вывести на консоль" << std::endl;
					std::cout << "0 - Отмена" << std::endl;
					std::cin >> anst;
				} while (anst < 0 || anst > 2);
				if (anst == 0) {
					break;
				}
				if (anst == 2) {
					subSet.ToConsole(DepositToConsole);
					break;
				}
				//вывод подмножества в файл в файл
				std::cout << "Введите имя файла ";
				std::cin >> fileName;
				file.open(fileName, std::fstream::out);
				if (file.is_open()) {
					subSet.ToFile(DepositToFile, &file);
					std::cout << "Данные загружены" << std::endl;
				}
				else {
					std::cout << "Не удалось открыть файл" << std::endl;
				}
				file.close();
				break;
			}
			break;

		case 10:
			//---------------очистка контенера-----------------
			cont.Clear();
			std::cout << "Контейнер очищен" << std::endl;
			break;
			//-------------выход-------------
		case 0:
			return;
		}
		system("pause");
		std::cout << std::endl;
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	MyContainer<Deposit> bank;
	Menu(bank);
    return 0;
}

