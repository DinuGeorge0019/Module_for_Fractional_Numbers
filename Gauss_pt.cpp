#include <iostream>
#include <vector>
#include <fstream>
#include "Fractional.h"
using namespace std;



void Gauss_pt(vector<vector<Fractional>>& matrix, int n, fstream& out_file)
{

	const Fractional E(1, pow(10, 9));

	int npc = 0;

	vector<pair<int, int>> c;

	for (int k = 1; k <= n - 1; k++)
	{
		Fractional piv = matrix[k][k];
		int lin = k;
		int col = k;

		for (int i = k; i <= n; i++)
		{
			for (int j = k; j <= n; j++)
			{

				Fractional abs_value_data = matrix[i][j];

				if (abs_value_data < 0)
				{
					abs_value_data = abs_value_data * (-1);
				}

				if (piv < abs_value_data)
				{
					piv = abs_value_data;
					lin = i;
					col = j;
				}
			}
		}

		if (piv <= E)
		{
			out_file << "Sistemul nu are solutie unica" << endl;
			out_file << endl;
			return;
		}

		if (lin != k)
		{
			for (int j = k; j <= n + 1; j++)
			{
				swap(matrix[k][j], matrix[lin][j]);
			}
		}

		if (col != k)
		{
			npc++;
			c.push_back({ k, col });
			for (int i = 1; i <= n; i++)
			{
				swap(matrix[i][k], matrix[i][col]);
			}

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

	Fractional abs_value_data = matrix[n][n];

	if (abs_value_data < 0)
	{
		abs_value_data = abs_value_data * (-1);
	}

	if (abs_value_data <= E)
	{
		out_file << "Sistemul nu are solutie unica" << endl;
		out_file << endl;
		return;
	}

	matrix[n][n + 1] = matrix[n][n + 1] / matrix[n][n];

	for (int i = n - 1; i >= 1; i--)
	{
		Fractional s;
		for (int j = i + 1; j <= n; j++)
		{
			s = s + matrix[i][j] * matrix[j][n + 1];
		}
		matrix[i][n + 1] = (matrix[i][n + 1] - s) / matrix[i][i];
	}

	if (npc != 0)
	{
		for (int i = npc-1; i >= 0; i--)
		{
			swap(matrix[c[i].first][n+1], matrix[c[i].second][n+1]);
		}
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
	out_file.open("output_Gauss_pt.txt", ios::out | ios::trunc);


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

		Gauss_pt(matrix, n, out_file);

		cases++;
	}

	in_file.close();
	out_file.close();

	return 0;
}