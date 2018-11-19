#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <algorithm>

using namespace std;


unsigned char* initialize1DArray(int length);

unsigned char** initializeSingleChannelImage(int length, int breadth);

unsigned char** convertTo3D(unsigned char* oneD, int length, int breadth);

unsigned char* convertTo1D(unsigned char** Imagedata3D, int length, int breadth);

unsigned char** generatePaddedImage(unsigned char** Imagedata3D, int length, int breadth, int padSize);

bool isInversionRequired(unsigned char** Imagedata3D);

void generateBinaryImage(unsigned char** Imagedata3D, int length, int breadth, bool invert);

unsigned char** returnM_Matrix(unsigned char** Image, int length, int breadth);

unsigned char** returnSkeletonImage(unsigned char** updatedImage, int length, int breadth, unsigned char** M_Matrix, unsigned char** Imagedata3D);

unsigned char** returnShrinkImage(unsigned char** updatedImage, int length, int breadth, unsigned char** M_Matrix, unsigned char** Imagedata3D);

unsigned char** returnThinnedImage(unsigned char** updatedImage, int length, int breadth, unsigned char** M_Matrix, unsigned char** Imagedata3D);



unsigned char* initialize1DArray(int length)
{
	unsigned char* oneDArray = new unsigned char[length];

	for (int i = 0; i < length; i++)
	{
		oneDArray[i] = 0;
	}
	return oneDArray;
}

unsigned char** initializeSingleChannelImage(int length, int breadth)
{
	unsigned char**newImage = new unsigned char*[length];
	for (int row = 0; row < length; row++)
	{
		newImage[row] = new unsigned char[breadth];
		for (int col = 0; col < breadth; col++)
		{
			newImage[row][col] = 0;

		}
	}
	return newImage;
}

unsigned char** convertTo3D(unsigned char* oneD, int length, int breadth)
{
	unsigned char** ThreeD = initializeSingleChannelImage(length, breadth);
	int x = 0;


	for (int row = 0; row < length; row++)
	{
		for (int col = 0; col < breadth; col++)
		{
			ThreeD[row][col] = oneD[x];
			x++;
		}
	}
	return ThreeD;
}

unsigned char* convertTo1D(unsigned char** ThreeD, int length, int breadth)
{
	unsigned char* oneD = initialize1DArray(length*breadth);
	int index = 0;
	for (int row = 0; row < length; row++)
	{
		for (int col = 0; col < breadth; col++)
		{
			oneD[index] = ThreeD[row][col];
			index++;
		}
	}

	return oneD;
}



unsigned char** generatePaddedImage(unsigned char** Imagedata3D, int length, int breadth, int padSize)
{
	int newLength = length + (padSize * 2);
	int newBreadth = breadth + (padSize * 2);
	unsigned char** paddedImage = initializeSingleChannelImage(newLength, newBreadth);

	for (int i = padSize; i < length + padSize; i++)
	{
		for (int j = padSize; j < breadth + padSize; j++)
		{
			paddedImage[i][j] = Imagedata3D[i - padSize][j - padSize];

		}
	}

	return paddedImage;
}

bool isInversionRequired(unsigned char** Imagedata3D)
{
	bool invert = false;

	if (Imagedata3D[0][0] < 127)
	{
		invert = false;

	}
	else
	{
		invert = true;

	}

	return invert;
}
void generateBinaryImage(unsigned char** Imagedata3D, int length, int breadth, bool invert)
{

	for (int row = 0; row < length; row++)
	{
		for (int col = 0; col < breadth; col++)
		{
			if (invert == true)
			{
				if (Imagedata3D[row][col] < 127)
				{
					Imagedata3D[row][col] = 255;
				}
				else
				{
					Imagedata3D[row][col] = 0;
				}
			}
			else
			{
				if (Imagedata3D[row][col] < 127)
				{
					Imagedata3D[row][col] = 0;
				}
				else
				{
					Imagedata3D[row][col] = 255;
				}

			}
		}
	}
}

