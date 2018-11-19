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
	int BytesPerPixel;
	int Size = 512;
	int i,j;
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}

	// Allocate image data array
	unsigned char Imagedata[Size][Size][BytesPerPixel];
	unsigned char Imagedata_r[Size*Size];
	unsigned char Imagedata_g[Size*Size];
	unsigned char Imagedata_b[Size*Size];
	unsigned char Imagedata_average[Size][Size];



	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

// To separate the channels from 3D array to 1D array as R,G,B
		for(i=0;i<Size;i++)
		{
			for(j=0;j<Size;j++)
			{
				Imagedata_r[i*Size+j]=(int)Imagedata[i][j][0] ;
				Imagedata_g[i*Size+j]=(int)Imagedata[i][j][1] ;
				Imagedata_b[i*Size+j]=(int)Imagedata[i][j][2] ;


			}
		}

		// To get the grayscale using the average method
		// Storing the 1D array into 3D array to get the image in grayscale
				for(i=0;i<Size;i++)
				{
					for(j=0;j<Size;j++)
					{
						Imagedata_average[i][j]=(Imagedata_r[i*Size+j]+Imagedata_g[i*Size+j]+Imagedata_b[i*Size+j])/3;
					}

				}


	// Write image data (filename specified by second argument) from image data matrix


	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_average, sizeof(unsigned char), Size*Size, file);
	fclose(file);


	return 0;
}
