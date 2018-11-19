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
	const int bytesPerPixel = 3;
	const int height = 480;
	const int width = 720;
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


	//unsigned char Imagedatafinal[height][width][bytesPerPixel];
	int i, j, k, pixel;
	int intensity[3][256] = { 0 };
	int binsize = 0;
	int sum;
	int startpt;
	int endpt;

	for (k = 0; k<bytesPerPixel; k++)
	{
		for (i = 0; i<height; i++)
		{
			for (j = 0; j<width; j++)
			{
				for (pixel = 0; pixel<256; pixel++)
				{
					if ((int)Imagedata[i][j][k] == pixel)
					{
						intensity[k][pixel] += 1;
					}
				}
			}
		}
	}
	/*
	for (pixel = 0; pixel<256; pixel++)
	{
	cout << intensity[0][pixel] << endl;
	}
	*/
	binsize = height * width / 8;


	int bin_R[8][2] = { 0 };
	int bin_G[8][2] = { 0 };
	int bin_B[8][2] = { 0 };
	int val = 0;
	//for (k = 0; k < bytesPerPixel; k++)
	//{
	sum = 0;
	startpt = 0;
	endpt = 0;
	for (pixel = 0; pixel < 256; pixel++)
	{
		if (sum < binsize)
		{
			sum = sum + intensity[0][pixel];
		}
		else
		{
			endpt = pixel - 1;
			bin_R[val][0] = startpt;
			bin_R[val][1] = endpt;
			val += 1;
			sum = 0;
			startpt = endpt + 1;
		}
	}
	bin_R[7][0] = startpt;
	bin_R[7][1] = 255;

	sum = 0;
	startpt = 0;
	endpt = 0;
	val = 0;
	for (pixel = 0; pixel < 256; pixel++)
	{
		if (sum < binsize)
		{
			sum = sum + intensity[1][pixel];
		}
		else
		{
			endpt = pixel - 1;
			bin_G[val][0] = startpt;
			bin_G[val][1] = endpt;
			val += 1;
			sum = 0;
			startpt = endpt + 1;
		}
	}
	bin_G[7][0] = startpt;
	bin_G[7][1] = 255;

	sum = 0;
	startpt = 0;
	endpt = 0;
	val = 0;
	for (pixel = 0; pixel < 256; pixel++)
	{
		if (sum < binsize)
		{
			sum = sum + intensity[2][pixel];
		}
		else
		{
			endpt = pixel - 1;
			bin_B[val][0] = startpt;
			bin_B[val][1] = endpt;
			val += 1;
			sum = 0;
			startpt = endpt + 1;
		}
	}
	bin_B[7][0] = startpt;
	bin_B[7][1] = 255;

	int x = 0;
	int sum_R;
	int Denom_R;
	int midpt_R[8] = { 0 };
	while (x < 8)
	{
		sum_R = 0;
		Denom_R = 0;
		for (i = bin_R[x][0]; i <= bin_R[x][1]; i++)
		{
			sum_R = sum_R + i * intensity[0][i];
			Denom_R = Denom_R + intensity[0][i];

		}
		midpt_R[x] = sum_R / Denom_R;
		x += 1;
	}

	int y = 0;
	int sum_G;
	int Denom_G;
	int midpt_G[8] = { 0 };
	while (y < 8)
	{
		sum_G = 0;
		Denom_G = 0;
		for (i = bin_G[y][0]; i <= bin_G[y][1]; i++)
		{
			sum_G = sum_G + i * intensity[1][i];
			Denom_G = Denom_G + intensity[1][i];

		}
		midpt_G[y] = sum_G / Denom_G;
		y += 1;
	}

	int z = 0;
	int sum_B;
	int Denom_B;
	int midpt_B[8] = { 0 };
	while (z < 8)
	{
		sum_B = 0;
		Denom_B = 0;
		for (i = bin_B[z][0]; i <= bin_B[z][1]; i++)
		{
			sum_B = sum_B + i * intensity[2][i];
			Denom_B = Denom_B + intensity[2][i];

		}
		midpt_B[z] = sum_B / Denom_B;
		z += 1;
	}
	//	cout << binsize << endl;
	/*	for (i = 0; i < 4; i++)
	{
	cout << midpt_R[i] << endl;
	}
	*/
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Imagedata[i][j][0] >= bin_R[0][0] && Imagedata[i][j][0] <= bin_R[0][1])
			{
				Imagedata[i][j][0] = midpt_R[0];
			}
			if (Imagedata[i][j][0] >= bin_R[1][0] && Imagedata[i][j][0] <= bin_R[1][1])
			{
				Imagedata[i][j][0] = midpt_R[1];
			}
			if (Imagedata[i][j][0] >= bin_R[2][0] && Imagedata[i][j][0] <= bin_R[2][1])
			{
				Imagedata[i][j][0] = midpt_R[2];
			}
			if (Imagedata[i][j][0] >= bin_R[3][0] && Imagedata[i][j][0] <= bin_R[3][1])
			{
				Imagedata[i][j][0] = midpt_R[3];
			}
			if (Imagedata[i][j][0] >= bin_R[4][0] && Imagedata[i][j][0] <= bin_R[4][1])
			{
				Imagedata[i][j][0] = midpt_R[4];
			}
			if (Imagedata[i][j][0] >= bin_R[5][0] && Imagedata[i][j][0] <= bin_R[5][1])
			{
				Imagedata[i][j][0] = midpt_R[5];
			}
			if (Imagedata[i][j][0] >= bin_R[6][0] && Imagedata[i][j][0] <= bin_R[6][1])
			{
				Imagedata[i][j][0] = midpt_R[6];
			}
			if (Imagedata[i][j][0] >= bin_R[7][0] && Imagedata[i][j][0] <= bin_R[7][1])
			{
				Imagedata[i][j][0] = midpt_R[7];
			}
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Imagedata[i][j][1] >= bin_G[0][0] && Imagedata[i][j][1] <= bin_G[0][1])
			{
				Imagedata[i][j][1] = midpt_G[0];
			}
			if (Imagedata[i][j][1] >= bin_G[1][0] && Imagedata[i][j][1] <= bin_G[1][1])
			{
				Imagedata[i][j][1] = midpt_G[1];
			}
			if (Imagedata[i][j][1] >= bin_G[2][0] && Imagedata[i][j][1] <= bin_G[2][1])
			{
				Imagedata[i][j][1] = midpt_G[2];
			}
			if (Imagedata[i][j][1] >= bin_G[3][0] && Imagedata[i][j][1] <= bin_G[3][1])
			{
				Imagedata[i][j][1] = midpt_G[3];
			}
			if (Imagedata[i][j][1] >= bin_G[4][0] && Imagedata[i][j][1] <= bin_G[4][1])
			{
				Imagedata[i][j][1] = midpt_G[4];
			}
			if (Imagedata[i][j][1] >= bin_G[5][0] && Imagedata[i][j][1] <= bin_G[5][1])
			{
				Imagedata[i][j][1] = midpt_G[5];
			}
			if (Imagedata[i][j][1] >= bin_G[6][0] && Imagedata[i][j][1] <= bin_G[6][1])
			{
				Imagedata[i][j][1] = midpt_G[6];
			}
			if (Imagedata[i][j][1] >= bin_G[7][0] && Imagedata[i][j][1] <= bin_G[7][1])
			{
				Imagedata[i][j][1] = midpt_G[7];
			}
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Imagedata[i][j][2] >= bin_B[0][0] && Imagedata[i][j][2] <= bin_B[0][1])
			{
				Imagedata[i][j][2] = midpt_B[0];
			}
			if (Imagedata[i][j][2] >= bin_B[1][0] && Imagedata[i][j][2] <= bin_B[1][1])
			{
				Imagedata[i][j][2] = midpt_B[1];
			}
			if (Imagedata[i][j][2] >= bin_B[2][0] && Imagedata[i][j][2] <= bin_B[2][1])
			{
				Imagedata[i][j][2] = midpt_B[2];
			}
			if (Imagedata[i][j][2] >= bin_B[3][0] && Imagedata[i][j][2] <= bin_B[3][1])
			{
				Imagedata[i][j][2] = midpt_B[3];
			}
			if (Imagedata[i][j][2] >= bin_B[4][0] && Imagedata[i][j][2] <= bin_B[4][1])
			{
				Imagedata[i][j][2] = midpt_B[4];
			}
			if (Imagedata[i][j][2] >= bin_B[5][0] && Imagedata[i][j][2] <= bin_B[5][1])
			{
				Imagedata[i][j][2] = midpt_B[5];
			}
			if (Imagedata[i][j][2] >= bin_B[6][0] && Imagedata[i][j][2] <= bin_B[6][1])
			{
				Imagedata[i][j][2] = midpt_B[6];
			}
			if (Imagedata[i][j][2] >= bin_B[7][0] && Imagedata[i][j][2] <= bin_B[7][1])
			{
				Imagedata[i][j][2] = midpt_B[7];
			}
		}
	}

	const int N = 11;
	const int n = (N - 1) / 2;
	const int disp = 2 * n;
	unsigned char Imagedata_Big[height + disp][width + disp][bytesPerPixel] = { 0 };

	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = n; i < height + n; i++)
		{
			for (j = n; j < width + n; j++)
			{
				Imagedata_Big[i][j][k] = Imagedata[i - n][j - n][k];

			}
		}
	}
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = n; j < width + n; j++)
			{
				Imagedata_Big[i][j][k] = Imagedata_Big[n][j][k];
			}
		}
	}
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = height + n; i < height + disp; i++)
		{
			for (j = n; j < width + n; j++)
			{
				Imagedata_Big[i][j][k] = Imagedata_Big[height + n - 1][j][k];
			}
		}
	}
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < height + disp; i++)
		{
			for (j = 0; j < n; j++)
			{
				Imagedata_Big[i][j][k] = Imagedata_Big[i][n][k];
			}
		}
	}
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < height + disp; i++)
		{
			for (j = width + n; j < width + disp; j++)
			{
				Imagedata_Big[i][j][k] = Imagedata_Big[i][width + n - 1][k];
			}
		}
	}



	int midptrgb[8][3] = { 0 };
	int a, b, c, d;
	int max, maxIndex;


	for (i = 0; i < 8; i++)
	{
		midptrgb[i][0] = midpt_R[i];
		midptrgb[i][1] = midpt_G[i];
		midptrgb[i][2] = midpt_B[i];

	}





	for (k = 0; k < bytesPerPixel; k++)
	{
		for (a = n; a < height + n; a++)
		{
			for (b = n; b < width + n; b++)
			{
				int hist[8] = { 0 };
				max = 0;
				maxIndex = 0;
				for (c = a - n; c <= a + n; c++)
				{
					for (d = b - n; d <= b + n; d++)
					{
						for (pixel = 0; pixel < 8; pixel++)
						{

							if ((int)Imagedata_Big[c][d][k] == midptrgb[pixel][k])
							{
								hist[pixel] += 1;

							}
						}
						for (pixel = 0; pixel <8; pixel++)
						{
							if (hist[pixel] > max)
							{
								max = hist[pixel];
								maxIndex = pixel;
							}
						}
					}
				}


				Imagedata_Big[a][b][k] = midptrgb[maxIndex][k];

			}
		}
	}
	unsigned char Imagedata_oil[height][width][bytesPerPixel];

	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = n; i < height + n; i++)
		{
			for (j = n; j < width + n; j++)
			{
				Imagedata_oil[i - n][j - n][k] = Imagedata_Big[i][j][k];
			}
		}

	}
	//cin.get();
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_oil, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	return 0;
}
