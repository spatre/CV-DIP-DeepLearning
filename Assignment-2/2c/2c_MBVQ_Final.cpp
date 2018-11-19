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
	const int height = 700;
	const int width = 700;
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
	//To store CMY data from the given RGB data
	//const int diffuser = 1;//1-Floyd-Steinberg's matrix, 2-Jarvis,Judice and Ninke matrix, 3-Stucki matrix
	//const int N = 3;// 3- FS matrix, 5- JJN and Stucki matrix.
	//const int n = (N - 1) / 2;
	//const int disp = 2 * n;
	//unsigned char Imagedata_Big[height + disp][width + disp][bytesPerPixel] = { 0 };
	unsigned char Imagedata_Halftone[height][width][bytesPerPixel] = { 0 };
	int i, j;
	//int div = divider(diffuser);
	double x, y, z;
	int vect = 0;

	//To store the CMY data
	double** cmy_r = initialDArray(height, width);
	double** cmy_g = initialDArray(height, width);
	double** cmy_b = initialDArray(height, width);

	//To store the error data
	double** err_r = initialDArray(height, width);
	double** err_g = initialDArray(height, width);
	double** err_b = initialDArray(height, width);

	//Initializing the 6 Minimum Brightness Variation Quadruples(MBVQ) values in the CMYK space 
	double CMYW[4][3] = { { 0,0,0 },{ 0,0,255},{ 255,0,0 },{ 0,255,0 } };//CMYW
	double MYGC[4][3] = { { 0,0,255 },{ 255,0,0 },{ 255,0,255 },{ 0,255,0 } };// MYGC
	double RGMY[4][3] = { { 0,0,255 },{ 255,0,255 },{ 0,255,255 },{ 0,255,0 } };// RGMY
	double KRGB[4][3] = { { 255,255,255 },{ 255,0,255 },{ 0,255,255 },{ 255,255,0 } };// KRGB
	double RGBM[4][3] = { { 0,255,255 },{ 255,255,0 },{ 255,0,255 },{ 0,255,0 } };// RGBM
	double CMGB[4][3] = { { 255,0,255 },{ 255,0,0 },{ 0,255,0 },{ 255,255,0 } };// CMGB


																	//Converting RGB to CMY
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			cmy_r[i][j] = 255 - (double)Imagedata[i][j][0];
			cmy_g[i][j] = 255 - (double)Imagedata[i][j][1];
			cmy_b[i][j] = 255 - (double)Imagedata[i][j][2];
		}
	}

	//Implementing the MBVQ algorithm
	for (i = 0; i < height; i++)
	{
		
			for (j = 0; j < width; j++)
			{
				//CMY value plus the error value to define the 3D location of the pixel
				x = cmy_r[i][j] + err_r[i][j];
				y = cmy_g[i][j] + err_g[i][j];
				z = cmy_b[i][j] + err_b[i][j];

				if (x + y <= 255)
				{
					if (y + z <= 255)
					{
						if (x + y + z <= 255)
						{
							//CMYW
							if (x >= 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x >= 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}

							vect = distance(x, y, z, CMYW);//Getting the Vertex

							err_r[i][j] = cmy_r[i][j] + err_r[i][j] - CMYW[vect][0];
							err_g[i][j] = cmy_g[i][j] + err_g[i][j] - CMYW[vect][1];
							err_b[i][j] = cmy_b[i][j] + err_b[i][j] - CMYW[vect][2];

							//Now to calculate error diffusion using FS method
							if (j + 1 < width)
							{
								err_r[i][j + 1] = err_r[i][j + 1] + err_r[i][j] * 7 / 16;
								err_g[i][j + 1] = err_g[i][j + 1] + err_g[i][j] * 7 / 16;
								err_b[i][j + 1] = err_b[i][j + 1] + err_b[i][j] * 7 / 16;
							}
							if (i + 1 < height&&j - 1 >= 0)
							{
								err_r[i + 1][j - 1] = err_r[i + 1][j - 1] + err_r[i][j] * 3 / 16;
								err_g[i + 1][j - 1] = err_g[i + 1][j - 1] + err_g[i][j] * 3 / 16;
								err_b[i + 1][j - 1] = err_b[i + 1][j - 1] + err_b[i][j] * 3 / 16;
							}
							if (i + 1 < height)
							{
								err_r[i + 1][j] = err_r[i + 1][j] + err_r[i][j] * 5 / 16;
								err_g[i + 1][j] = err_g[i + 1][j] + err_g[i][j] * 5 / 16;
								err_b[i + 1][j] = err_b[i + 1][j] + err_b[i][j] * 5 / 16;
							}
							if (i + 1 < height&&j + 1 < width)
							{
								err_r[i + 1][j + 1] = err_r[i + 1][j + 1] + err_r[i][j] * 1 / 16;
								err_g[i + 1][j + 1] = err_g[i + 1][j + 1] + err_g[i][j] * 1 / 16;
								err_b[i + 1][j + 1] = err_b[i + 1][j + 1] + err_b[i][j] * 1 / 16;
							}

						}
						else//MYGC 
						{
							if (x >= 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x >= 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}

							vect = distance(x, y, z, MYGC);//Getting the Vertex

							err_r[i][j] = cmy_r[i][j] + err_r[i][j] - MYGC[vect][0];
							err_g[i][j] = cmy_g[i][j] + err_g[i][j] - MYGC[vect][1];
							err_b[i][j] = cmy_b[i][j] + err_b[i][j] - MYGC[vect][2];

							//Now to calculate error diffusion using FS method
							if (j + 1 < width)
							{
								err_r[i][j + 1] = err_r[i][j + 1] + err_r[i][j] * 7 / 16;
								err_g[i][j + 1] = err_g[i][j + 1] + err_g[i][j] * 7 / 16;
								err_b[i][j + 1] = err_b[i][j + 1] + err_b[i][j] * 7 / 16;
							}
							if (i + 1 < height&&j - 1 >= 0)
							{
								err_r[i + 1][j - 1] = err_r[i + 1][j - 1] + err_r[i][j] * 3 / 16;
								err_g[i + 1][j - 1] = err_g[i + 1][j - 1] + err_g[i][j] * 3 / 16;
								err_b[i + 1][j - 1] = err_b[i + 1][j - 1] + err_b[i][j] * 3 / 16;
							}
							if (i + 1 < height)
							{
								err_r[i + 1][j] = err_r[i + 1][j] + err_r[i][j] * 5 / 16;
								err_g[i + 1][j] = err_g[i + 1][j] + err_g[i][j] * 5 / 16;
								err_b[i + 1][j] = err_b[i + 1][j] + err_b[i][j] * 5 / 16;
							}
							if (i + 1 < height&&j + 1 < width)
							{
								err_r[i + 1][j + 1] = err_r[i + 1][j + 1] + err_r[i][j] * 1 / 16;
								err_g[i + 1][j + 1] = err_g[i + 1][j + 1] + err_g[i][j] * 1 / 16;
								err_b[i + 1][j + 1] = err_b[i + 1][j + 1] + err_b[i][j] * 1 / 16;
							}
						}

					}
					else//RGMY
					{
						if (x >= 127 && y >= 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x >= 127 && y >= 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 255;
						}
						if (x >= 127 && y < 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x >= 127 && y < 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 255;
						}
						if (x < 127 && y >= 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x < 127 && y >= 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 255;
						}
						if (x < 127 && y < 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x < 127 && y < 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 255;
						}

						vect = distance(x, y, z, RGMY);//Getting the Vertex

						err_r[i][j] = cmy_r[i][j] + err_r[i][j] - RGMY[vect][0];
						err_g[i][j] = cmy_g[i][j] + err_g[i][j] - RGMY[vect][1];
						err_b[i][j] = cmy_b[i][j] + err_b[i][j] - RGMY[vect][2];

						//Now to calculate error diffusion using FS method
						if (j + 1 < width)
						{
							err_r[i][j + 1] = err_r[i][j + 1] + err_r[i][j] * 7 / 16;
							err_g[i][j + 1] = err_g[i][j + 1] + err_g[i][j] * 7 / 16;
							err_b[i][j + 1] = err_b[i][j + 1] + err_b[i][j] * 7 / 16;
						}
						if (i + 1 < height&&j - 1 >= 0)
						{
							err_r[i + 1][j - 1] = err_r[i + 1][j - 1] + err_r[i][j] * 3 / 16;
							err_g[i + 1][j - 1] = err_g[i + 1][j - 1] + err_g[i][j] * 3 / 16;
							err_b[i + 1][j - 1] = err_b[i + 1][j - 1] + err_b[i][j] * 3 / 16;
						}
						if (i + 1 < height)
						{
							err_r[i + 1][j] = err_r[i + 1][j] + err_r[i][j] * 5 / 16;
							err_g[i + 1][j] = err_g[i + 1][j] + err_g[i][j] * 5 / 16;
							err_b[i + 1][j] = err_b[i + 1][j] + err_b[i][j] * 5 / 16;
						}
						if (i + 1 < height&&j + 1 < width)
						{
							err_r[i + 1][j + 1] = err_r[i + 1][j + 1] + err_r[i][j] * 1 / 16;
							err_g[i + 1][j + 1] = err_g[i + 1][j + 1] + err_g[i][j] * 1 / 16;
							err_b[i + 1][j + 1] = err_b[i + 1][j + 1] + err_b[i][j] * 1 / 16;
						}
					}


				}
				else
				{
					if (y + z > 255)
					{
						if (x + y + z > 510)//KRGB
						{
							if (x >= 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x >= 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}

							vect = distance(x, y, z, KRGB);//Getting the Vertex

							err_r[i][j] = cmy_r[i][j] + err_r[i][j] - KRGB[vect][0];
							err_g[i][j] = cmy_g[i][j] + err_g[i][j] - KRGB[vect][1];
							err_b[i][j] = cmy_b[i][j] + err_b[i][j] - KRGB[vect][2];

							//Now to calculate error diffusion using FS method
							if (j + 1 < width)
							{
								err_r[i][j + 1] = err_r[i][j + 1] + err_r[i][j] * 7 / 16;
								err_g[i][j + 1] = err_g[i][j + 1] + err_g[i][j] * 7 / 16;
								err_b[i][j + 1] = err_b[i][j + 1] + err_b[i][j] * 7 / 16;
							}
							if (i + 1 < height&&j - 1 >= 0)
							{
								err_r[i + 1][j - 1] = err_r[i + 1][j - 1] + err_r[i][j] * 3 / 16;
								err_g[i + 1][j - 1] = err_g[i + 1][j - 1] + err_g[i][j] * 3 / 16;
								err_b[i + 1][j - 1] = err_b[i + 1][j - 1] + err_b[i][j] * 3 / 16;
							}
							if (i + 1 < height)
							{
								err_r[i + 1][j] = err_r[i + 1][j] + err_r[i][j] * 5 / 16;
								err_g[i + 1][j] = err_g[i + 1][j] + err_g[i][j] * 5 / 16;
								err_b[i + 1][j] = err_b[i + 1][j] + err_b[i][j] * 5 / 16;
							}
							if (i + 1 < height&&j + 1 < width)
							{
								err_r[i + 1][j + 1] = err_r[i + 1][j + 1] + err_r[i][j] * 1 / 16;
								err_g[i + 1][j + 1] = err_g[i + 1][j + 1] + err_g[i][j] * 1 / 16;
								err_b[i + 1][j + 1] = err_b[i + 1][j + 1] + err_b[i][j] * 1 / 16;
							}

						}
						else//RGBM
						{
							if (x >= 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x >= 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x >= 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 0;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y >= 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y >= 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 0;
								Imagedata_Halftone[i][j][2] = 255;
							}
							if (x < 127 && y < 127 && z >= 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 0;
							}
							if (x < 127 && y < 127 && z < 127)
							{
								Imagedata_Halftone[i][j][0] = 255;
								Imagedata_Halftone[i][j][1] = 255;
								Imagedata_Halftone[i][j][2] = 255;
							}

							vect = distance(x, y, z, RGBM);//Getting the Vertex

							err_r[i][j] = cmy_r[i][j] + err_r[i][j] - RGBM[vect][0];
							err_g[i][j] = cmy_g[i][j] + err_g[i][j] - RGBM[vect][1];
							err_b[i][j] = cmy_b[i][j] + err_b[i][j] - RGBM[vect][2];

							//Now to calculate error diffusion using FS method
							if (j + 1 < width)
							{
								err_r[i][j + 1] = err_r[i][j + 1] + err_r[i][j] * 7 / 16;
								err_g[i][j + 1] = err_g[i][j + 1] + err_g[i][j] * 7 / 16;
								err_b[i][j + 1] = err_b[i][j + 1] + err_b[i][j] * 7 / 16;
							}
							if (i + 1 < height&&j - 1 >= 0)
							{
								err_r[i + 1][j - 1] = err_r[i + 1][j - 1] + err_r[i][j] * 3 / 16;
								err_g[i + 1][j - 1] = err_g[i + 1][j - 1] + err_g[i][j] * 3 / 16;
								err_b[i + 1][j - 1] = err_b[i + 1][j - 1] + err_b[i][j] * 3 / 16;
							}
							if (i + 1 < height)
							{
								err_r[i + 1][j] = err_r[i + 1][j] + err_r[i][j] * 5 / 16;
								err_g[i + 1][j] = err_g[i + 1][j] + err_g[i][j] * 5 / 16;
								err_b[i + 1][j] = err_b[i + 1][j] + err_b[i][j] * 5 / 16;
							}
							if (i + 1 < height&&j + 1 < width)
							{
								err_r[i + 1][j + 1] = err_r[i + 1][j + 1] + err_r[i][j] * 1 / 16;
								err_g[i + 1][j + 1] = err_g[i + 1][j + 1] + err_g[i][j] * 1 / 16;
								err_b[i + 1][j + 1] = err_b[i + 1][j + 1] + err_b[i][j] * 1 / 16;
							}
						}
					}
					else//CMGB
					{
						if (x >= 127 && y >= 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x >= 127 && y >= 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 255;
						}
						if (x >= 127 && y < 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x >= 127 && y < 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 0;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 255;
						}
						if (x < 127 && y >= 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x < 127 && y >= 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 0;
							Imagedata_Halftone[i][j][2] = 255;
						}
						if (x < 127 && y < 127 && z >= 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 0;
						}
						if (x < 127 && y < 127 && z < 127)
						{
							Imagedata_Halftone[i][j][0] = 255;
							Imagedata_Halftone[i][j][1] = 255;
							Imagedata_Halftone[i][j][2] = 255;
						}

						vect = distance(x, y, z, CMGB);//Getting the Vertex

						err_r[i][j] = cmy_r[i][j] + err_r[i][j] - CMGB[vect][0];
						err_g[i][j] = cmy_g[i][j] + err_g[i][j] - CMGB[vect][1];
						err_b[i][j] = cmy_b[i][j] + err_b[i][j] - CMGB[vect][2];

						//Now to calculate error diffusion using FS method
						if (j + 1 < width)
						{
							err_r[i][j + 1] = err_r[i][j + 1] + err_r[i][j] * 7 / 16;
							err_g[i][j + 1] = err_g[i][j + 1] + err_g[i][j] * 7 / 16;
							err_b[i][j + 1] = err_b[i][j + 1] + err_b[i][j] * 7 / 16;
						}
						if (i + 1 < height&&j - 1 >= 0)
						{
							err_r[i + 1][j - 1] = err_r[i + 1][j - 1] + err_r[i][j] * 3 / 16;
							err_g[i + 1][j - 1] = err_g[i + 1][j - 1] + err_g[i][j] * 3 / 16;
							err_b[i + 1][j - 1] = err_b[i + 1][j - 1] + err_b[i][j] * 3 / 16;
						}
						if (i + 1 < height)
						{
							err_r[i + 1][j] = err_r[i + 1][j] + err_r[i][j] * 5 / 16;
							err_g[i + 1][j] = err_g[i + 1][j] + err_g[i][j] * 5 / 16;
							err_b[i + 1][j] = err_b[i + 1][j] + err_b[i][j] * 5 / 16;
						}
						if (i + 1 < height&&j + 1 < width)
						{
							err_r[i + 1][j + 1] = err_r[i + 1][j + 1] + err_r[i][j] * 1 / 16;
							err_g[i + 1][j + 1] = err_g[i + 1][j + 1] + err_g[i][j] * 1 / 16;
							err_b[i + 1][j + 1] = err_b[i + 1][j + 1] + err_b[i][j] * 1 / 16;
						}
					}
				}


			}
		
		
		

	}
	








	//for (i = 0; i < height; i++)
	//{
	//for (j = 0; j < width; j++)
	//{
	//	cout << (int)Imagedata_Out[i][j][0] << endl;

	//}
	////cout << endl;
	//}

	//cin.get();

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_Halftone, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	return 0;
}