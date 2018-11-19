#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <limits>
#include "Header.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	const int BytesPerPixel = 1;
	const int length = 480;
	const int breadth = 640;


	// Allocate image data array
	unsigned char* Imagedata1D = initialize1DArray(length*breadth*BytesPerPixel);

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb")))
	{
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata1D, sizeof(unsigned char), length*breadth*BytesPerPixel, file);
	fclose(file);

	//PROCESSING
	unsigned char** Imagedata3D = convertTo3D(Imagedata1D, length, breadth);



	unsigned char** updatedImage = initializeSingleChannelImage(length, breadth);

	const int n = 30;
	int countStars[n] = { 0 };



	for (int r = 0; r < length; r++)
	{
		for (int c = 0; c < breadth; c++)
		{
			if (Imagedata3D[r][c] <= 127)
			{
				Imagedata3D[r][c] = 0;
			}

			else
			{
				Imagedata3D[r][c] = 1;
			}
		}

	}




	for (int numIterations = 0; numIterations<n; numIterations++)
	{

		unsigned char** M_Matrix = returnM_Matrix(Imagedata3D, length, breadth);
		updatedImage = returnSkeletonImage(updatedImage, length, breadth, M_Matrix, Imagedata3D);
		Imagedata3D = updatedImage;
		



	}

	
	for (int i = 0; i<length; i++)
	{

		for (int j = 0; j<breadth; j++)
		{
			if (Imagedata3D[i][j] == 1) {

				Imagedata3D[i][j] = 255;
			}
		}
	}
	unsigned char* returnImage = convertTo1D(Imagedata3D, length, breadth);
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(returnImage, sizeof(unsigned char), length*breadth*BytesPerPixel, file);
	fclose(file);
	cin.get();
	return 0;
}


