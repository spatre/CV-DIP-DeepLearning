// This sample code reads in image data from a RAW image file and
// writes it into another file

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
	const int height = 512;
	const int width = 512;
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

	int i, j,x,y;
	int n = 4;
	//int** init = initialArray(n,n);
	//int** ones = onesArray(n, n);
	//int** twos = Mult(ones, 2, n, n);
	//int** threes= Mult(ones, 3, n, n);
	//int** add = matrixAdd(ones, twos,n,n);

	float** T = thresholdMatrix(n);

	//	int** bae = bayerMatrix(n);
	/*for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << T[i][j] << " ";
		}
		cout << endl;
	}*/


	for (i = 0; i < height;i=i+n)
	{
		for (j = 0; j < width;j=j+n)
		{
			for (x = 0; x < n; x++)
			{
				for (y = 0; y < n; y++)
				{

					if (Imagedata[x + i][y + j][0] > 255 * (T[x%n][y%n]))
					{
						Imagedata[x + i][y + j][0] = 255;
					}
					else
					{
						Imagedata[i + x][j + y][0] = 0;
					}
				}
			}
			
		}

	}

	//cin.get();



	

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
	cout << "Cannot open file: " << argv[2] << endl;
	exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);
	
	return 0;
}