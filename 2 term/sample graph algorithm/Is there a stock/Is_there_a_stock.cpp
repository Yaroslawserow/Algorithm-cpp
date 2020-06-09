#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
	int n;
	std::cin >> n;
	int** matrix;
	matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int j = 0; j < n; j++)
		for (int i = 0; i < n; i++)
			std::cin >> matrix[j][i];
	int i = 0, j = 0;
	while (i != n - 1 && j != n - 1)
	{
		int count = 0;
		if (matrix[j][i] == 1)
			j++;
		else
			while (matrix[j][i] != 1)
			{
				count++;
				i++;
				if (i == n)
				{
					i--;
					j -= count;
					break;
				}
			}
		j += count;
	}
	bool v = 1;
	if (i == n - 1)
	{
		for (int k = 0; k < n; k++)
			if (matrix[j][k] == 1)
				v = 0;
		for (int k = 0; k < n; k++)
			if (k != j)
				if (matrix[k][j] == 0)
					v = 0;
	}
	if (j == n - 1)
	{
		for (int k = 0; k < n; k++)
			if (k != j)
				if (matrix[k][i] == 0)
					v = 0;
		for (int k = 0; k < n; k++)
			if (k != j)
				if (matrix[i][k] == 1)
					v = 0;
	}
	for (int i = 0; i < n; i++)
		delete(matrix[i]);
	delete(matrix);
	if (v == 0)
		std::cout << "NO";
	else
		std::cout << "YES";
	/*for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
			std::cout << matrix[j][i] << ' ';
		std::cout << '\n';
	}*/
}