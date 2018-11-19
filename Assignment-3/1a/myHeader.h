#pragma once
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
double** initialDArray(int row, int column);

double** tensor_Prod(double arr1[5], double arr2[5]);

//int** convolver(unsigned char Img[483][323][1], int filter[3][3], int n, int N, int height, int width);
int** convolver(unsigned char Img[483][323][1], int filter[9], int n, int N, int height, int width);
int** convolver_Log(unsigned char Img[485][325][1], int filter[25], int n, int N, int height, int width);
float** initialFArray(int row, int column);

int minimum(int** Img, int height, int width);
int maximum(int** Img, int height, int width);
int** initialArray(int row, int column);
double distance(double fv[9], double cent[9]);
double** tensor_Prod_3D(double arr1[3], double arr2[3]);


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


double** tensor_Prod(double arr1[5],double arr2[5])
{
	double ** tensor_mat = initialDArray(5, 5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			{
				tensor_mat[i][j] = arr1[i]*arr2[j];
			}
	}
	return tensor_mat;
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

//
//int** convolver(unsigned char Img[483][323][1],int filter[3][3],int n,int N,int height, int width )
//{
//	int** Image = initialArray(height, width);
//	int a, b, c, d;
//	for (a = n; a < height + n; a++)
//	{
//		for (b = n; b < width + n; b++)
//		{
//			int sum_gx = 0;
//			for (c = a - n; c <= a + n; c++)
//			{
//				for (d = b - n; d <= b + n; d++)
//				{
//					sum_gx = sum_gx + (int)Img[c][d][0] * filter[c%N][d%N];
//				
//				}
//				
//			}
//			Image[a-n][b-n] = sum_gx;
//
//		}
//	}
//	return Image;
//}


int** convolver_Log(unsigned char Img[485][325][1], int filter[25], int n, int N, int height, int width)
{
	int** Image = initialArray(height, width);
	int a, b, c, d;
	for (a = n; a < height + n; a++)
	{
		for (b = n; b < width + n; b++)
		{
			int sum_gx = 0, window[25] = { 0 }, i = 0;;
			for (c = a - n; c <= a + n; c++)
			{
				for (d = b - n; d <= b + n; d++)
				{
					window[i] = Img[c][d][0];
					i++;
				}
				//cout << endl;
			}
			for (int k = 0; k < 25; k++)
			{
				sum_gx += window[k] * filter[k];
			}
			
			Image[a - n][b - n] = sum_gx;
			//cout << sum_gx << endl;
		}
	}
	return Image;
}


int** convolver(unsigned char Img[483][323][1],int filter[9],int n,int N,int height, int width )
{
	int** Image = initialArray(height, width);
	int a, b, c, d;
	for (a = n; a < height + n; a++)
	{
		for (b = n; b < width + n; b++)
		{
			int sum_gx = 0, window[9] = { 0 }, i = 0;;
			for (c = a - n; c <= a + n; c++)
			{
				for (d = b - n; d <= b + n; d++)
				{
					window[i] = Img[c][d][0];
					i++;
				}
				//cout << endl;
			}
			for (int k = 0; k < 9; k++)
			{
				sum_gx += window[k] * filter[k];
			}

			Image[a - n][b - n] = sum_gx;
			//cout << sum_gx << endl;
		}
	}
	return Image;
}

int minimum(int** Img, int height, int width)
{
	int min = 9999;
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Img[i][j] < min)
			{
				min = Img[i][j];
			}
		}
	}
	return min;
}


int maximum(int** Img, int height, int width)
{
	int max = -1;
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Img[i][j] > max)
			{
				max = Img[i][j];
			}
		}
	}
	return max;
}

double distance(double fv[9], double cent[9])
{
	double dist = 0.0;
	int i, j, k;

	
		for (i = 0; i < 9; i++)
		{
			dist = dist + ((fv[i] - cent[i])*(fv[i] - cent[i]));
		}

		return sqrt(dist);
	
}


double** tensor_Prod_3D(double arr1[3], double arr2[3])
{
	double ** tensor_mat = initialDArray(3, 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tensor_mat[i][j] = arr1[i] * arr2[j];
		}
	}
	return tensor_mat;
}