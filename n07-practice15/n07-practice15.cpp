#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Функция вывода расстановок скобок и минимального значения умножения матриц
void print(int i, int j, int n, int* arr,
	char& name)
{
	// если осталась одна матрица
	if (i == j) {
		cout << name++;
		return;
	}
	cout << "(";
	// рекурсивного заключаем выражения в скобки 
	// от i до arr[i][j]
	print(i, *((arr + i * n) + j), n,
		arr, name);
	cout << "*";
	// тоже самое только от arr[i][j] + 1 до j.
	print(*((arr + i * n) + j) + 1, j, n,
		arr, name);
	cout << ")";
}

// Матрица Ai имеет размерность p [i-1] умножить на p [i] для i = 1..n.
void matrix(vector<int> p, int n)
{
	//добавляем одну лишнюю строку и столбец 
	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}
	// arr2[i][j] сохраняет оптимальную точку останова от i до j
	int** arr2 = new int* [n];
	for (int i = 0; i < n; i++) {
		arr2[i] = new int[n];
	}
	/* arr[i,j] = Минимальное количество скалярных умножений, необходимых для вычисления матрицы A [i] A [i + 1] */

	// при умножении одной матрицы значение перемножений равно 0
	for (int i = 1; i < n; i++)
		arr[i][i] = 0;

	// L это размер нашей цепочки матриц
	for (int Length = 2; Length < n; Length++)
	{
		for (int i = 1; i < n - Length + 1; i++)
		{
			int j = i + Length - 1;
			arr[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++)
			{
				int q = arr[i][k] + arr[k + 1][j]
					+ p[i - 1] * p[k] * p[j];
				if (q < arr[i][j])
				{
					arr[i][j] = q;

					// Каждая квадратная скобка[i, j] = k показывает где разделить значение arr для минимального значения умножений матрицы
					arr2[i][j] = k;
				}
			}
		}
	}
	//переводим двумерный массив в одномерный
	int* mass_odnom = new int[n * n];
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mass_odnom[k] = arr2[i][j];
			k++;
		}
	}
	//первая матрица печатается как "А" вторая как "B" и тд.
	char name = 'A';
	cout << "Расстановка скобок : ";
	print(1, n - 1, n, mass_odnom, name);
	cout << "\nМинимальное значение при перемножении = " << arr[1][n - 1];
}
void Clear_String(char* stringPtr, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		stringPtr[i] = 0;
	}
}
int main()
{
	setlocale(LC_ALL, "RU");
	int t = 0;
	int p;
	vector<int>MyVector; //создаем вектор для значений из файла
	ifstream file("text.txt");
	while (!file.eof()) //заполняем вектор значениями из файла
	{
		file >> p;
		MyVector.push_back(p);
	}
	file.close();
	int size = MyVector[0]; //в size передаем первую строчку из файла
	MyVector.erase(MyVector.begin()); //удаляем количество матриц из вектора
	matrix(MyVector, size + 1); //передаем вектор и количество матриц в функцию
	cout << endl;
	return 0;
}