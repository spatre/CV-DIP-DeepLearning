#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "myHeader.h"

using namespace std;


int condPatternMatch(int pattern, char type)
{
	int S1 = 0, S2 = 57;
	int T1 = 16, T2 = 61;
	int K1 = 26, K2 = 65;
	int condPatterns[] = { 0b001010000,0b100010000,0b000010100,0b000010001, //S
		0b000011000,0b010010000,0b000110000,0b000010010, //S
		0b001011000,0b011010000,0b110010000,0b100110000, //S
		0b000110100,0b000010110,0b000010011,0b000011001, //S
		0b110011000,0b010011001,0b011110000,0b001011010, //ST
		0b011011000,0b110110000,0b000110110,0b000011011, //ST
		0b110011001,0b011110100, //ST

		0b011011011,0b111111000,0b110110110,0b000111111, //STK
		0b111011011,0b011011111,0b111111100,0b111111001, //STK
		0b111110110,0b110110111,0b100111111,0b001111111, //STK
		0b111011111,0b111111101,0b111110111,0b101111111, //STK
		0b001011001,0b111010000,0b100110100,0b000010111, //STK
		0b111011000,0b011011001,0b111110000,0b110110100, //STK
		0b100110110,0b000110111,0b000011111,0b001011011, //STK
		0b111011001,0b111110100,0b100110111,0b001011111, //STK
		0b010011000,0b010110000,0b000110010,0b000011010, //TK
		0b111111011,0b111111110,0b110111111,0b011111111 };// K
	switch (type)
	{
	case 'S':
		for (int i = S1; i <= S2; i++)
		{
			if (pattern == condPatterns[i])
				return 1;
		}
		break;
	case 'T':
		for (int i = T1; i <= T2; i++)
		{
			if (pattern == condPatterns[i])
				return 1;
		}
		break;
	case 'K':
		for (int i = K1; i <= K2; i++)
		{
			if (pattern == condPatterns[i])
				return 1;
		}
		break;
	}

	return 0;
}

int uncondPatternMatch(int pattern, char type)
{
	int uncondPatternsSTWithoutD[] = { 0b001010000,0b100010000, // Spur
		0b000010010,0b000011000, // Single 4-connection
		0b001011000,0b011010000,0b110010000,0b100110000, //LCluster
		0b000110100,0b000010110,0b000010011,0b000011001,
		0b011110000,0b110011000,0b010011001,0b001011010, // 4-connected offset
		0b011011100,0b001011100,0b011010100, // Spur corner Cluster
		0b110110001,0b100110001,0b110010001,
		0b001110110,0b001110100,0b001010110,
		0b100011011,0b100011001,0b100010011
	};
	int uncondPatternsSTWithD[] = { 0b110110000,// Corner Cluster
		0b010111000,// TeeBranch
		0b010111000,
		0b000111010,
		0b000111010,
		0b010110010,
		0b010110010,
		0b010011010,
		0b010011010,
		0b101010001,0b101010010,0b101010011,0b101010100,0b101010101,0b101010110,0b101010111,// VeeBranch
		0b100010101,0b100011100,0b100011101,0b101010100,0b101010101,0b101011100,0b101011101,
		0b001010101,0b010010101,0b011010101,0b100010101,0b101010101,0b110010101,0b111010101,
		0b001010101,0b001110001,0b001110101,0b101010001,0b101010101,0b101110001,0b101110101,
		0b010011100,// DiagonalBranch
		0b010110001,
		0b001110010,
		0b100011010
	};
	int uncondPatternsSTD[] = { 0b110110000,// Corner Cluster
		0b011111011,// TeeBranch
		0b110111110,
		0b110111110,
		0b011111011,
		0b010111111,
		0b111111010,
		0b111111010,
		0b010111111,
		0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,// VeeBranch
		0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,
		0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,
		0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,
		0b011111110,// DiagonalBranch
		0b110111011,
		0b011111110,
		0b110111011
	};
	int uncondPatternsKWithoutD[] = { 0b000010001,0b000010100,0b001010000,0b100010000, // Spur
		0b000010010,0b000011000,0b000110000,0b010010000, // Single 4-connection
		0b010011000,0b010110000,0b000011010,0b000110010// LCorner
	};
	int uncondPatternsKWithD[] = {
		0b110110000,// Corner Cluster
		0b000011011,
		0b010111000,// TeeBranch
		0b010110010,
		0b000111010,
		0b010011010,
		0b101010001,0b101010010,0b101010011,0b101010100,0b101010101,0b101010110,0b101010111,// VeeBranch
		0b100010101,0b100011100,0b100011101,0b101010100,0b101010101,0b101011100,0b101011101,
		0b001010101,0b010010101,0b011010101,0b100010101,0b101010101,0b110010101,0b111010101,
		0b001010101,0b001110001,0b001110101,0b101010001,0b101010101,0b101110001,0b101110101,
		0b010011100,// DiagonalBranch
		0b010110001,
		0b001110010,
		0b100011010,
	};
	int uncondPatternsKDMask[] = { 0b110110000,// Corner Cluster
		0b000011011,
		0b010111000,// TeeBranch
		0b010110010,
		0b000111010,
		0b010011010,
		0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,// VeeBranch
		0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,
		0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,
		0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,
		0b011111110,// DiagonalBranch
		0b110111011,
		0b011111110,
		0b110111011
	};
	int lengthSTWithoutD = sizeof(uncondPatternsSTWithoutD) / sizeof(int);
	int lengthSTWithD = sizeof(uncondPatternsSTWithD) / sizeof(int);
	int lengthWithoutD = sizeof(uncondPatternsKWithoutD) / sizeof(int);
	int lengthKWithD = sizeof(uncondPatternsKWithD) / sizeof(int);
	switch (type)
	{
	case 'S':
	case 'T':
		for (int i = 0; i<lengthSTWithoutD; i++)
		{
			if (pattern == uncondPatternsSTWithoutD[i])
				return 1;
		}
		for (int i = 0; i<lengthSTWithD; i++)
		{
			int tmp = pattern & uncondPatternsSTD[i];
			if (tmp == uncondPatternsSTWithD[i])
				return 1;
		}
		break;
	case 'K':
		for (int i = 0; i<lengthWithoutD; i++)
		{
			if (pattern == uncondPatternsKWithoutD[i])
				return 1;
		}
		for (int i = 0; i<lengthKWithD; i++)
		{
			int tmp = pattern & uncondPatternsKDMask[i];
			if (tmp == uncondPatternsKWithD[i])
				return 1;
		}
		break;
	}
	return 0;
}


