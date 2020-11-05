#include <limits>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "GraphElements.h"
#include "Graph.h"
#include "DijkstraShortestPathAlg.h"
#include "YenTopKShortestPathsAlg.h"
#include <windows.h>
using namespace std;

void GraphIn()
{
	setlocale(LC_ALL, "RUS");
	int i, n;
	int l;
	char a='@', c;
	ofstream f;
	f.open("D://domashka//equation//n05-practice13//test_10", ios::out);
	cout << "Введите количество вершин - ";
	cin >> n;
	f << n << "\n" << "\n";
	cout << "Ввод путей окончен как только первая вершина равна '?'!" << endl;
	while(a!='?'){
		cout << "Первая вершина - ";
		cin >> a;
		if (a != '?') {
			f << a << "\t";
			cout << "Вторая вершина - ";
			cin >> c;
			f << c << "\t";
			cout << "Длина пути - ";
			cin >> l;
			f << l << "\n";
		}
	}
	f.close();
}
void Yen() {
	char one, two;
	cout << "Введите две вершины между которыми нужно искать путь?" << endl;
	cin >> one;
	cin >> two;
	cout << "--------------Метод Йена-----------------" << endl;
	Graph my_graph("n05-practice13/test_10");
	YenTopKShortestPathsAlg yenAlg(my_graph, my_graph.get_vertex((int)one - 65),
		my_graph.get_vertex((int)two - 65));

	int j = 0;
	while (yenAlg.has_next())
	{
		++j;
		yenAlg.next()->PrintOut(cout);
	}
}
void Dijkstra() {
	char one, two;
	cout << "Введите две вершины между которыми нужно искать путь?" << endl;
	cin >> one;
	cin >> two;
	cout << "--------------Метод Дейкстры-----------------" << endl;
	Graph* my_graph_pt = new Graph("n05-practice13/test_10");
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result =
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex((int)one - 65), my_graph_pt->get_vertex((int)two - 65));
	result->PrintOut(cout);
}

void testDijkstraGraph()
{
	char one, two;
	cout << "Введите две вершины между которыми нужно искать путь?" << endl;
	cin >> one;
	cin >> two;
	Graph* my_graph_pt = new Graph("n05-practice13/test_16");
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result =
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex((int)one - 65), my_graph_pt->get_vertex((int)two - 65));
	result->PrintOut(cout);
}

void testYenAlg()
{
	char one, two;
	cout << "Введите две вершины между которыми нужно искать путь?" << endl;
	cin >> one;
	cin >> two;
	Graph my_graph("n05-practice13/test_16");
	YenTopKShortestPathsAlg yenAlg(my_graph, my_graph.get_vertex((int)one - 65),
		my_graph.get_vertex((int)two - 65));

	int i = 0;
	while (yenAlg.has_next())
	{
		++i;
		yenAlg.next()->PrintOut(cout);
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int s;
	cout << "----------------------------------------------------" << endl;
	cout << "Метод ЙЕНА(Граф 14.4.5)" << endl;
	cout << "----------------------------------------------------" << endl;
	do {
		cout << "Выберите команду:" << endl;
		cout << "1 - Тестовый прогон метода Дейкстры на графе приведенным в задании" << endl;
		cout << "2 - Тестовый прогон метода Йена на графе приведенным в задании" << endl;
		cout << "3 - Ввод графа" << endl;
		cout << "4 - Метод Дейкстры на введеном графе" << endl;
		cout << "5 - Метод Йена на введеном графе" << endl;
		cout << "6 - Выход из программы" << endl;
		cout << "Введите команду: ";
		cin >> s;
		cout << endl;
		switch (s)
		{
		case 1:
			testDijkstraGraph();
			break;
		case 2:
			testYenAlg();
			break;
		case 3:
			GraphIn();
			break;
		case 4:
			Dijkstra();
			break;
		case 5:
			Yen();
		case 6:
			cout << "Выход...";
			break;
		default: cout << "Ошибка выбора. Выберите число 1-6" << endl;
		}
	} while (s != 6);
}
