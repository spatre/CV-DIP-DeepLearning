#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "myHeader.h"

using namespace std;
double Imagedata_tmp[700][700][3];
int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 3;
	const int height = 700;
	const int width = 700;
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
	const int diffuser = 1;//1-Floyd-Steinberg's matrix, 2-Jarvis,Judice and Ninke matrix, 3-Stucki matrix
	const int N = 3;// 3- FS matrix, 5- JJN and Stucki matrix.
	const int n = (N - 1) / 2;
	const int disp = 2 * n;

	unsigned char Imagedata_Out[height][width][bytesPerPixel];
	int i, j, k, a, b, c, d;
	int div = divider(diffuser);

	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				Imagedata_tmp[i][j][k] = 255.0 - (double)Imagedata[i][j][k];
			}
		}
	}

	
	double error;
	for (k = 0; k<bytesPerPixel; k++)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width ; j++)
			{
				int** mat_diffused = diffusionMatrix(diffuser);//Creating a diffusion matrix
															   // getting the multiplier for the matrix
															   // multiplying the diffusion matrix by the multiplier

				if (Imagedata_tmp[i][j][k]>=127)
				{
					error = Imagedata_tmp[i][j][k] - 255;
					Imagedata_Out[i][j][k] =(unsigned char)0;
					
				}
				else
				{
					error = Imagedata_tmp[i][j][k];
					Imagedata_Out[i][j][k] = (unsigned char)255;
					
				}
				if (j + 1<width)
				{
					Imagedata_tmp[i][j + 1][k] = Imagedata_tmp[i][j + 1][k] + error * (mat_diffused[1][2] )/ div;
				}
				if (j - 1 >= 0 && i + 1<height)
				{
					Imagedata_tmp[i + 1][j - 1][k] = Imagedata_tmp[i + 1][j - 1][k] + error * (mat_diffused[2][0] )/ div;
				}
				if (i + 1<height)
				{
					Imagedata_tmp[i + 1][j][k] = Imagedata_tmp[i + 1][j][k] + error * (mat_diffused[2][1]) /div;
				}
				if (i + 1<height && j + 1<width)
				{
					Imagedata_tmp[i + 1][j + 1][k] = Imagedata_tmp[i + 1][j + 1][k] + error * (mat_diffused[2][2]) / div;
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
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_Out, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	return 0;
}