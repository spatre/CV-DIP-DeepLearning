#pragma once
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

int** initialArray(int row, int column);

int** Mult(int** matrix, int val, int row, int column);

double** Mult_double(int** matrix, double val, int row, int column);

float** Mult_float(float** matrix, float val, int row, int column);

double** divide_double(int** matrix, int val, int row, int column);

float** divide_float(int** matrix, int val, int row, int column);

int** onesArray(int row, int column);

int** matrixAdd(int** mat1, int** mat2, int row, int column);

int** bayerMatrix(int x);

float** thresholdMatrix(int y);

float** initialThreshold(int row, int column);

int** diffusionMatrix(int z);

int divider(int a);

double** initialDArray(int row, int column);

float** initialFArray(int row, int column);

int distance(double a, double b, double c, double space[][3]);

int** initialArray(int row, int column)
{
	int** mat = new int*[row];
	for (int i = 0; i < row; i++)
	{
		mat[i] = new int[column];
		for (int j = 0; j < column; j++)
		{
			mat[i][j] = 0;
		}
	}
	return mat;
}

int** onesArray(int row, int column)
{
	int** mat = initialArray(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			mat[i][j] = 1;
		}
	}
	return mat;
}

int** Mult(int** matrix, int val, int row, int column)
{
	int** mult = initialArray(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			mult[i][j] = val * matrix[i][j];
		}
	}
	return mult;

}

double** Mult_double(int** matrix, double val, int row, int column)
{
	double** mult_d = initialDArray(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			mult_d[i][j] = val * matrix[i][j];
		}
	}
	return mult_d;

}

float** Mult_float(float** matrix, float val, int row, int column)
{
	float** mult_f = initialFArray(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			mult_f[i][j] = val * matrix[i][j];
		}
	}
	return mult_f;
}

double** divide_double(int** matrix, int val, int row, int column)
{
	double** div_d = initialDArray(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			div_d[i][j] = matrix[i][j]/val;
		}
	}
	return div_d;

}

float** divide_float(int** matrix, int val, int row, int column)
{
	float** div_f = initialFArray(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			div_f[i][j] = matrix[i][j] / val;
		}
	}
	return div_f;

}


int** matrixAdd(int** mat1, int** mat2, int row, int column)
{
	int** adder = initialArray(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			adder[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
	return adder;

}

int** bayerMatrix(int x)
{
	int** I_mat = initialArray(x, x);
	if (x == 2)
	{

		I_mat[0][0] = 1;
		I_mat[0][1] = 2;
		I_mat[1][0] = 3;
		I_mat[1][1] = 0;

	}
	else
	{
		int** I_dummy = initialArray(x / 2, x / 2);
		//int** I_mat = initialArray(x,x);
		int** temp_mat = initialArray(x / 2, x / 2);
		int** ones = onesArray(x / 2, x / 2);
		int** twos = Mult(ones, 2, x / 2, x / 2);
		int** threes = Mult(ones, 3, x / 2, x / 2);
		I_dummy = bayerMatrix(x / 2);

		temp_mat = matrixAdd(Mult(I_dummy, 4, x / 2, x / 2), ones, x / 2, x / 2);
		for (int i = 0; i<x / 2; i++)
		{
			for (int j = 0; j<x / 2; j++)
			{
				I_mat[i][j] = temp_mat[i][j];
			}

		}

		temp_mat = matrixAdd(Mult(I_dummy, 4, x / 2, x / 2), twos, x / 2, x / 2);
		for (int i = 0; i<x / 2; i++)
		{
			for (int j = x / 2; j<x; j++)
			{
				I_mat[i][j] = temp_mat[i][j - x / 2];
			}

		}

		temp_mat = matrixAdd(Mult(I_dummy, 4, x / 2, x / 2), threes, x / 2, x / 2);
		for (int i = x / 2; i<x; i++)
		{
			for (int j = 0; j<x / 2; j++)
			{
				I_mat[i][j] = temp_mat[i - x / 2][j];
			}

		}

		temp_mat = Mult(I_dummy, 4, x / 2, x / 2);
		for (int i = x / 2; i<x; i++)
		{
			for (int j = x / 2; j<x; j++)
			{
				I_mat[i][j] = temp_mat[i - x / 2][j - x / 2];
			}
		}


	}
	return I_mat;


}
float** initialThreshold(int row, int column)
{
	float** thre = new float*[row];
	for (int i = 0; i < row; i++)
	{
		thre[i] = new float[column];
		for (int j = 0; j < column; j++)
		{
			thre[i][j] = 0.0f;
		}
	}
	return thre;
}
float** thresholdMatrix(int y)
{
	int** bayer = bayerMatrix(y);
	float** threshold = initialThreshold(y, y);
	int N = y * y;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < y; j++)
		{
			threshold[i][j] = (bayer[i][j] + 0.5) / N;
		}
	}

	return threshold;
}


