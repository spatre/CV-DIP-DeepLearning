// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>


using namespace std;

void sort(int arr[], int val)
{
	int i, j;
	int n = val;
	//cout << n;
	int bubble = 0;
	for (i = 0; i < (n - 1); i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1]) 
			{
				bubble = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = bubble;
			}
		}
	}
}


int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 3;
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


	//unsigned char Imagedatafinal[height][width][bytesPerPixel];
	int i, j, k, pixel;
	//int intensity[3][256] = { 0 };
	const int N = 3;
	const int n = (N-1)/2;
	const int disp = 2 * n;
	const int wsize = N * N;
	unsigned char Imagedata_Big[height + disp][width + disp][bytesPerPixel] = { 0 };

	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = n; i < height+n; i++)
		{
			for (j = n; j < width+n; j++)
			{
				Imagedata_Big[i][j][k] = Imagedata[i-n][j-n][k];
				
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
				Imagedata_Big[i][j][k] = Imagedata_Big[height+n-1][j][k];
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

	
	int a, b, c, d;
	for (k = 0; k < bytesPerPixel; k++)
	{
		for (a = n; a < height + n; a++)
		{
			for (b = n; b < width + n; b++)
			{
				int bubble[wsize] = { 0 };
				int x = 0;
				for (c = a - n; c <= a + n; c++)
				{
					for (d = b - n; d <= b + n; d++)
					{
						
						bubble[x] = Imagedata_Big[c][d][k];
						x++;
						
					}
				}
				sort(bubble, wsize);
				Imagedata_Big[a][b][k] = bubble[(wsize/2)];

			
				
				
			}
		}
	}

	for (k = 0; k < bytesPerPixel; k++)
	{
		for (a = n; a < height + n; a++)
		{
			for (b = n; b < width + n; b++)
			{
				int window[wsize] = { 0 };
				int y = 0;
				int mean = 0;
				int sum = 0;
				for (c = a - n; c <= a + n; c++)
				{
					for (d = b - n; d <= b + n; d++)
					{

						window[y] = Imagedata_Big[c][d][k];
						y++;

					}
				}
				for (i = 0; i < wsize; i++)
				{
					sum = sum + window[i];
				}
				mean = sum / wsize;
				Imagedata_Big[a][b][k] = mean;




			}
		}
	}





	
	unsigned char Imagedata_denoise[height][width][bytesPerPixel];

	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = n; i < height + n; i++)
		{
			for (j = n; j < width + n; j++)
			{
				Imagedata_denoise[i - n][j - n][k] = Imagedata_Big[i][j][k];
			}
		}

	}
	

	

	
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_denoise, sizeof(unsigned char), (height+disp)*(width+disp)*bytesPerPixel, file);
	fclose(file);

	return 0;
}
