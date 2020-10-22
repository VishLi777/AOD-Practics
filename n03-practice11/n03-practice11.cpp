#include <iostream>
#include <windows.h>
using namespace std;

struct Node {
	long long Num;
	string Comp;
	string FIO;
	Node(long long Num, string Comp, string FIO) {
		this->Num = Num;
		this->Comp = Comp;
		this->FIO = FIO;
	}
};

struct Hash {
	Node* data[30];
	Hash() {
		for (int i = 0; i < 30; i++) {
			data[i] = NULL;
		}
	}
	//Функция хеширование создаем индексы для нашей хеш таблицы
	int HashFunc(long long Num) {
		return Num % 16; // 16 - размер номера страхового полиса
	}
	//Проверка не пуста ли наша хеш таблица
	int Proverka() {
		int proverka = 0;
		for (int i = 0; i < 30; i++) {
			if (data[i] == NULL) {
				proverka++;
			}
		}
		return proverka;
	}
	//Поиск элемента в хеш таблице
	int FindItem(long long key) {
		int pr = Proverka();
		if (pr != 30) {
			int i = HashFunc(key);
			if (data[i] == NULL) {
				cout << "Элемент не найден!" << endl;
				return -1;
			}
			else if (data[i]->Num == key) {
				return i;
			}
			else {
				for (int x = 1; x <= 7; x++) {
					if (data[(i + (x * x))]->Num == key)
					{
						return (i + (x * x));
					}
				}
				cout << "Элемент не найден!" << endl;
				return -1;
			}
		}
		else
		{
			cout << "Таблица пуста!" << endl;
			cout << endl;
		}
	}
	//Удаление элемента из хеш таблицы
	void DeleteItem(long long key)
	{
		int pr = Proverka();
		if (pr != 30) {
			int del = FindItem(key);
			if (del != -1) {
				data[del] = NULL;
				cout << "Элемент на позиции- " << del << " удалён!" << endl;
			}
			else
			{
				cout << "Элемент не найден!" << endl;
			}
		}
		else
		{
			cout << "Таблица пуста!" << endl;
			cout << endl;
		}
	}

	//Добавление элемента в хеш таблицу
	void AddItem(long long Num, string Comp, string FIO) {
		int i = HashFunc(Num);
		//Если коллизий не вызванно, просто добавляем элемент в нашу хэш таблицу
		if (data[i] == NULL) {
			data[i] = new Node(Num, Comp, FIO);
		}
		else //Если вызванна КОЛЛИЗИЯ тогда, используем квадратичное пробирование
		{
			for (int x = 1; ; x++) {
				if (data[(i + (x * x))] == NULL)
				{
					data[(i + (x * x))] = new Node(Num, Comp, FIO);
					break;
				}
			}
		}
	}
	//Вывод хеш таблицы на экран
	void PrintHash() {
		int pr = Proverka();
		if (pr != 30) {
			for (int i = 0; i < 30; i++) {
				if (data[i] != NULL) {
					cout << "Позиция - " << i << " Значение - " << (long long)(data[i]->Num) << endl;
				}
			}
		}
		else
		{
			cout << "Таблица пуста!" << endl;
			cout << endl;
		}
	}
};

int main()
{
	SetConsoleCP(1251); //для отображения русского языка
	SetConsoleOutputCP(1251);
	Hash* hash = new Hash;
	int s;
	cout << "----------------------------------------------------" << endl;
	cout << "    Хэш таблица (Квадратичное пробирование)" << endl;
	cout << "----------------------------------------------------" << endl;
	long long num;
	long long key;
	string comp;
	string name;
	do {
		cout << "Выберите команду: " << endl;
		cout << "1 - Добавление элемента в хэш таблицу" << endl;
		cout << "2 - Удаление элемента из хэш таблицы" << endl;
		cout << "3 - Вывод хэш таблицы" << endl;
		cout << "4 - Поиск элемента в хэш таблице" << endl;
		cout << "5 - Выход из программы" << endl;
		cout << "Введите команду: ";
		cin >> s;
		cout << endl;
		switch (s)
		{
		case 1:
			cout << "Введите номер страхового полиса(16-значное число)" << endl;
			cin >> num;
			cout << "Введите название страховой компании" << endl;
			cin >> comp;
			cout << "Введите фамилию владельца" << endl;
			cin >> name;
			hash->AddItem(num, comp, name);
			break;
		case 2:
			cout << "Введите номер страхoвого полиса" << endl << endl;
			cin >> key;
			hash->DeleteItem(key);
			break;
		case 3:
			hash->PrintHash();
			break;
		case 4:
			cout << "Введите номер страхoвого полиса(Ключ)" << endl << endl;
			cin >> key;
			if (hash->FindItem(key) != -1)
			{
				cout << "Элемент найден!" << endl;
				cout << "Номер - " << hash->data[hash->FindItem(key)]->Num << endl;
				cout << "Компания - " << hash->data[hash->FindItem(key)]->Comp << endl;
				cout << "ФИО - " << hash->data[hash->FindItem(key)]->FIO << endl;
			}
			break;
		case 5:
			cout << "Выход...";
			break;
		default: cout << "Ошибка выбора. Выберите число 1-5" << endl;
		}
	} while (s != 5);
}