unsigned char** returnM_Matrix(unsigned char** Imagedata3D, int length, int breadth)
{
	unsigned char conditionalMask[58][9] = { { 0,1,0,0,1,1,0,0,0 },{ 0,1,0,1,1,0,0,0,0 },{ 0,0,0,1,1,0,0,1,0 },{ 0,0,0,0,1,1,0,1,0 },
	{ 0,0,1,0,1,1,0,0,1 },{ 1,1,1,0,1,0,0,0,0 },{ 1,0,0,1,1,0,1,0,0 },{ 0,0,0,0,1,0,1,1,1 },
	{ 1,1,1,0,1,1,0,0,0 },{ 0,1,1,0,1,1,0,0,1 },{ 1,1,1,1,1,0,0,0,0 },{ 1,1,0,1,1,0,1,0,0 },{ 1,0,0,1,1,0,1,1,0 } ,{ 0,0,0,1,1,0,1,1,1 },{ 0,0,0,0,1,1,1,1,1 },{ 0,0,1,0,1,1,0,1,1 },
	{ 1,1,1,0,1,1,0,0,1 },{ 1,1,1,1,1,0,1,0,0 },{ 1,0,0,1,1,0,1,1,1 },{ 0,0,1,0,1,1,1,1,1 },
	{ 0,1,1,0,1,1,0,1,1 },{ 1,1,1,1,1,1,0,0,0 },{ 1,1,0,1,1,0,1,1,0 },{ 0,0,0,1,1,1,1,1,1 },
	{ 1,1,1,0,1,1,0,1,1 },{ 0,1,1,0,1,1,1,1,1 },{ 1,1,1,1,1,1,1,0,0 },{ 1,1,1,1,1,1,0,0,1 },{ 1,1,1,1,1,0,1,1,0 },{ 1,1,0,1,1,0,1,1,1 },{ 1,0,0,1,1,1,1,1,1 },{ 0,0,1,1,1,1,1,1,1 },
	{ 1,1,1,0,1,1,1,1,1 },{ 1,1,1,1,1,1,1,0,1 },{ 1,1,1,1,1,0,1,1,1 },{ 1,0,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,0,1,1 },{ 1,1,1,1,1,1,1,1,0 },{ 1,1,0,1,1,1,1,1,1 },{ 0,1,1,1,1,1,1,1,1 } };



	unsigned char** M_Matrix = initializeSingleChannelImage(length, breadth);

	for (int row = 1; row < length - 1; row++)
	{
		for (int col = 1; col < breadth - 1; col++)
		{
			M_Matrix[row][col] = 0;
			if (Imagedata3D[row][col] == 1)
			{
				unsigned char pixelStack[9]; int index = 0;
				for (int r = row - 1; r <= row + 1; r++)
				{
					for (int c = col - 1; c <= col + 1; c++)
					{
						pixelStack[index] = Imagedata3D[r][c];
						index++;
					}
				}
				bool flag;
				for (int i = 0; i<58; i++)
				{
					flag = true;
					for (int j = 0; j<9; j++)
					{
						if (int(conditionalMask[i][j]) != int(pixelStack[j]))
						{
							flag = false;
							break;
						}
					}
					if (flag == true)
					{
						M_Matrix[row][col] = 1;
						break;
					}
				}
			}
		}
	}

	return M_Matrix;
}

