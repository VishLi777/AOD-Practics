#include <iostream>
#include <windows.h>
#include "funcc.h"
using namespace std;

int main()

{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "----------------------------------------------------" << endl;
	cout << "Внешние структуры данных - файлы и алгоритмы их обработки" << endl;
	cout << "----------------------------------------------------" << endl;
	int s;
	do {
		cout << "Выберите команду:" << endl;
		cout << "1 - Преобразовать текстовые данные в двоичный файл" << endl;
		cout << "2 - Вывод содержимого файла в нормальном виде" << endl;
		cout << "3 - Вывод содержимого файла в двоичным виде " << endl;
		cout << "4 - Поиск записи по ключу" << endl;
		cout << "5 - Удаление элемента по ключу" << endl;
		cout << "6 - Софрмировать текстовый файл из записей по начальному фрагменту(3 цифры) ключу" << endl;
		cout << "7 - Выход из программы" << endl;
		cout << "Введите команду: ";
		cin >> s;
		cout << endl;
		switch (s)
		{
		case 1:
			bin();
			break;
		case 2:
			outputNorm();
			break;
		case 3:
			outputBin();
			break;
		case 4:
			search();
			break;
		case 5:
			deleting();
			break;
		case 6:
			newFile();
			cout << "Файл сформирован keys.txt" << endl;
			break;
		case 7:
			cout << "Выход...";
			break;
		default: cout << "Ошибка выбора. Выберите число 1-5" << endl;
		}
	} while (s != 6);
}