// This sample code reads in image data from a RAW image file and
// writes it into another file

#include <stdio.h>
#include <iostream>
#include <stdlib.h>


using namespace std;

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

	int i, j;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((Imagedata[i][j][0] >= 0) && (Imagedata[i][j][0] < 127))
			{
				Imagedata[i][j][0] = 0;
			}
			else if (Imagedata[i][j][0] >= 127 && Imagedata[i][j][0] < 256)
			{
				Imagedata[i][j][0] = 255;
			}

		}
	}

	
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	return 0;
}
