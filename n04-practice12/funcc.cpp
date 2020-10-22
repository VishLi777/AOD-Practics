#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <bitset>

#include <fstream>

#include <string>

#include "funcc.h"
#include <list>

using namespace std;
struct Node {
	string Num = "";
	string Adres = "";
	string FIO = "";
};

void bin() {
	setlocale(LC_ALL, "rus");
	ifstream ifs;
	ifs.open("aod.txt");
	ofstream ofs;
	ofs.open("aod2.txt");
	int counter = 1;
	ofs << "1.";
	while (!ifs.eof())
	{
		char ch = ifs.get();
		if ((int)ch != -1) {
			if ((ch) == '\n') {
				counter++;
				ofs << "\n" << counter << '.';
			}
			else
				ofs << bitset<CHAR_BIT>(ch);
		}
	}
	cout << "двоичный код записан в aod2.txt" << endl;
}
void outputBin()
{
	setlocale(LC_ALL, "rus");
	ifstream ifs;
	ifs.open("aod2.txt");
	int counter = 1;
	while (!ifs.eof())
	{
		char ch = ifs.get();
		if ((int)ch != -1) {
			cout << ch;
		}
	}
	cout << endl;
}
bool searching(string line_for_searching, int key) {
	if (key == stoi(line_for_searching.substr(0, 5))) {
		return true;
	}
	else
	{
		return false;
	}

}
void search()
{
	setlocale(LC_ALL, "rus");
	string in_line, new_line = "";
	ifstream ifs;
	ifs.open("aod.txt");
	int key;
	int k = 0;
	cout << "Введите ключ записи для поиска" << endl;
	cin >> key;
	while (getline(ifs, in_line))
	{
		if (searching(in_line, key) == true) {
			k++;
			new_line = new_line + in_line + '\n';
		}
	}
	if (k != 1 & k > 0) {
		cout << "Найдено несколько совпадений: " << endl;
		cout << new_line << endl;
	}
	else if (new_line != "")
	{
		cout << "Найдено одно совпадение: " << endl;
		cout << new_line << endl;
	}
	if (new_line == "") {
		cout << "Совпадений не найдено" << endl;
	}
}

void deleting() {
	setlocale(LC_ALL, "rus");
	string in_line,new_line = "";
	ifstream ifs;
	ifs.open("aod.txt");
	int key;
	cout << "Введите ключ записи для удаления" << endl;
	cin >> key;
	if (key < 10) {
		while (getline(ifs, in_line))
		{
			if (searching(in_line, key) == false)
				new_line = new_line + in_line + '\n';
		}
	}
	cout << "Удаление выполнено проверьте текстовый файл aod.txt" << endl;
	ofstream ofs;
	ofs.open("aod.txt");
	ofs << new_line;
}

int sizeFile()
{
	char* str = new char[1024];
	int i = 0;
	ifstream base("aod.txt");
	while (!base.eof())
	{
		base.getline(str, 1024, '\n');
		i++;
	}
	base.close();
	delete str;
	cout << i << '\n';
	return i;
}

int  searching2(string line_for_searching2) {
	int key = stoi(line_for_searching2.substr(0, 3));

	return key;

}



void newFile()
{
	setlocale(LC_ALL, "rus");
	string in_line, new_line = "";
	ifstream ifs;
	ifs.open("aod.txt");
	ofstream ofs;
	ofs.open("keys.txt");

	while (getline(ifs, in_line))
	{
		if (searching2(in_line) != 0)
		{
			ofs << searching2(in_line);
			ofs << " " << "\n";
		}
	}

}

void outputNorm() {
	ifstream ofs;
	ofs.open("aod2.txt");
	int counter = 0;
	string ch;
	while (getline(ofs, ch))
	{
		ch.erase(0, ch.find('.') + 1);
		while (!ch.empty()) {
			cout << static_cast<char>(bitset<CHAR_BIT>(ch.substr(0, 8)).to_ulong());
			ch.erase(0, 8);
		}
		cout << endl;
	}
}