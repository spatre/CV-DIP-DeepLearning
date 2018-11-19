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
	int n1 = 4;
	int n2 = 8;
	int indicator1[height][width];
	int indicator2[height][width];
	//int** init = initialArray(n,n);
	//int** ones = onesArray(n, n);
	//int** twos = Mult(ones, 2, n, n);
	//int** threes= Mult(ones, 3, n, n);
	//int** add = matrixAdd(ones, twos,n,n);

	float** T1 = thresholdMatrix(n1);
	float** T2 = thresholdMatrix(n2);
	unsigned char Imagedata_graylevel[height][width][bytesPerPixel];


	for (i = 0; i < height;i=i+n1)
	{
		for (j = 0; j < width;j=j+n1)
		{
			for (x = 0; x < n1; x++)
			{
				for (y = 0; y < n1; y++)
				{

					if (Imagedata[x + i][y + j][0] > 255 * (T1[x%n1][y%n1]))
					{
						
						indicator1[x + i][y + j] = 0;
					}
					else
					{
						
						indicator1[x + i][y + j] = 1;
					}
				}
			}
			
		}

	}

	for (i = 0; i < height; i = i + n2)
	{
		for (j = 0; j < width; j = j + n2)
		{
			for (x = 0; x < n2; x++)
			{
				for (y = 0; y < n2; y++)
				{

					if (Imagedata[x + i][y + j][0] > 255 * (T2[x%n2][y%n2]))
					{
						
						indicator2[x + i][y + j] = 0;
					}
					else
					{
						
						indicator2[x + i][y + j] = 1;
					}
				}
			}

		}

	}


	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (indicator1[i][j] == 1)
			{
				if (indicator2[i][j] == 1)
				{
					Imagedata_graylevel[i][j][0] = 0;
				}
				else
				{
					Imagedata_graylevel[i][j][0] = 85;
				}
			}
			else
			{
				if (indicator2[i][j] == 1)
				{
					Imagedata_graylevel[i][j][0] = 170;
				}
				else
				{
					Imagedata_graylevel[i][j][0] = 255;
				}
			}
		}
	}

	
	/*for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			cout << (int)Imagedata_graylevel[i][j][0] << " ";

		}
		cout << endl;
	}

	cin.get();*/

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
	cout << "Cannot open file: " << argv[2] << endl;
	exit(1);
	}
	fwrite(Imagedata_graylevel, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);
	
	return 0;
}