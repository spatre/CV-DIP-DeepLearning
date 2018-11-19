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


	//unsigned char Imagedatafinal[height][width][bytesPerPixel];
	int i, j, k, pixel;
	float intensity[3][256] = { 0 };




	// Write image data (filename specified by second argument) from image data matrix

	int counter = 467;
	int color = 0;
	for (k = 0; k < bytesPerPixel; k++)//loop for RGB
	{
		int flag[height][width] = { 0 };

		for (pixel = 0; pixel < 256; pixel++)// loop for pixel intensity
		{
			for (i = 0; i < height; i++) // loop for row traversal
			{
				for (j = 0; j < width; j++) // loop for column traversal
				{
					if ((int)Imagedata[i][j][k] == pixel && flag[i][j] == 0)
					{
						Imagedata[i][j][k] = color;
						flag[i][j] = 1;
						if (counter == 0)
						{
							color += 1;
							counter = 467;
						}
						else
						{
							counter -= 1;
						}
					}



				}

			}

		}
	}
	for (k = 0; k<bytesPerPixel; k++)
	{
		for (i = 0; i<height; i++)
		{
			for (j = 0; j<width; j++)
			{
				for (pixel = 0; pixel<256; pixel++)
				{
					if (Imagedata[i][j][k] == pixel)
					{
						intensity[k][pixel] += 1;
					}
				}
			}
		}
	}
	//cout << intensity[0][2]<<endl;

	for (pixel = 0; pixel < 256; pixel++)
	{
		intensity[0][pixel] = intensity[0][pixel] / (120000);
		intensity[1][pixel] = intensity[1][pixel] / (120000);
		intensity[2][pixel] = intensity[2][pixel] / (120000);
		//cout << intensity[0][pixel];
		if (pixel > 0)
		{
			intensity[0][pixel] = intensity[0][pixel] + intensity[0][pixel - 1];
			intensity[1][pixel] = intensity[1][pixel] + intensity[1][pixel - 1];
			intensity[2][pixel] = intensity[2][pixel] + intensity[2][pixel - 1];
			
		}
	}
	int contrast = 255;
	for (pixel  = 0; pixel < 256; pixel++)
	{
		intensity[0][pixel] = (int)(intensity[0][pixel] * contrast);
		intensity[1][pixel] = (int)(intensity[1][pixel] * contrast);
		intensity[2][pixel] = (int)(intensity[2][pixel] * contrast);
		//cout << intensity[0][pixel] << endl;
	}


	/*
	for (pixel = 0; pixel<256; pixel++)
	{
		cout << intensity[0][pixel] << ", " << intensity[1][pixel] << ", " << intensity[2][pixel] << endl;
	}
	cin.get();
*/
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);


	return 0;
}
