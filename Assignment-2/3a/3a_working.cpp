#include <iostream>

#include <fstream>

#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <cmath>

#include <algorithm>

#include <string>

#include <limits>

//#include "Header.h"



using namespace std;



int main(int argc, char *argv[])

{

	// Define file pointer and variables

	FILE *file;

	const int BytesPerPixel = 1;

	const int length = 480;

	const int breadth = 640;





	// Allocate image data array

	unsigned char Imagedata3D[length][breadth] = {0};



	// Read image (filename specified by first argument) into image data matrix

	if (!(file = fopen(argv[1], "rb")))

	{

		cout << "Cannot open file: " << argv[1] << endl;

		exit(1);

	}

	fread(Imagedata3D, sizeof(unsigned char), length*breadth*BytesPerPixel, file);

	fclose(file);



	//PROCESSING

	//unsigned char** Imagedata3D = convertTo3D(Imagedata1D, length, breadth);



	unsigned char conditionalMask[58][9] = { { 0,0,1,0,1,0,0,0,0 },

	{ 1,0,0,0,1,0,0,0,0 },

	{ 0,0,0,0,1,0,1,0,0 },

	{ 0,0,0,0,1,0,0,0,1 },



	{ 0,0,0,0,1,1,0,0,0 },

	{ 0,1,0,0,1,0,0,0,0 },

	{ 0,0,0,1,1,0,0,0,0 },

	{ 0,0,0,0,1,0,0,1,0 },



	{ 0,0,1,0,1,1,0,0,0 },

	{ 0,1,1,0,1,0,0,0,0 },

	{ 1,1,0,0,1,0,0,0,0 },

	{ 1,0,0,1,1,0,0,0,0 },



	{ 0,0,0,1,1,0,1,0,0 },

	{ 0,0,0,0,1,0,1,1,0 },

	{ 0,0,0,0,1,0,0,1,1 },

	{ 0,0,0,0,1,1,0,0,1 },



	{ 0,0,1,0,1,1,0,0,1 },

	{ 1,1,1,0,1,0,0,0,0 },

	{ 1,0,0,1,1,0,1,0,0 },

	{ 0,0,0,0,1,0,1,1,1 },

	{ 1,1,0,0,1,1,0,0,0 },



	{ 0,1,0,0,1,1,0,0,1 },

	{ 0,1,1,1,1,0,0,0,0 },

	{ 0,0,1,0,1,1,0,1,0 },

	{ 0,1,1,0,1,1,0,0,0 },



	{ 1,1,0,1,1,0,0,0,0 },

	{ 0,0,0,1,1,0,1,1,0 },

	{ 0,0,0,0,1,1,0,1,1 },

	{ 1,1,0,0,1,1,0,0,1 },

	{ 0,1,1,1,1,0,1,0,0 },



	{ 1,1,1,0,1,1,0,0,0 },

	{ 0,1,1,0,1,1,0,0,1 },

	{ 1,1,1,1,1,0,0,0,0 },

	{ 1,1,0,1,1,0,1,0,0 },

	{ 1,0,0,1,1,0,1,1,0 },



	{ 0,0,0,1,1,0,1,1,1 },

	{ 0,0,0,0,1,1,1,1,1 },

	{ 0,0,1,0,1,1,0,1,1 },

	{ 1,1,1,0,1,1,0,0,1 },

	{ 1,1,1,1,1,0,1,0,0 },



	{ 1,0,0,1,1,0,1,1,1 },

	{ 0,0,1,0,1,1,1,1,1 },

	{ 0,1,1,0,1,1,0,1,1 },

	{ 1,1,1,1,1,1,0,0,0 },

	{ 1,1,0,1,1,0,1,1,0 },



	{ 0,0,0,1,1,1,1,1,1 },

	{ 1,1,1,0,1,1,0,1,1 },

	{ 0,1,1,0,1,1,1,1,1 },

	{ 1,1,1,1,1,1,1,0,0 } ,

	{ 1,1,1,1,1,1,0,0,1 }, //STK9



	{ 1,1,1,1,1,0,1,1,0 },

	{ 1,1,0,1,1,0,1,1,1 },

	{ 1,0,0,1,1,1,1,1,1 },

	{ 0,0,1,1,1,1,1,1,1 },

	{ 1,1,1,0,1,1,1,1,1 }, //STK10



	{ 1,1,1,1,1,1,1,0,1 },

	{ 1,1,1,1,1,0,1,1,1 },

	{ 1,0,1,1,1,1,1,1,1 } };





	unsigned char M_Matrix[length][breadth] = { 0 };



	unsigned char shrunkenimage[length][breadth] = { 0 };



	const int n = 30;

	int counter[n] = { 0 };







	for (int r = 0; r < length; r++)

	{

		for (int c = 0; c < breadth; c++)

		{

			if (Imagedata3D[r][c] <= 127)

			{

				Imagedata3D[r][c] = 0;

			}



			else

			{

				Imagedata3D[r][c] = 1;

			}

		}



	}









	for (int numIterations = 0; numIterations<n; numIterations++)

	{

		for (int r = 1; r < length - 1; r++)

		{

			for (int c = 1; c<breadth - 1; c++)

			{

				M_Matrix[r][c] = 0;

				if (Imagedata3D[r][c] == 1)

				{

					unsigned char temp[9]; int index = 0;

					for (int k = r - 1; k <= r + 1; k++)

					{

						for (int l = c - 1; l <= c + 1; l++)

						{

							temp[index] = Imagedata3D[k][l];

							index++;

						}

					}

					bool flag;

					for (int i = 0; i<58; i++)

					{

						flag = true;

						for (int j = 0; j<9; j++)

						{

							if (int(conditionalMask[i][j]) != int(temp[j]))

							{

								// cout<<int(conditional_skeleton[i][j])<<' '<<int(temp[j]);

								flag = false;

								break;

							}

						}

						if (flag == true)

						{

							M_Matrix[r][c] = 1;

							break;

						}

					}

				}

			}

		}





		for (int r = 0; r< length; r++)

		{

			for (int c = 0; c<breadth; c++)

			{

				if (M_Matrix[r][c] == 0)

				{

					shrunkenimage[r][c] = Imagedata3D[r][c];

				}

				if (M_Matrix[r][c] == 1)

				{

					unsigned char temp1[9]; int index = 0; int temp[9];

					for (int k = r - 1; k <= r + 1; k++)

					{

						for (int l = c - 1; l <= c + 1; l++)

						{

							temp[index] = M_Matrix[k][l];

							index++;

						}

					}



					bool flag = false;

					//Spur

					if ((temp[0]) == 0 && temp[1] == 0 && temp[2] == 1 && temp[3] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						// cout<<flag;



						//break;



					}



					else  if (temp[0] == 1 && temp[1] == 0 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}







					//single 4 connection



					else    if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 1 && temp[8] == 0)



					{



						flag = true;



						//break;



					}



					else   if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}







					// L cluster







					else    if (temp[0] == 0 && temp[1] == 0 && temp[2] == 1 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}







					else   if (temp[0] == 0 && temp[1] == 1 && temp[2] == 1 && temp[3] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}



					else  if (temp[0] == 1 && temp[1] == 1 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;







					}



					else    if (temp[0] == 1 && temp[1] == 0 && temp[2] == 0 && temp[3] == 1 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}







					else    if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0 && temp[3] == 1 && temp[4] == 1 && temp[5] == 0 && temp[6] == 1 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}



					else    if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 1 && temp[7] == 1 && temp[8] == 0)



					{



						flag = true;



						//break;



					}



					else    if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 1 && temp[8] == 1)



					{



						flag = true;



						//break;



					}



					else    if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 0 && temp[8] == 1)



					{



						flag = true;



						//break;



					}











					//4-connected offset



					else    if (temp[0] == 0 && temp[1] == 1 && temp[2] == 1 && temp[3] == 1 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}



					else  if (temp[0] == 1 && temp[1] == 1 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}



					else    if (temp[0] == 0 && temp[1] == 1 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 0 && temp[8] == 1)



					{



						flag = true;



						//break;



					}



					else    if (temp[0] == 0 && temp[1] == 0 && temp[2] == 1 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 1 && temp[8] == 0)



					{



						flag = true;



						//break;



					}



























					//Corner Cluster







					else  if (temp[0] == 1 && temp[1] == 1 && temp[3] == 1 && temp[4] == 1)



					{



						flag = true;



						//break;



					}











					//Spur corner cluster







					else if (temp[0] == 0 && ((temp[1] || temp[5]) == 1) && temp[2] == 1 && temp[3] == 0 && temp[4] == 1 && temp[6] == 1 && temp[7] == 0 && temp[8] == 0)



					{

						flag = true;



						//break;



					}







					else if (temp[0] == 1 && ((temp[1] || temp[3]) == 1) && temp[2] == 0 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 0 && temp[8] == 1)



					{

						flag = true;



						//break;



					}







					else if (temp[0] == 0 && ((temp[3] || temp[7]) == 1) && temp[1] == 0 && temp[2] == 1 && temp[4] == 1 && temp[5] == 0 && temp[6] == 1 && temp[8] == 0)



					{

						flag = true;



						//break;



					}







					else if (temp[0] == 1 && ((temp[5] || temp[7]) == 1) && temp[1] == 0 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[6] == 0 && temp[8] == 1)



					{

						flag = true;



						//break;







					}



					// Tee Branch



					//---D0



					else if (temp[1] == 1 && temp[2] == 0 && temp[3] == 1 && temp[4] == 1 && temp[5] == 1 && temp[7] == 0 && temp[8] == 0)



					{



						flag = true;



						//break;



					}





					//---D0



					else  if (temp[0] == 0 && temp[1] == 1 && temp[3] == 1 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 0)



					{



						flag = true;



						//break;



					}







					//---D0



					else  if (temp[0] == 0 && temp[1] == 0 && temp[3] == 1 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 1)



					{



						flag = true;



						//break;



					}









					//--D0



					else  if (temp[1] == 0 && temp[2] == 0 && temp[3] == 1 && temp[4] == 1 && temp[5] == 1 && temp[7] == 1 && temp[8] == 0)



					{



						flag = true;



						//break;











					}







					else if (temp[1] == 1 && temp[3] == 1 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 1 && temp[8] == 0)



					{



						flag = true;



						//break;



					}





					//--D0



					else  if (temp[0] == 0 && temp[1] == 1 && temp[2] == 0 && temp[3] == 1 && temp[4] == 1 && temp[5] == 0 && temp[7] == 1)



					{



						flag = true;



						//break;



					}





					//--D0



					else  if (temp[0] == 0 && temp[1] == 1 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[7] == 1)



					{



						flag = true;



						//break;



					}







					//--D0



					else  if (temp[1] == 1 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 0 && temp[7] == 1 && temp[8] == 0)



					{



						flag = true;



						//break;



					}









					// Vee Branch



					//--



					else  if (temp[0] == 1 && temp[2] == 1 && temp[4] == 1 && ((temp[6] || temp[7] || temp[8]) == 1))



					{



						flag = true;



						//break;



					}





					//--



					else if (temp[0] == 1 && temp[4] == 1 && temp[6] == 1 && ((temp[2] || temp[5] || temp[8]) == 1))



					{



						flag = true;



						//break;



					}





					//---



					else   if (temp[4] == 1 && temp[6] == 1 && temp[8] == 1 && ((temp[0] || temp[1] || temp[2]) == 1))



					{



						flag = true;



						//break;



					}





					//--



					else if (temp[2] == 1 && temp[4] == 1 && temp[8] == 1 && ((temp[0] || temp[3] || temp[6]) == 1))



					{



						flag = true;



						//break;



					}









					//Diagonal Branch



					//--



					else if (temp[1] == 1 && temp[2] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[6] == 1 && temp[7] == 0)



					{



						flag = true;



						//break;



					}





					//--



					else  if (temp[0] == 0 && temp[1] == 1 && temp[3] == 1 && temp[4] == 1 && temp[5] == 0 && temp[7] == 0 && temp[8] == 1)



					{



						flag = true;



						//break;



					}





					//--



					else  if (temp[1] == 0 && temp[2] == 1 && temp[3] == 1 && temp[4] == 1 && temp[5] == 0 && temp[6] == 0 && temp[7] == 1)



					{



						flag = true;



						//break;



					}





					//--



					else  if (temp[0] == 1 && temp[1] == 0 && temp[3] == 0 && temp[4] == 1 && temp[5] == 1 && temp[7] == 1 && temp[8] == 0)



					{



						flag = true;



						//break;



					}





					if (flag == true)

					{

						shrunkenimage[r][c] = 1;

					}

					else if (flag == false)

					{

						shrunkenimage[r][c] = 0;

						//  cout<<"shrink"<<'\n';

					}











				}



			}



		}











		for (int i = 0; i<length; i++)



			for (int j = 0; j<breadth; j++)



			{



				Imagedata3D[i][j] = shrunkenimage[i][j];



			}



		for (int i = 1; i<length - 1; i++)

			for (int j = 1; j<breadth - 1; j++)

			{

				if (Imagedata3D[i][j] == 1 && Imagedata3D[i - 1][j - 1] == 0 && Imagedata3D[i - 1][j] == 0 && Imagedata3D[i - 1][j + 1] == 0 && Imagedata3D[i][j - 1] == 0 &&

					Imagedata3D[i][j + 1] == 0 && Imagedata3D[i + 1][j - 1] == 0 && Imagedata3D[i + 1][j] == 0 && Imagedata3D[i + 1][j + 1] == 0)

					counter[numIterations]++;





			}

		//cout<<counter[numIterations]<<endl;





	}



	cout << "no. of stars " << counter[0] << endl;

	for (int i = 0; i<n - 1; i++)

		cout << "no. of stars " << counter[i + 1] - counter[i] << endl;

















	for (int i = 0; i<length; i++) {



		for (int j = 0; j<breadth; j++)



		{



			if (M_Matrix[i][j] == 1) {



				M_Matrix[i][j] = 255;

			}



			if (Imagedata3D[i][j] == 1) {



				Imagedata3D[i][j] = 255;

			}



			if (shrunkenimage[i][j] == 1) {



				shrunkenimage[i][j] = 255;

			}



		}







	}

	//unsigned char* returnImage = convertTo1D(Imagedata3D, length, breadth);

	// Write image data (filename specified by second argument) from image data matrix



	if (!(file = fopen(argv[2], "wb"))) {

		cout << "Cannot open file: " << argv[2] << endl;

		exit(1);

	}

	fwrite(Imagedata3D, sizeof(unsigned char), length*breadth*BytesPerPixel, file);

	fclose(file);

	//cin.get();

	return 0;

}