unsigned char** returnSkeletonImage(unsigned char** updatedImage, int length, int breadth, unsigned char** M_Matrix, unsigned char** Imagedata3D)
{
	for (int row = 0; row < length; row++)
	{
		for (int col = 0; col < breadth; col++)
		{
			if (M_Matrix[row][col] == 0)
			{
				updatedImage[row][col] = Imagedata3D[row][col];
			}
			if (M_Matrix[row][col] == 1)
			{
				int pixelStack[9];
				int index = 0;
				for (int r = row - 1; r <= row + 1; r++)
				{
					for (int c = col - 1; c <= col + 1; c++)
					{
						pixelStack[index] = M_Matrix[r][c];
						index++;
					}
				}

				bool flag = false;
				if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;
				}
				else  if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 1 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				//single 4 connection
				else if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				// L corner
				else    if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else  if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				//Corner Cluster
				else  if (pixelStack[0] == 1 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1)
				{
					flag = true;
				}
				else  if (pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1 && pixelStack[8] == 1)
				{
					flag = true;
				}
				// Tee Branch
				else if (pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1)
				{
					flag = true;

				}
				else  if (pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[7] == 1)
				{
					flag = true;

				}
				else  if (pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1)
				{
					flag = true;

				}
				else  if (pixelStack[1] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1)
				{
					flag = true;

				}
				// Vee Branch

				else  if (pixelStack[0] == 1 && pixelStack[2] == 1 && pixelStack[4] == 1 && ((pixelStack[6] || pixelStack[7] || pixelStack[8]) == 1))
				{
					flag = true;

				}

				else if (pixelStack[0] == 1 && pixelStack[4] == 1 && pixelStack[6] == 1 && ((pixelStack[2] || pixelStack[5] || pixelStack[8]) == 1))
				{
					flag = true;

				}
				else   if (pixelStack[4] == 1 && pixelStack[6] == 1 && pixelStack[8] == 1 && ((pixelStack[0] || pixelStack[1] || pixelStack[2]) == 1))
				{
					flag = true;

				}
				else if (pixelStack[2] == 1 && pixelStack[4] == 1 && pixelStack[8] == 1 && ((pixelStack[0] || pixelStack[3] || pixelStack[6]) == 1))
				{
					flag = true;

				}

				//Diagonal Branch
				else if (pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 1 && pixelStack[7] == 0)
				{
					flag = true;

				}
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;
					//break;
				}
				else  if (pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1)
				{
					flag = true;

				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;

				}

				if (flag == true)
				{
					updatedImage[row][col] = 1;
				}
				else if (flag == false)
				{
					updatedImage[row][col] = 0;
				}

			}

		}

	}
	return updatedImage;

}
unsigned char** returnShrinkImage(unsigned char** updatedImage, int length, int breadth, unsigned char** M_Matrix, unsigned char** Imagedata3D)
{
	for (int row = 0; row < length; row++)
	{
		for (int col = 0; col < breadth; col++)
		{
			if (M_Matrix[row][col] == 0)
			{
				updatedImage[row][col] = Imagedata3D[row][col];
			}
			if (M_Matrix[row][col] == 1)
			{
				int pixelStack[9];
				int index = 0; 
				for (int r = row - 1; r <= row + 1; r++)
				{
					for (int c = col - 1; c <= col + 1; c++)
					{
						pixelStack[index] = M_Matrix[r][c];
						index++;
					}
				}

				bool flag = false;
				//Spur
				if ((pixelStack[0]) == 0 && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				//single 4 connection
				else if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				// L cluster
				else if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else    if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 1 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 1 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 1)
				{
					flag = true;

				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;

				}
				//4-connected offset
				else    if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
					//break;
				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;

				}

				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;

				}
				//Corner Cluster
				else  if (pixelStack[0] == 1 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1)
				{
					flag = true;

				}
				//Spur corner cluster
				else if (pixelStack[0] == 0 && ((pixelStack[1] || pixelStack[5]) == 1) && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[6] == 1 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else if (pixelStack[0] == 1 && ((pixelStack[1] || pixelStack[3]) == 1) && pixelStack[2] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;
				}
				else if (pixelStack[0] == 0 && ((pixelStack[3] || pixelStack[7]) == 1) && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else if (pixelStack[0] == 1 && ((pixelStack[5] || pixelStack[7]) == 1) && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[6] == 0 && pixelStack[8] == 1)
				{
					flag = true;

				}

				//Tee Branch
				else if (pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				//---D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0)
				{
					flag = true;
				}

				//---D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 1)
				{
					flag = true;
					//break;
				}
				//--D0
				else  if (pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else if (pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;

				}
				//--D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[7] == 1)
				{
					flag = true;
				}
				//--D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1)
				{
					flag = true;

				}
				//--D0
				else  if (pixelStack[1] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}


				// Vee Branch
				//--
				else  if (pixelStack[0] == 1 && pixelStack[2] == 1 && pixelStack[4] == 1 && ((pixelStack[6] || pixelStack[7] || pixelStack[8]) == 1))
				{
					flag = true;

				}

				else if (pixelStack[0] == 1 && pixelStack[4] == 1 && pixelStack[6] == 1 && ((pixelStack[2] || pixelStack[5] || pixelStack[8]) == 1))
				{
					flag = true;

				}
				//---
				else   if (pixelStack[4] == 1 && pixelStack[6] == 1 && pixelStack[8] == 1 && ((pixelStack[0] || pixelStack[1] || pixelStack[2]) == 1))
				{
					flag = true;


				}
				//--

				else if (pixelStack[2] == 1 && pixelStack[4] == 1 && pixelStack[8] == 1 && ((pixelStack[0] || pixelStack[3] || pixelStack[6]) == 1))
				{
					flag = true;

				}

				//Diagonal Branch
				else if (pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 1 && pixelStack[7] == 0)
				{

					flag = true;

				}

				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{

					flag = true;
				}

				else  if (pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1)
				{

					flag = true;

				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{

					flag = true;
				}
				if (flag == true)
				{
					updatedImage[row][col] = 1;
				}
				else if (flag == false)
				{
					updatedImage[row][col] = 0;
				}

			}

		}

	}
	return updatedImage;

}

unsigned char** returnThinnedImage(unsigned char** updatedImage, int length, int breadth, unsigned char** M_Matrix, unsigned char** Imagedata3D)
{
	for (int row = 0; row < length; row++)
	{
		for (int col = 0; col < breadth; col++)
		{
			if (M_Matrix[row][col] == 0)
			{
				updatedImage[row][col] = Imagedata3D[row][col];
			}
			if (M_Matrix[row][col] == 1)
			{
				int pixelStack[9];
				int index = 0;
				for (int r = row - 1; r <= row + 1; r++)
				{
					for (int c = col - 1; c <= col + 1; c++)
					{
						pixelStack[index] = M_Matrix[r][c];
						index++;
					}
				}

				bool flag = false;
				if ((pixelStack[0]) == 0 && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;

				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				//single 4 connection
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{

					flag = true;
					
				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;					

				}
				// L cluster
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{

					flag = true;
				}
				else   if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else    if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 1 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 1 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 1)
				{
					flag = true;
				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;
				}
				//4-connected offset
				else    if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;
				}
				else    if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				//Corner Cluster
				else  if (pixelStack[0] == 1 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1)
				{
					flag = true;
				}
				//Spur corner cluster
				else if (pixelStack[0] == 0 && ((pixelStack[1] || pixelStack[5]) == 1) && pixelStack[2] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[6] == 1 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else if (pixelStack[0] == 1 && ((pixelStack[1] || pixelStack[3]) == 1) && pixelStack[2] == 0 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;
				}
				else if (pixelStack[0] == 0 && ((pixelStack[3] || pixelStack[7]) == 1) && pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else if (pixelStack[0] == 1 && ((pixelStack[5] || pixelStack[7]) == 1) && pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[6] == 0 && pixelStack[8] == 1)
				{
					flag = true;
				}
				else if (pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 0 && pixelStack[8] == 0)
				{
					flag = true;
				}
				//---D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 0)
				{
					flag = true;
				}
				//---D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 1)
				{
					flag = true;
				}
				//--D0
				else  if (pixelStack[1] == 0 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				else if (pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{

					flag = true;

				}
				//--D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[7] == 1)
				{
					flag = true;
				}
				//--D0
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1)
				{
					flag = true;
				}
				//--D0
				else  if (pixelStack[1] == 1 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 0 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				// Vee Branch
				else  if (pixelStack[0] == 1 && pixelStack[2] == 1 && pixelStack[4] == 1 && ((pixelStack[6] || pixelStack[7] || pixelStack[8]) == 1))
				{
					flag = true;
				}
				else if (pixelStack[0] == 1 && pixelStack[4] == 1 && pixelStack[6] == 1 && ((pixelStack[2] || pixelStack[5] || pixelStack[8]) == 1))
				{
					flag = true;
				}
				else   if (pixelStack[4] == 1 && pixelStack[6] == 1 && pixelStack[8] == 1 && ((pixelStack[0] || pixelStack[1] || pixelStack[2]) == 1))
				{
					flag = true;
				}
				else if (pixelStack[2] == 1 && pixelStack[4] == 1 && pixelStack[8] == 1 && ((pixelStack[0] || pixelStack[3] || pixelStack[6]) == 1))
				{
					flag = true;

				}
				//Diagonal Branch
				else if (pixelStack[1] == 1 && pixelStack[2] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[6] == 1 && pixelStack[7] == 0)
				{
					flag = true;
				}
				else  if (pixelStack[0] == 0 && pixelStack[1] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[7] == 0 && pixelStack[8] == 1)
				{
					flag = true;
				}
				else  if (pixelStack[1] == 0 && pixelStack[2] == 1 && pixelStack[3] == 1 && pixelStack[4] == 1 && pixelStack[5] == 0 && pixelStack[6] == 0 && pixelStack[7] == 1)
				{
					flag = true;
				}
				else  if (pixelStack[0] == 1 && pixelStack[1] == 0 && pixelStack[3] == 0 && pixelStack[4] == 1 && pixelStack[5] == 1 && pixelStack[7] == 1 && pixelStack[8] == 0)
				{
					flag = true;
				}
				if (flag == true)
				{
					updatedImage[row][col] = 1;
				}
				else if (flag == false)
				{
					updatedImage[row][col] = 0;
				}

			}

		}

	}
	return updatedImage;

}