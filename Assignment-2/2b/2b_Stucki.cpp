#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "myHeader.h"

using namespace std;
double Imagedata_tmp[512][512][1];
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
	const int diffuser = 3;// 2-Jarvis,Judice and Ninke matrix, 3-Stucki matrix
	
	int i, j, a, b, c, d;
	int div = divider(diffuser);
	
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				Imagedata_tmp[i][j][0] = 255.0 - (double)Imagedata[i][j][0];
			}
		}
	
	unsigned char Imagedata_Out[height][width][bytesPerPixel];

	double error;
	for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				int** mat_diffused = diffusionMatrix(diffuser);//Creating a diffusion matrix
															   // getting the multiplier for the matrix
															   // multiplying the diffusion matrix by the multiplier

				if (Imagedata_tmp[i][j][0] >= 127)
				{
					error = Imagedata_tmp[i][j][0] - 255;
					Imagedata_Out[i][j][0] = (unsigned char)0;

				}
				else
				{
					error = Imagedata_tmp[i][j][0];
					Imagedata_Out[i][j][0] = (unsigned char)255;

				}
				if (j + 1<width)
				{
					Imagedata_tmp[i][j + 1][0] = Imagedata_tmp[i][j + 1][0] + error * (mat_diffused[2][3]) / div; 
				}
				if (j + 2< width)
				{
					Imagedata_tmp[i][j + 2][0] = Imagedata_tmp[i][j + 2][0] + error * (mat_diffused[2][4]) / div;
				}
				if (j - 2 >= 0 && i + 1< height)
				{
					Imagedata_tmp[i + 1][j - 2][0] = Imagedata_tmp[i + 1][j - 2][0] + error * (mat_diffused[3][0]) / div;
				}
				if (j - 1 >= 0 && i + 1< height)
				{
					Imagedata_tmp[i + 1][j - 1][0] = Imagedata_tmp[i + 1][j - 1][0] + error * (mat_diffused[3][1]) / div;
				}
				if (i + 1<height)
				{
					Imagedata_tmp[i + 1][j][0] = Imagedata_tmp[i + 1][j][0] + error * (mat_diffused[3][2]) / div;
				}
				if (j + 1< width && i + 1< height)
				{
					Imagedata_tmp[i + 1][j + 1][0] = Imagedata_tmp[i + 1][j + 1][0] + error * (mat_diffused[3][3]) / div;
				}
				if (j + 2< width && i + 1< height)
				{
					Imagedata_tmp[i + 1][j + 2][0] = Imagedata_tmp[i + 1][j + 2][0] + error * (mat_diffused[3][4]) / div;
				}
				if (j - 2 >= 0 && i + 2< height)
				{
					Imagedata_tmp[i + 2][j - 2][0] = Imagedata_tmp[i + 2][j - 2][0] + error * (mat_diffused[4][0]) / div;
				}
				if (j - 1 >= 0 && i + 2<height)
				{
					Imagedata_tmp[i + 2][j - 1][0] = Imagedata_tmp[i + 2][j - 1][0] + error * (mat_diffused[4][1]) / div;
				}
				if (i + 2< height)
				{
					Imagedata_tmp[i + 2][j][0] = Imagedata_tmp[i + 2][j][0] + error * (mat_diffused[4][2]) / div;
				}
				if (j + 1< width && i + 2< height)
				{
					Imagedata_tmp[i + 2][j + 1][0] = Imagedata_tmp[i + 2][j + 1][0] + error * (mat_diffused[4][3]) / div;
				}
				if (j + 2< width && i + 2< height)
				{
					Imagedata_tmp[i + 2][j + 2][0] = Imagedata_tmp[i + 2][j + 2][0] + error * (mat_diffused[4][4]) / div;
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
	fwrite(Imagedata_Out, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	return 0;
}