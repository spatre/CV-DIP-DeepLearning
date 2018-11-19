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


	int i, j, k;
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				Imagedata_Big[i + 300][j + 700][k] = Imagedata[i][j][k];
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
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_Big, sizeof(unsigned char), 1400 * 1800 * bytesPerPixel, file);
	fclose(file);

	return 0;
}