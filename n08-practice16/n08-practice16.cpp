#include <stdio.h>
#include <iostream>
int matrica[50][50];
int vichesl[50][50];
int mStroki[50];
int mStolbsi[50];
int kp[50];
int matSh[50][50];
int matShStr[50][50];
int matShStobls[50][50];
int d[50][2], c[50];
int g[50][2];
int k[50][2];
int m[50][2];
int a, b, e, f;
int h;
int n;
int sp = 0;
int r;
int i, j;
using namespace std;
int main()
{

	setlocale(LC_ALL, "RU");
	//ввод размера матрицы
	cout << "Введите размер матрицы" << endl;
	cin >> r;
	//присваиваем диагональным элементам "-1"
	for (i = 0; i <= (r - 1); i++)
	{
		matrica[i][i] = -1;
	}
	//вводим элементы матрицы
	cout << "Введите значения матрицы, КРОМЕ диагональных" << endl;
	for (i = 0; i <= (r - 1); i++)
	{
		for (j = 0; j <= (r - 1); j++)
		{
			if (matrica[i][j] != -1)scanf_s("%d", &matrica[i][j]);
		}
	}
	//выводим исходные данные
	cout << "Выводим введеную матрицу" << endl;
	for (i = 0; i <= (r - 1); i++)
	{
		printf("\n");
		for (j = 0; j <= (r - 1); j++)
		{
			printf("\t%d", matrica[i][j]);
		}
	}
	//присваиваем первые значения в матрицу g[][]
	for (j = 0; j <= (r - 1); j++)
	{
		g[j][0] = j + 1;
		g[j][1] = j + 1;
	}
	//присваиваем значения в матрицу vichesl
	for (i = 0; i <= (r - 1); i++)
	{
		for (j = 0; j <= (r - 1); j++)
		{
			vichesl[i][j] = matrica[i][j];
		}
	}
	//присваиваем 0 в матрицу  m[][]
	for (j = 0; j <= (r - 2); j++)
	{
		m[j][0] = 0;
		m[j][1] = 0;
	}
	//начало цикла шага задачи
	for (h = 1; h <= 5; h++)
	{
		cout << endl << "Шаг №" << h << endl;
		//вычисляем минимальный элемент строки
		for (i = 0; i <= (r - h); i++)
		{
			for (j = 0; j <= (r - h); j++)
			{
				if (vichesl[i][j] != -1) { mStroki[i] = vichesl[i][j]; break; }
			}
		}
		for (i = 0; i <= (r - h); i++)
		{
			for (j = 0; j <= (r - h); j++)
			{
				if (vichesl[i][j] != -1)
				{
					if (mStroki[i] > vichesl[i][j])mStroki[i] = vichesl[i][j];
				}
			}
		}
		//вычитаем минимальные значения строк
		for (i = 0; i <= (r - h); i++)
		{
			for (j = 0; j <= (r - h); j++)
			{
				if (vichesl[i][j] != -1)vichesl[i][j] = vichesl[i][j] - mStroki[i];
			}
		}

		cout << endl << "Вывод минимальных элементов строк:" << endl;
		for (i = 0; i <= (r - h); i++)
		{
			cout << mStroki[i] << " ";
		}

		cout << endl << "Вывод после вычета минимальных элементов строк:" << endl;
		for (i = 0; i <= (r - h); i++)
		{
			printf("\n");
			for (j = 0; j <= (r - h); j++)
			{
				printf("\t%d", vichesl[i][j]);
			}
		}

		//вычисляем минимальные элементы столбцов
		for (j = 0; j <= (r - h); j++)
		{
			for (i = 0; i <= (r - h); i++)
			{
				if (vichesl[i][j] != -1) { mStolbsi[j] = vichesl[i][j]; break; }
			}
		}

		for (j = 0; j <= (r - h); j++)
		{
			for (i = 0; i <= (r - h); i++)
			{
				if (vichesl[i][j] != -1)
				{
					if (mStolbsi[j] > vichesl[i][j])mStolbsi[j] = vichesl[i][j];
				}
			}
		}

		cout << endl << "Вывод минимальных элементов столбцов:" << endl;
		for (j = 0; j <= (r - h); j++)
		{
			cout << mStolbsi[j] << " ";
		}

		for (j = 0; j <= (r - h); j++)
		{
			for (i = 0; i <= (r - h); i++)
			{
				if (vichesl[i][j] != -1)vichesl[i][j] = vichesl[i][j] - mStolbsi[j];
			}
		}

		cout << endl << "Вывод после вычета минимальных элементов столбцов:" << endl;
		for (i = 0; i <= (r - h); i++)
		{
			printf("\n");
			for (j = 0; j <= (r - h); j++)
			{
				printf("\t%d", vichesl[i][j]);
			}
		}
		//запомним сумму в шаге
		for (i = 0; i <= (r - h); i++)
		{
			kp[h - 1] = kp[h - 1] + mStroki[i] + mStolbsi[i];
		}
		if (h == r - 1)goto e;

		//присваием -111
		for (i = 0; i <= (r - h); i++)
		{
			for (j = 0; j <= (r - h); j++)
			{
				matSh[i][j] = -111;
			}
		}

		//вычисляем минимум shtr у нулей в стобцах и строках
		for (i = 0; i <= (r - h); i++)
		{
			for (j = 0; j <= (r - h); j++)
			{
				if (vichesl[i][j] == 0)
				{
					//вычисляем shtr в строке
					for (a = 0; a <= (r - h); a++)
					{
						if (vichesl[i][a] != -1)
						{
							if (a != j)
							{
								matShStr[i][j] = vichesl[i][a]; goto A;
							}
						}
					}

				A:
					for (a = 0; a <= (r - h); a++)
					{
						if (vichesl[i][a] != -1)
						{
							if (a != j)
							{
								if (matShStr[i][j] > vichesl[i][a])matShStr[i][j] = vichesl[i][a];
							}
						}
					}

					//вычисляем shtr в стобце у нулей
					for (b = 0; b <= (r - h); b++)
					{
						if (vichesl[b][j] != -1)
						{
							if (b != i)
							{
								matShStobls[i][j] = vichesl[b][j]; goto B;
							}
						}
					}
				B:
					for (b = 0; b <= (r - h); b++)
					{
						if (vichesl[b][j] != -1)
						{
							if (b != i)
							{
								if (matShStobls[i][j] > vichesl[b][j])matShStobls[i][j] = vichesl[b][j];
							}
						}
					}
					//вычисление штрафа
					matSh[i][j] = matShStr[i][j] + matShStobls[i][j];

				}
			}
		}

		//нахождение макс штрафа
		for (i = 0; i <= (r - h); i++)
		{
			for (j = 0; j <= (r - h); j++)
			{
				if (matSh[i][j] != -111)
				{
					c[h - 1] = matSh[i][j]; d[h - 1][0] = i; d[h - 1][1] = j; goto C;
				}
			}
		}
	C:
		for (i = 0; i <= (r - h); i++)
		{
			for (j = 0; j <= (r - h); j++)
			{
				if (matSh[i][j] != 111)
				{
					if (matSh[i][j] > c[h - 1])
					{
						c[h - 1] = matSh[i][j]; d[h - 1][0] = i; d[h - 1][1] = j;
					}
				}
			}
		}
		//присваиваем матрицу к значению на шаге
		k[h - 1][0] = g[d[h - 1][0]][0];
		k[h - 1][1] = g[d[h - 1][1]][1];

		//урезание строки матрицы
		for (i = 0; i <= (r - h - 1); i++)
		{
			if (i == d[h - 1][0])
			{
				for (e = i; e <= (r - h - 1); e++)
				{
					for (f = 0; f <= (r - h); f++)
					{
						vichesl[e][f] = vichesl[e + 1][f];
					}
				}
			}
		}

		cout << endl << "Вывод после урезания строки" << endl;
		for (i = 0; i <= (r - h - 1); i++)
		{
			printf("\n");
			for (j = 0; j <= (r - h); j++)
			{
				printf("\t%d", vichesl[i][j]);
			}
		}

		//урезание столбца матрицы
		for (j = 0; j <= (r - h - 1); j++)
		{
			if (j == d[h - 1][1])
			{
				for (e = j; e <= (r - h - 1); e++)
				{
					for (f = 0; f <= (r - h - 1); f++)
					{
						vichesl[f][e] = vichesl[f][e + 1];
					}
				}
			}
		}

		cout << endl << "Вывод после урезания столбца" << endl;
		for (i = 0; i <= (r - h - 1); i++)
		{
			printf("\n");
			for (j = 0; j <= (r - h - 1); j++)
			{
				printf("\t%d", vichesl[i][j]);
			}
		}
		//присвоение матрицы g номеров строк и столбцов
		for (i = d[h - 1][0]; i <= (r - h - 1); i++)
			g[i][0] = g[i + 1][0];
		for (i = d[h - 1][1]; i <= (r - h - 1); i++)
			g[i][1] = g[i + 1][1];

		//провека есть ли противоположный элемент, если есть то присваиваем бесконечность
		for (i = 0; i <= (r - h - 1); i++)
		{
			for (j = 0; j <= (r - h - 1); j++)
			{
				if (k[h - 1][0] == g[j][1] && k[h - 1][1] == g[i][0])
				{
					vichesl[i][j] = -1; printf("\n%d", vichesl[d[h - 1][1]][d[h - 1][0]]);
				}
			}
		}
		//нахождение всех цепей(присоединение дуги в начале)
		for (i = 0; i < (h - 1); i++)
		{
			if (k[h - 1][0] == k[i][1])
			{
				m[h - 1][0] = k[i][0]; m[h - 1][1] = k[h - 1][1];
			}
		}
		//нахождение всех цепей(присоединение дуги в конце)
		for (i = 0; i < (h - 1); i++)
		{
			if (k[h - 1][1] == k[i][0])
			{
				if (m[h - 1][0] == 0)
				{
					m[h - 1][0] = k[h - 1][0]; m[h - 1][1] = k[i][1];
				}
				else m[h - 1][1] = k[i][1];
			}
		}
		//проверка можно ли присоеденить цепи если да то присоедением 
		for (i = 0; i < h - 1; i++)
		{
			if (m[i][0] != 0)
			{
				if (k[h - 1][0] == m[i][1])
				{
					m[h - 1][0] = m[i][0];
				}
			}
		}
		for (i = 0; i < h - 1; i++)
		{
			if (m[i][0] != 0)
			{
				if (k[h - 1][1] == m[i][0])
				{
					m[h - 1][1] = m[i][1];
				}
			}
		}
		//запрет цепи на шаге, присваиваем -1
		for (i = 0; i <= (r - h - 1); i++)
		{
			for (j = 0; j <= (r - h - 1); j++)
			{
				if (m[h - 1][0] == g[j][1] && m[h - 1][1] == g[i][0])
				{
					vichesl[i][j] = -1;
				}
			}
		}
	}
e:
	//присвоение двухх последних строк в матрицу k
	int l = 2;
	for (i = 0; i <= 1; i++)
	{
		for (j = 0; j <= 1; j++)
		{
			if (vichesl[i][j] == 0)
			{
				k[r - l][0] = g[i][0]; k[r - l][1] = g[j][1]; l = l - 1;
			}

		}
	}
	//расчитываем длину пути
	for (i = 0; i <= r - 1; i++)
	{
		sp = sp + matrica[k[i][0] - 1][k[i][1] - 1];
	}
	cout << "\nВывод графа пути";
	for (i = 0; i <= (r - 1); i++)
	{
		printf("\n");
		for (j = 0; j <= 1; j++)
		{

			printf("\t%d", k[i][j]);
		}

	}
	cout << endl << "\nДлина пути = ";
	printf("%d", sp);
	cout << endl << "Путь - ";
	cout << ("%d", k[3][0]);
	cout << "->";
	cout << ("%d", k[4][0]);
	cout << "->";
	cout << ("%d", k[4][1]);
	cout << "->";
	cout << ("%d", k[0][0]);
	cout << "->";
	cout << ("%d", k[1][0]);
	cout << "->";
	cout << ("%d", k[1][1]);
}
