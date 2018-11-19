#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "myHeader.h"

using namespace std;
unsigned char Imagedata_Big[1400][1800][3] = { 0 };
int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 3;
	const int height = 640;
	const int width = 480;
	const int newHeight = 1400;
	const int newWidth = 1800;
	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Allocate image data array
	unsigned char Imagedata_left[height][width][bytesPerPixel];
	unsigned char Imagedata_right[height][width][bytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata_left, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(argv[2], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata_Big, sizeof(unsigned char), newHeight*newWidth*bytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(argv[3], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata_right, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////


	int i, j, k;
	long double M1_left[1][3] = { 0.501060937,-0.00556030908,-142.795698 };
	long double M2_left[1][3] = { -0.171975543 ,0.715637288 ,-75.0202132 };
	long double M3_left[1][3] = { -0.000563082599 ,0.0000119012944  ,1.15948872 };
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < newHeight; i++)
		{
			for (j = 0; j < newWidth; j++)
			{
				double X, Y;
				X = (M1_left[0][0] * i + M1_left[0][1] * j + M1_left[0][2] * 1) / (M3_left[0][0] * i + M3_left[0][1] * j + M3_left[0][2] * 1);
				Y = (M2_left[0][0] * i + M2_left[0][1] * j + M2_left[0][2] * 1) / (M3_left[0][0] * i + M3_left[0][1] * j + M3_left[0][2] * 1);

				if (X > 0 && X < 479 && Y > 0 && Y < 639)
				{
					Imagedata_Big[j][i][k] = Imagedata_left[int(Y)][int(X)][k];
				}
			}
		}
	}

	long double M1_right[1][3] = { 1.18871559,0.00825060797,-1082.84654 };
	long double M2_right[1][3] = { 0.202338082  ,1.09607989  ,-540.161623 };
	long double M3_right[1][3] = { 0.000673412550 ,0.0000228692652  ,0.380648028 };
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < newHeight; i++)
		{
			for (j = 0; j < newWidth; j++)
			{
				double X, Y;
				X = (M1_right[0][0] * i + M1_right[0][1] * j + M1_right[0][2] * 1) / (M3_right[0][0] * i + M3_right[0][1] * j + M3_right[0][2] * 1);
				Y = (M2_right[0][0] * i + M2_right[0][1] * j + M2_right[0][2] * 1) / (M3_right[0][0] * i + M3_right[0][1] * j + M3_right[0][2] * 1);

				if (X > 0 && X < 479 && Y > 0 && Y < 639)
				{
					Imagedata_Big[j][i][k] = Imagedata_right[int(Y)][int(X)][k];
				}
			}
		}
	}



	//for (i = 0; i < height; i++)
	//{
	//for (j = 0; j < width; j++)
	//{
	//	cout << (int)Imagedata_Out[i][j][0] << endl;

	//}
	////cout << endl;
	//}

	//cin.get();

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[4], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_Big, sizeof(unsigned char), newHeight *newWidth* bytesPerPixel, file);
	fclose(file);

	return 0;
}