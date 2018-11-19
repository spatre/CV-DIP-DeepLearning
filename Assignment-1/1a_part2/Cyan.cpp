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
	int Size1 = 480;
 	int Size2 = 854;
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
		/*if (argc >= 5){
			Size = atoi(argv[4]);
		}*/
	}

	// Allocate image data array
	unsigned char Imagedata[Size1][Size2][BytesPerPixel];
	unsigned char Imagedata_r[Size1*Size2];
	//unsigned char Imagedata_g[Size1*Size2];
	//unsigned char Imagedata_b[Size1*Size2];
	unsigned char Imagedata_C[Size1][Size2];



	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

// To separate the channels from 3D array to 1D array as R,G,B
		for(i=0;i<Size1;i++)
		{
			for(j=0;j<Size2;j++)
			{
				Imagedata_r[i*Size2+j]=(int)Imagedata[i][j][0] ;
				//Imagedata_g[i*Size1+j]=(int)Imagedata[i][j][1] ;
				//Imagedata_b[i*Size1+j]=(int)Imagedata[i][j][2] ;


			}
		}
		//float C[Size*Size];
		//float M[Size*Size];
		//float Y[Size*Size];

		for(i=0;i<Size1;i++)
		{
			for(j=0;j<Size2;j++)
			{
				 Imagedata_C[i][j]=(1.0f-Imagedata_r[i*Size2+j]/255.0f)*255.0f;



			}
		}



	// Write image data (filename specified by second argument) from image data matrix


	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_C, sizeof(unsigned char), Size1*Size2, file);
	fclose(file);


	return 0;
}
