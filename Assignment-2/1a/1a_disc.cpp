#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 3;
	const int size = 512;
	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Allocate image data array
	unsigned char Imagedata[size][size][bytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), size*size*bytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int i, j, k;
	unsigned char Imagedata_Disc[size][size][bytesPerPixel] = { 0 };

	for (k = 0; k < bytesPerPixel; k++)
	{
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				
				

				float x = (i - 256.0f) / 256.0f;//left shifting by 256 and normalizing to lie in [-1,1]
				float y = (j - 256.0f) / 256.0f;

				float u = x * (sqrt(1.0f - (pow(y, 2.0f)) / 2.0f));//Square to Disc conversion formula
				float v = y * (sqrt(1.0f - (pow(x, 2.0f)) / 2.0f));
				
					
			    int U = (u * 256) + 256;
				int V = (v * 256) + 256;
				

				Imagedata_Disc[U][V][k] = Imagedata[i][j][k];
				//cout << (int)Imagedata_Disc[U][V][k] << endl;
			}
		}
	}
	//cin.get();



	
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_Disc, sizeof(unsigned char), size*size*bytesPerPixel, file);
	fclose(file);

	return 0;
}