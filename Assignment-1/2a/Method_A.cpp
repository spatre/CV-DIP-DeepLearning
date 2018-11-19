// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>


using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel=3;
	const int height = 300;
	const int width = 400;
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

		
	//unsigned char ImagedataNew[height][width][bytesPerPixel];
	int i, j, k;
	unsigned char ImagedataRGB[height][width][bytesPerPixel];
	float hist_R[256] = { 0 };
	float hist_G[256] = { 0 };
	float hist_B[256] = { 0 };
	int intensity = 255;
	

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			
			for (k = 0; k < 256; k++)
			{
				if ((int)Imagedata[i][j][0] == k)
				{
					hist_R[k] += 1;
					//cout << hist_R[0] << endl;
				}
				
			}
		}

	}



	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{

			for (k = 0; k < 256; k++)
			{
				if ((int)Imagedata[i][j][1] == k)
				{
					hist_G[k] += 1;
				}

			}
		}

	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{

			for (k = 0; k < 256; k++)
			{
				if ((int)Imagedata[i][j][2] == k)
				{
					hist_B[k] += 1;
				}

			}
		}

	}
	
	for (k = 0; k < 256; k++)
	{
		hist_R[k] = hist_R[k] / (120000);
		hist_G[k] = hist_G[k] / (120000);
		hist_B[k] = hist_B[k] / (120000);
		//cout << hist_R[k] << endl;
		if (k > 0)
		{
			hist_R[k] = hist_R[k] + hist_R[k - 1];
			hist_G[k] = hist_G[k] + hist_G[k - 1];
			hist_B[k] = hist_B[k] + hist_B[k - 1];
			//cout << hist_R[k] << endl;
		}
	}
	for (k = 0; k < 256; k++)
	{
		hist_R[k] = (int)(hist_R[k] * intensity);
		hist_G[k] = (int)(hist_G[k] * intensity);
		hist_B[k] = (int)(hist_B[k] * intensity);
	}


	

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{

			for (k = 0; k < 256; k++)
			{
				if ((int)Imagedata[i][j][0] == k)
				{
					ImagedataRGB[i][j][0] = (unsigned char)hist_R[k];
				}
				
				
			}
		}
	}
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{

			for (k = 0; k < 256; k++)
			{
				if ((int)Imagedata[i][j][1] == k)
				{
					ImagedataRGB[i][j][1] = (unsigned char)hist_G[k];
				}


			}
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{

			for (k = 0; k < 256; k++)
			{
				if ((int)Imagedata[i][j][2] == k)
				{
					ImagedataRGB[i][j][2] = (unsigned char)hist_B[k];
				}

			}
		}
	}
	/*
	for (k = 0; k<256; k++)
	{
		cout << hist_R[k] << ", " << hist_G[k] << ", " << hist_B[k] << endl;
	}
	cin.get();
*/


	// Write image data (filename specified by second argument) from image data matrix


	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataRGB, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);


	return 0;
}
