#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "myHeader.h"

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 1;
	const int height = 128;
	const int width = 128;
	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Allocate image data array
	unsigned char Imagedata[height][width][bytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int i, j, k, a, b, c, d;
	const int N = 5; // Window Size
	const int n = (N - 1) / 2; // Padding parameter
	const int disp = 2 * n;//Number of extra rows and columns to be added
	unsigned char Imagedata_Big[height + disp][width + disp][bytesPerPixel] = { 0 };
	unsigned char Imagedata_Pad[height + disp][width + disp][bytesPerPixel] = { 0 };
	unsigned char Imagedata_Out[height][width][9] = { 0 };
	unsigned char Imagedata_final[height][width][bytesPerPixel] = { 0 };
	double filterBank[5][5][9] = { 0 };
	double filter_conv[5][5][9] = { 0 };
	double E5[5] = { -1.0 / 6.0, -2.0 / 6.0, 0.0, 2.0 / 6.0, 1.0 / 6.0};
	double S5[5] = { -1.0 / 4.0, 0.0 , 2.0 / 4.0, 0.0, -1.0 / 4.0 };
	double W5[5] = { -1.0 / 6.0, 2.0 / 6.0, 0.0, -2.0 / 6.0, 1.0 / 6.0 };

	double** E5_E5 = tensor_Prod(E5, E5);
	double** E5_S5 = tensor_Prod(E5, S5);
	double** E5_W5 = tensor_Prod(E5, W5);
	double** S5_E5 = tensor_Prod(S5, E5);
	double** S5_S5 = tensor_Prod(S5, S5);
	double** S5_W5 = tensor_Prod(S5, W5);
	double** W5_E5 = tensor_Prod(W5, E5);
	double** W5_S5 = tensor_Prod(W5, S5);
	double** W5_W5 = tensor_Prod(W5, W5);


	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][0] = E5_E5[i][j];
		}
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][1] = E5_S5[i][j];
		}
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][2] = E5_W5[i][j];
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][3] = S5_E5[i][j];
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][4] = S5_S5[i][j];
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][5] = S5_W5[i][j];
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][6] = W5_E5[i][j];
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][7] = W5_S5[i][j];
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			filterBank[i][j][8] = W5_W5[i][j];
		}
	}

	// Image Processing code starts here
	// Padding the image
	for (i = n; i < height + n; i++)
	{
		for (j = n; j < width + n; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata[i - n][j - n][0];
		}
	}


	// Inverting the filter bank for convolution
	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				filter_conv[i][j][k] = filterBank[N-i-1][N-j-1][k];
			}
		}
	}
	for (k = 0; k < 9; k++)
	{
		for (a = n; a < height + n; a++)
		{
			for (b = n; b < width + n; b++)
			{
				double sum = 0;
				for (c = a - n; c <= a + n; c++)
				{
					for (d = b - n; d <= b + n; d++)
					{
						sum = sum + (double)Imagedata_Pad[c][d][0] * filter_conv[c%N][d%N][k];
					}
				}
				if (sum > 255.0)
				{
					Imagedata_Big[a][b][0] = (unsigned char) 255;
				}
				else
				{
					Imagedata_Big[a][b][0] = (unsigned char) sum;
				}
			}
		}
		for (i = n; i < height + n; i++)
		{
			for (j = n; j < width + n; j++)
			{
				Imagedata_Out[i - n][j - n][k] = Imagedata_Big[i][j][0];
			}
		}
	}

	// To calculate the average energy for the image to obtain the feature vector
	double featureVector[9] = { 0 };
	for (k = 0; k < 9; k++)
	{
		int val = 0;
		double energy = 0;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				val = val + (int)Imagedata_Out[i][j][k] * (int)Imagedata_Out[i][j][k];
			}
		}
		energy = (double)val / (double)(height*width);
		featureVector[k] = energy;
	}

	for (k = 0; k < 9; k++)
	{
		cout << featureVector[k] << endl;
	}
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			Imagedata_final[i][j][0] = Imagedata_Out[i][j][8];
		}
	}
	//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		cout << (int)Imagedata_Out[i][j][0] << endl;

	//	}
	//	//cout << endl;
	//}
	cin.get();

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_final, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	return 0;
}