int** diffusionMatrix(int z)
{
	if (z == 1)
	{
		int** FS = initialArray(3, 3);
		FS[0][0] = 0;
		FS[0][1] = 0;
		FS[0][2] = 0;
		FS[1][0] = 0;
		FS[1][1] = 0;
		FS[1][2] = 7;
		FS[2][0] = 3;
		FS[2][1] = 5;
		FS[2][2] = 1;
		return FS;
	}
	else if (z == 2)
	{
		int** JJN = initialArray(5, 5);

		JJN[0][0] = 0;
		JJN[0][1] = 0;
		JJN[0][2] = 0;
		JJN[0][3] = 0;
		JJN[0][4] = 0;
		JJN[1][0] = 0;
		JJN[1][1] = 0;
		JJN[1][2] = 0;
		JJN[1][3] = 0;
		JJN[1][4] = 0;
		JJN[2][0] = 0;
		JJN[2][1] = 0;
		JJN[2][2] = 0;
		JJN[2][3] = 7;
		JJN[2][4] = 5;
		JJN[3][0] = 3;
		JJN[3][1] = 5;
		JJN[3][2] = 7;
		JJN[3][3] = 5;
		JJN[3][4] = 3;
		JJN[4][0] = 1;
		JJN[4][1] = 3;
		JJN[4][2] = 5;
		JJN[4][3] = 3;
		JJN[4][4] = 1;

		return JJN;
	}
	else if (z == 3)
	{
		int** Stucki = initialArray(5, 5);

		Stucki[0][0] = 0;
		Stucki[0][1] = 0;
		Stucki[0][2] = 0;
		Stucki[0][3] = 0;
		Stucki[0][4] = 0;
		Stucki[1][0] = 0;
		Stucki[1][1] = 0;
		Stucki[1][2] = 0;
		Stucki[1][3] = 0;
		Stucki[1][4] = 0;
		Stucki[2][0] = 0;
		Stucki[2][1] = 0;
		Stucki[2][2] = 0;
		Stucki[2][3] = 8;
		Stucki[2][4] = 4;
		Stucki[3][0] = 2;
		Stucki[3][1] = 4;
		Stucki[3][2] = 8;
		Stucki[3][3] = 4;
		Stucki[3][4] = 2;
		Stucki[4][0] = 1;
		Stucki[4][1] = 2;
		Stucki[4][2] = 4;
		Stucki[4][3] = 2;
		Stucki[4][4] = 1;

		return Stucki;
	}
}

int divider(int a)
{
	if (a == 1)
	{
		return 16;
	}
	else if (a == 2)
	{
		return 48;
	}
	else if (a == 3)
	{
		return 42;
	}
}


double** initialDArray(int row, int column)
{
	double** mat = new double*[row];
	for (int i = 0; i < row; i++)
	{
		mat[i] = new double [column];
		for (int j = 0; j < column; j++)
		{
			mat[i][j] = 0;
		}
	}
	return mat;
}

float** initialFArray(int row, int column)
{
	float** mat = new float*[row];
	for (int i = 0; i < row; i++)
	{
		mat[i] = new float[column];
		for (int j = 0; j < column; j++)
		{
			mat[i][j] = 0;
		}
	}
	return mat;
}

int distance(double a, double b, double c, double space[][3])
{
	double d1, d2, d3, d4;
	int val = 0;

	//Calculating the distance
	d1 = sqrt((a - space[0][0])*(a - space[0][0]) + (b - space[0][1])*(b - space[0][1]) + (c - space[0][2])*(c - space[0][2]));
	d2 = sqrt((a - space[1][0])*(a - space[1][0]) + (b - space[1][1])*(b - space[1][1]) + (c - space[1][2])*(c - space[1][2]));
	d3 = sqrt((a - space[2][0])*(a - space[2][0]) + (b - space[2][1])*(b - space[2][1]) + (c - space[2][2])*(c - space[2][2]));
	d4 = sqrt((a - space[3][0])*(a - space[3][0]) + (b - space[3][1])*(b - space[3][1]) + (c - space[3][2])*(c - space[3][2]));
	
	// To find the smallest distance from the CMY(x,y,z)
	if (d1 < d2 && d1 < d3 && d1 < d4)
	{
		val = 0;
	}
	if (d2 < d1 && d2 < d3 && d2 < d4)
	{
		val = 1;
	}
	if (d3 < d1 && d3< d2 && d3 < d4)
	{
		val = 2;
	}
	if (d4 < d1 && d4 < d2 && d4 < d3)
	{
		val = 3;
	}
	return val;

}
