//
//  PSNR.cpp
//  calculate the PSNR of am image
//
//  created by Yi Zheng on 9/9/15.
//  version 3.0
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 3;
	const int height = 512;
	const int width = 512;

	// Allocate image data array
	unsigned char Imagedata_denoise[height][width][bytesPerPixel];
	unsigned char Imagedata_noiseless[height][width][bytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata_denoise, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(argv[2], "rb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fread(Imagedata_noiseless, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int i, j, k;
	int temp;
	double mse, psnr;
	mse = 0;
	for (k = 0; k<bytesPerPixel; k++)
	{
		for (i = 0; i<height; i++)
		{
			for (j = 0; j<width; j++)
			{
				temp = abs((int)Imagedata_denoise[i][j][k] - (int)Imagedata_noiseless[i][j][k]);
				mse = mse + temp * temp;
			}
		}
	}
	mse = mse / (height*width*bytesPerPixel);
	psnr = 10 * log10(255 * 255 / mse);
	cout << "The PSNR Value is " << psnr << endl;
	cin.get();
	return 0;
}