int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 1;
	const int height = 372;
	const int width = 372;
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

	//const int X = 255;
	int i, j, k, a, b, c, d;
	const int N = 3;
	const int n = (N - 1) / 2;
	const int disp = 2 * n;
	unsigned char Imagedata_Pad[height + disp][width + disp][bytesPerPixel] = { 0 };
	//unsigned char M_Image[height + disp][width + disp][bytesPerPixel] = { 0 };
	unsigned char Imagedata_temp[height][width][bytesPerPixel] = { 0 };
	unsigned char Imagedata_final[height][width][bytesPerPixel] = { 0 };
	unsigned char Imagedata_Pad2[height + disp][width + disp][bytesPerPixel] = { 0 };
	unsigned char Imagedata_Out[height][width][bytesPerPixel] = { 0 };
	//Converting to Binary
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((int)Imagedata[i][j][0] < 127)
			{
				Imagedata[i][j][0] = 0;
			}
			else
			{
				Imagedata[i][j][0] = 255;
			}

		}
	}


	//complementing the image
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((int)Imagedata[i][j][0] == 0)
			{
				Imagedata[i][j][0] = 255;
			}
			else
			{
				Imagedata[i][j][0] = 0;
			}

		}
	}


	//Padding the image 

	for (i = n; i < height + n; i++)
	{
		for (j = n; j < width + n; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata[i - n][j - n][0];


		}
	}

	int counter = 0;
	while (counter < 3000)
	{

		//Stage 1 of the Process
		for (a = n; a < height + n; a++)
		{
			for (b = n; b < width + n; b++)
			{
				if (Imagedata_Pad[a][b][0] == 255)
				{
					int pat = 0b000000000;

					/*pat = pat << 1;
					if (Imagedata_Pad[a][b][0] == 255) {
						pat = pat + 1;
					}*/

					pat = pat << 1;
					if (Imagedata_Pad[a][b + 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad[a - 1][b + 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad[a - 1][b][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad[a - 1][b - 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad[a][b - 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad[a + 1][b - 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad[a + 1][b][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad[a + 1][b + 1][0] == 255) {
						pat = pat + 1;
					}
					/*for (c = -1; c <= 1; c++)
					{
					for (d = -1; d <= 1; d++)
					{
					pat = pat << 1;
					if (Imagedata_Pad[a + c][b + d][0] == 255)
					{
					pat = pat + 1;
					}
					}
					}*/

					int hit = condPatternMatch(pat, 'S');
					if (hit == 1)
					{
						Imagedata_temp[a - n][b - n][0] = 255;
					}
					else
					{
						Imagedata_temp[a - n][b - n][0] = 0;
					}
				}

			}
		}

		for (i = n; i < height + n; i++)
		{
			for (j = n; j < width + n; j++)
			{
				Imagedata_Pad2[i][j][0] = Imagedata_temp[i - n][j - n][0];


			}
		}


		//Stage 2 of the process
		for (a = n; a < height + n; a++)
		{
			for (b = n; b < width + n; b++)
			{
				if (Imagedata_Pad2[a][b][0] == 255)
				{
					int pat = 0b000000000;
					/*for (c = -1; c <= 1; c++)
					{
					for (d = -1; d <= 1; d++)
					{
					pat = pat << 1;
					if (Imagedata_Pad2[a + c][b + d][0] == 255)
					{
					pat = pat + 1;
					}
					}
					}*/

					/*pat = pat << 1;
					if (Imagedata_Pad2[a][b][0] == 255) {
						pat = pat + 1;
					}*/

					pat = pat << 1;
					if (Imagedata_Pad2[a][b + 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad2[a - 1][b + 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad2[a - 1][b][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad2[a - 1][b - 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad2[a][b - 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad2[a + 1][b - 1][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad2[a + 1][b][0] == 255) {
						pat = pat + 1;
					}

					pat = pat << 1;
					if (Imagedata_Pad2[a + 1][b + 1][0] == 255) {
						pat = pat + 1;
					}

					int hit = uncondPatternMatch(pat, 'S');
					if (hit == 1)
					{
						Imagedata_final[a - n][b - n][0] = 0;
					}
					else
					{
						Imagedata_final[a - n][b - n][0] = 255;
					}
				}

			}
		}
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				Imagedata_Pad[i][j][0] = Imagedata_final[i][j][0];
			}
		}
		counter++;
	}


	for (i = n; i < height + n; i++)
	{
		for (j = n; j < width + n; j++)
		{
			Imagedata_Out[i - n][j - n][0] = Imagedata_Pad[i][j][0];
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
	fwrite(Imagedata_Out, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);

	return 0;
}