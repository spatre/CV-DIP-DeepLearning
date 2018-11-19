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
	const int BytesPerPixel=3;
	const int OldSize = 512;
	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	
	

	// Allocate image data array
	unsigned char Imagedata[OldSize][OldSize][BytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), OldSize*OldSize*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Implementing the Bilinear interpolation to resize the image to 650x650
	const int NewSize = 650;
	int i, j, k;
	int r, c;
	float deltar, deltac;
	int val;
	unsigned char ImagedataNew[NewSize][NewSize][BytesPerPixel];
	cout << "here";
	for (k = 0; k<BytesPerPixel; k++)
	{
		for (i = 0; i<NewSize; i++)
		{
			for (j = 0; j<NewSize; j++)
			{
				r = i * (OldSize ) / (NewSize );
				c = j * (OldSize ) / (NewSize );
				deltar = (float)i*(OldSize) / (NewSize) - r;
				deltac = (float)j*(OldSize) / (NewSize) - c;

				
				val = (1 - deltar)*(1 - deltac)*(int)Imagedata[r][c][k] + (1 - deltar)*deltac*(int)Imagedata[r][c + 1][k] + deltar * (1 - deltac)*(int)Imagedata[r + 1][c][k] + deltar * deltac*(int)Imagedata[r + 1][c + 1][k];
				ImagedataNew[i][j][k] = (char)val;

			}
		}
	}




	// Write image data (filename specified by second argument) from image data matrix


	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataNew, sizeof(unsigned char), NewSize*NewSize*BytesPerPixel, file);
	fclose(file);


	return 0;
}
