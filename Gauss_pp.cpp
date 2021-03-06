#include <iostream>
#include <vector>
#include <fstream>
#include "Fractional.h"
using namespace std;



void Gauss_pp(vector<vector<Fractional>>& matrix, int n, fstream& out_file)
{

	int counter = 0;

	for (int k = 1; k <= n - 1; k++)
	{
		out_file << "Etapa " << k << endl;

		Fractional piv = matrix[k][k];
		int lin = k;


		Fractional piv_value = matrix[k][k];
		int piv_col = k;
		int piv_lin = k;


		for (int i = k + 1; i <= n; i++)
		{
			Fractional abs_value_data = matrix[i][k];

			if (abs_value_data < 0)
			{
				abs_value_data = abs_value_data * (-1);
			}


			if (piv < abs_value_data) // abs
			{
				piv = abs_value_data; // abs
				lin = i;

				piv_value = matrix[i][k];
				piv_col = k;
				piv_lin = i;
			}
		}


		if (piv == 0)
		{
			out_file << "Sistemul nu are solutie unica" << endl;
			out_file << endl;
			return;
		}

		out_file << "Pivot :" << piv_value << "  Linia : " << piv_lin << "  Coloana :" << piv_col << endl;


		if (lin != k)
		{
			out_file << "Linii permutate :" << lin << " <-> " << k << endl;
			for (int j = k; j <= n + 1; j++)
			{
				swap(matrix[k][j], matrix[lin][j]);
			}
			counter++;
		}

		for (int i = k + 1; i <= n; i++)
		{
			matrix[i][k] = matrix[i][k] / matrix[k][k];
			for (int j = k + 1; j <= n + 1; j++)
			{
				matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j];
			}
		}


	}

	if (matrix[n][n] == 0)
	{
		out_file << "Sistemul nu are solutie unica" << endl;
		out_file << endl;
		return;
	}

	out_file << "Numarul de linii permutate : " << counter << endl;

	matrix[n][n + 1] = matrix[n][n + 1] / matrix[n][n];

	for (int i = n - 1; i >= 1; i--)
	{
		Fractional s;
		for (int j = i + 1; j <= n; j++)
		{
			s = s + (matrix[i][j] * matrix[j][n + 1]);
		}
		matrix[i][n + 1] = (matrix[i][n + 1] - s) / matrix[i][i];
	}

	for (int i = 1; i <= n; i++)
	{
		out_file << "X[" << i << "] = " << matrix[i][n + 1] << endl;
	}
	out_file << endl;

}


int main()
{

	fstream in_file, out_file;
	in_file.open("input.txt", ios::in);
	out_file.open("output_Gauss_pp.txt", ios::out | ios::trunc);

	int cases = 1;

	while (cases <= 3)
	{
		// reading the input from file 

		int n;
		in_file >> n;
		vector<vector<Fractional>> matrix(n + 1, vector<Fractional>(n + 2));

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n + 1; j++)
			{
				in_file >> matrix[i][j];
			}
		}

		out_file << "Sistem: " << cases << endl;

		// solving the given system

		Gauss_pp(matrix, n, out_file);

		cases++;
	}

	in_file.close();
	out_file.close();

	return 0;
}