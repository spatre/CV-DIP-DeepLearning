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
	const int bytesPerPixel = 3;
	const int height = 481;
	const int width = 321;
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
	unsigned char Imagedata_gray[height][width][1] = { 0 };
	unsigned char Imagedata_Pad[height + disp][width + disp][1] = { 0 };
	//int Gx[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };// X gradient filter
	//int Gy[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };// Y gradient filter
	int Mask[25] = { 0,0,1,0,0,0,1,2,1,0,1,2,-16,2,1,0,1,2,1,0,0,0,1,0,0 };




														// Image Processing code starts here
														// Converting RGB to Grayscale using the Luminosity method
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			Imagedata_gray[i][j][0] = 0.21*((int)Imagedata[i][j][0]) + 0.72*((int)Imagedata[i][j][1]) + 0.07*((int)Imagedata[i][j][2]);
		}
	}

	// Padding the image
	for (i = n; i < height + n; i++)
	{
		for (j = n; j < width + n; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata_gray[i - n][j - n][0];
		}
	}


	//Copying the padded rows and columns with the Image row and column data
	for (i = 0; i < n; i++)
	{
		for (j = n; j < width + n; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata_Pad[n][j][0];
		}
	}


	for (i = height + n; i < height + disp; i++)
	{
		for (j = n; j < width + n; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata_Pad[height + n - 1][j][0];
		}
	}


	for (i = 0; i < height + disp; i++)
	{
		for (j = 0; j < n; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata_Pad[i][n][0];
		}
	}


	for (i = 0; i < height + disp; i++)
	{
		for (j = width + n; j < width + disp; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata_Pad[i][width + n - 1][0];
		}
	}

	//int Mask_conv[5][5] = { 0 };
	//int Gy_conv[3][3] = { 0 };

	// Inverting the filters Gx and Gy for convolution

	//for (i = 0; i < N; i++)
	//{
	//	for (j = 0; j < N; j++)
	//	{
	//		Gy_conv[i][j] = Gy[N - i - 1][N - j - 1];
	//		
	//	}
	//}
	int** Imagedata_Resp = convolver_Log(Imagedata_Pad, Mask, n, N, height, width);
	//int** Imagedata_Gy = convolver(Imagedata_Pad, Gy_conv, n, N, height, width);


	//int min_gx = minimum(Imagedata_Gx, height, width);
	//int max_gx = maximum(Imagedata_Gx, height, width);
	//int min_gy = minimum(Imagedata_Gy, height, width);
	//int max_gy = maximum(Imagedata_Gy, height, width);


	/*cout << min_gx << endl;
	cout << max_gx << endl;
	cout << min_gy << endl;
	cout << max_gy << endl;*/

	//unsigned char Imagedata_xgrad[height][width] = { 0 };
	//unsigned char Imagedata_ygrad[height][width] = { 0 };
	//float den1 = max_gx - min_gx;
	//float den2 = max_gy - min_gy;
	//for (i = 0; i < height; i++)
	//{
	//	for (j = 0; j < width; j++)
	//	{
	//		Imagedata_xgrad[i][j] = (unsigned char)(255.0*((float)(Imagedata_Gx[i][j] - min_gx) / den1));
	//	}
	//}

	//for (i = 0; i < height; i++)
	//{
	//	for (j = 0; j < width; j++)
	//	{
	//		Imagedata_ygrad[i][j] = (unsigned char)(255.0*((float)(Imagedata_Gy[i][j] - min_gy) / den2));
	//	}
	//}

	//int** Imagedata_G = initialArray(height, width);
	unsigned char Imagedata_final[height][width] = { 0 };
	unsigned char Imagedata_threshold[height][width] = { 0 };

	/*for (i = 0; i < height; i++)
	{
		for (j = 0; j< width; j++)
		{
			Imagedata_G[i][j] = sqrt((Imagedata_Gx[i][j]) * (Imagedata_Gx[i][j]) + (Imagedata_Gy[i][j])* (Imagedata_Gy[i][j]));
		}
	}*/
	/*int min_G = minimum(Imagedata_G, height, width);
	int max_G = maximum(Imagedata_G, height, width);
	float den3 = max_G - min_G;
	cout << min_G << endl;
	cout << max_G << endl;*/
	//for (i = 0; i < height; i++)
	//{
	//	for (j = 0; j < width; j++)
	//	{
	//		
	//		Imagedata_final[i][j] = (unsigned char)(255.0*((float)(Imagedata_G[i][j] - min_G) / den3));
	//	}
	//}
	const int dim = 154401;
	int temp;
	int Img_1D[dim] = { 0 };
	for (i = 0; i < height; i++)
	{
		for (j = 0; j< width; j++)
		{
			Img_1D[i*width + j] = Imagedata_Resp[i][j];
		}
	}
	//int count = 0;
	//Logic to Bubble Sort
	for (i = 1; i<dim; ++i)
	{
		for (j = 0; j<(dim - i); ++j)
			if (Img_1D[j]>Img_1D[j + 1])
			{
				temp = Img_1D[j];
				Img_1D[j] = Img_1D[j + 1];
				Img_1D[j + 1] = temp;
			}
	}

	//	for (i = n; i < height + n; i++)
	//	{
	//		for (j = n; j < width + n; j++)
	//		{
	//			Imagedata_Out[i - n][j - n][k] = Imagedata_Big[i][j][0];
	//		}
	//	}
	int min_G = Img_1D[0];
	int max_G = Img_1D[dim - 1];
	//cout << min_G << endl;
	//cout << max_G << endl;
	float den3 = (float)max_G - (float)min_G;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{

			Imagedata_final[i][j] = (unsigned char)(255.0*(((float)(Imagedata_Resp[i][j] - min_G)) / den3));
		//	cout << (int)Imagedata_final[i][j] << endl;
		}
	}

	//for (i = 0; i < height; i++)
	//{
	//	for (j = 0; j< width; j++)
	//	{
	//		Img_1D[i*width + j] = 255.0*(((float)(Img_1D[i*width + j] - min_G)) / den3);
	//	}
	//}
	////Thresholding
	//int perc = 90;
	//int index = (dim*perc) / 100;
	//int threshold = Img_1D[index];
	////cout << threshold << endl;

	//for (i = 0; i < height; i++)
	//{
	//	for (j = 0; j< width; j++)
	//	{
	//		if ((int)Imagedata_final[i][j] < threshold)
	//		{
	//			Imagedata_threshold[i][j] = (unsigned char)0;
	//		}
	//		else
	//		{
	//			Imagedata_threshold[i][j] = (unsigned char)255;
	//		}
	//	}
	//}
	int pixel;
	int intensity[256] = { 0 };
	float hist[256] = { 0 };
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			for (pixel = 0; pixel<256; pixel++)
			{
				if ((int)Imagedata_final[i][j] == pixel)
				{
					intensity[pixel] += 1;
				}
			}
		}
	}
	for (i = 0; i<256; i++)
	{
		
		hist[i]=((float)intensity[i])/154401.0;
		
	}
	
		
	for (i = 0; i<256; i++)
	{
		if (i > 0)
		{
			hist[i] = hist[i] + hist[i - 1];
		}
	}

	int threshold[2] = { 0 };

	for (i = 0; i<256; i++)
	{

		if (hist[i] >= 0.5)
		{
			threshold[0] = i;
			break;
		}

	}

	for (i = 0; i<256; i++)
	{

		if (hist[i] >= 0.95)
		{
			threshold[1] = i;
			break;
		}

	}

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			if ((int)Imagedata_final[i][j] < threshold[0])
			{
				Imagedata_final[i][j] = (unsigned char)64;
			}
			else if (((int)Imagedata_final[i][j] >= threshold[0]) && ((int)Imagedata_final[i][j] < threshold[1]))
			{
				Imagedata_final[i][j] = (unsigned char)128;
			}
			else if ((int)Imagedata_final[i][j] >= threshold[1])
			{
				Imagedata_final[i][j] = (unsigned char)192;
			}
		}
	}



	/*for (i = 0; i<256; i++)
	{

		cout << i << " " << hist[i] << endl;

	}*/

	//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		
	//			cout << (int)Img_1D[i*width+j] << endl;
	//		
	//	}
	//	//cout << endl;
	//}
	//cin.get();

	//// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_final, sizeof(unsigned char), height*width * 1, file);
	fclose(file);
	/*
	if (!(file = fopen(argv[3], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_ygrad, sizeof(unsigned char), height*width * 1, file);
	fclose(file);

	if (!(file = fopen(argv[4], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_final, sizeof(unsigned char), (height)*(width) * 1, file);
	fclose(file);

	if (!(file = fopen(argv[5], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_threshold, sizeof(unsigned char), (height)*(width) * 1, file);
	fclose(file);*/
	return 0;
}