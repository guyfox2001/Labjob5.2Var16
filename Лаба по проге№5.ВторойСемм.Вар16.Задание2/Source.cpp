#pragma comment(linker, "/STACK:10000000000")
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include "checkfile.h"
using namespace std;

double** size_mass(int n, int m) {
	double** mass = new double * [n];
	for (int i = 0; i < n; ++i) {
		mass[i] = new double[m];
	}
	return mass;
}

template <typename MatrixType>
double calc_determinant(MatrixType** matrix, int n, int m) {
	if (n != m) return -1;
	if (n == 1 && m == 1) return matrix[0][0];
	if (n ==2 && m == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	MatrixType** minor;
	MatrixType result = 0;
	for (int k = 0; k < n; ++k) {
		minor = size_mass(n - 1, m - 1); 
		for (int mi=0, i = 1; i < n; ++i, mi++) {
			for (int mj=0, j = 0; j < m; j++) {
				if (j == k) continue;
				minor[mi][mj] = matrix[i][j];
				mj++;
			}
		}
		result += pow(-1, k) * matrix[0][k] * calc_determinant(minor, n - 1, m - 1);
		delete [] minor;
	}
	return result;
}

template <typename MatrixType>
void print_matrix(MatrixType** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << setw(3) << matrix[i][j] << ' ';
		}
		cout << endl;
	}
}

template <typename MatrixType>
void foutput_matrix(MatrixType** matrix, int n, int m, string filename) {
	ofstream output(filename, ios::out);
	output << n << ' ' << m << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			output << matrix[i][j] << ' ';
		}
		output << endl;
	}
}

void SW_OP(string& _FileName, double** matrix) {
	int OpWithFile= -1;
	int n, m;
	ifstream input;
	bool exit = true;
	do
	{
		cout << "Работа с файлом или рандом значений. 1. Считать с файла. 2. Зарандомить \n";
		while (OpWithFile != 1 && OpWithFile !=2)
		{
			cin >> OpWithFile;
			if (OpWithFile != 1 && OpWithFile != 2) {
				cerr << "Ошибка! Повторите ввод\n";
			}
		}
		switch (OpWithFile)
		{
		case 1:
			cout << "Введите имя файла\n";
			do
			{
				getline(cin, _FileName);
			} while (_FileName.empty());
			_FileName = check_mask(_FileName);
			if (check_file(_FileName)) {
				if (!check_empty(_FileName)) {
					input.open(_FileName, ios::in);
					input >> n >> m;
					matrix = size_mass(n, m);
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							input >> matrix[i][j];
						}
					}
					print_matrix(matrix, n, m);
					cout << endl << fixed << calc_determinant(matrix, n, m) << endl;
					
				}
				else {
					cerr << "Файл пуст\n";
				}
			}
			delete[]matrix;
			exit = true;
			break;
		case 2:
			cout << "Введите размерность матрицы\n";
			cin >> n >> m;
			srand(NULL);
			matrix = size_mass(n, m);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					matrix[i][j] = rand() % 100 + 1;
				}
			}
			print_matrix(matrix, n, m);
			cout << endl << fixed << calc_determinant(matrix, n, m) << endl;
			cout << "Запись в файл lastcalc.pbs\n";
			foutput_matrix(matrix, n, m, "lastcalc.pbs");
			exit = true;
			delete[] matrix;
			break;
		default:

			break;
		}
	} while (!exit);
}

int main() {
	setlocale(LC_ALL, "Rus");
	int flag;
	string _FileName;
	double** matrix = NULL;
	do {
		SW_OP(_FileName, matrix);
		cout << "Продолжить? 1.Yes 2.No\n";
		cin >> flag;
		if (flag == 2) break;
	} while (true);
}