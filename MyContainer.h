#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

//класс контейнер 
template <typename T>
class MyContainer
{
private:
	std::vector<T> _records; //контейнер

	//вопрос пользователю
	bool InputQuery() {
		char c;
		do {
			std::cout << "N/Y? ";
			std::cin >> c;
		} while (c != 'n' && c != 'N' && c != 'y' && c != 'Y');
		return c == 'Y' || c == 'y';
	}

	//вернуть индекс элемента
	int GetIndex(T el) {
		int i = 0;
		for (T rec : _records) {
			if (rec == el) {
				return i;
			}
			++i;
		}
		return -1;
	}

public:

	//конструктор
	MyContainer() {}

	//деструктор
	~MyContainer() {
		Clear();
	}

	//кол-во элементов в контейнере
	int Count() {
		return _records.size();
	}

	//сортировка
	void Sort(bool(*compare)(T, T)) {
		std::sort(_records.begin(), _records.end(), compare);
	}

	//выборка подмножества по заданному критерию
	MyContainer<T> LinearSearch(bool(*func)(T, T), T crit) {
		MyContainer<T> subSet;
		for (T rec : _records) {
			if (func(rec, crit)) {
				subSet.Add(rec);
			}
		}
		return subSet;
	}

	//бинарный поиск
	MyContainer<T> BinarySearch(int(*func)(T, T), T crit, bool(*compare)(T, T)) {
		Sort(compare);
		MyContainer<T> subSet;
		int left = 0, right = _records.size() - 1, mid = left + (right - left) / 2;
		while (left < right){
			if (func(_records[mid], crit) >= 0) {
				right = mid;
			}
			else {
				left = mid + 1;
			}
			mid = left + (right - left) / 2;
		}
		if (func(_records[mid], crit) == 0) {
			subSet.Add(_records[mid]);
			bool lequal, requal;
			for (int i = mid - 1, j = mid + 1; i >= 0 || j < _records.size(); --i, ++j) {
				lequal = requal = false;
				if (i >= 0 && func(_records[i], crit) == 0) {
					subSet.Add(_records[i]);
					lequal = true;
				}
				if (j < _records.size() && func(_records[j], crit) == 0){
					subSet.Add(_records[j]);
					requal = true;
				}
				if (!(lequal || requal)) {
					break;
				}
			}
		}
		return subSet;
	}

	//очистка
	void Clear() {
		_records.clear();
	}

	//добавить 
	void Add(T client) {
		_records.push_back(client);
	}

	//удаление по индексу
	bool RemoveInd(int ind){
		if (ind < 0 || ind >= _records.size()) {
			return false;
		}
		_records.erase(_records.begin() + ind);
	}

	//удаление по значению
	bool RemoveVal(T client) {
		int ind = GetIndex(client);
		return RemoveInd(ind);
	}

	//изменение записи в консоле
	bool Change(bool(*func)(T&), int ind) {
		if (ind < 0 || ind >= _records.size()) {
			return false;
		}
		do {
			if (func(_records[ind])) {
				std::cout << "«апись изменена, продолжить изменение? " << std::endl;
			}
			else {
				std::cout << "Ќе удалось изменить запись, продолжить? " << std::endl;
			}
		} while (InputQuery());
		return true;
	}


	//ввод с консоли
	void FromConsole(bool(*input)(T&)){
		T t;
		do {
			std::cout << std::endl;
			if (input(t)) {
				Add(t);
				std::cout << "«апись успешно довавлена, еще? ";
			}
			else {
				std::cout << "¬ведено некорректное значение, повторить? ";
			}
		} while (InputQuery());
	}

	//считывание из файла
	bool FromFile(bool(*input)(T&, std::fstream*), std::fstream *f) {
		if (!f->is_open()) {
			return false;
		}
		T tmp;
		while (!f->eof()) {
			if (input(tmp, f)) {
				Add(tmp);
			}
			else {
				return false;
			}
		}
		return true;
	}

	//запись в поток
	void ToFile(void(*output)(T, std::fstream*), std::fstream *f) {
		if (!f->is_open()) {
			throw "‘айл не открыт";
		}
		for (T r : _records) {
			output(r, f);
		}
	}

	//вывод в консоль
	void ToConsole(void(*output)(T)) {
		std::cout << std::endl;
		int i = 1;
		for (T r : _records) {
			std::cout << i++ << std::endl;
			output(r);
		}
		std::cout << "¬сего записей: " << _records.size() << std::endl;
	}
};
