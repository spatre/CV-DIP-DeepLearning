#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "myHeader.h"

using namespace std;


double Imagedata_Out[400][600][9] = { 0 };
double Imagedata_extend[400 + 12][600 + 12][9] = { 0 };
double Imagedata_extend_Out[400][600][9] = { 0 };
double Imagedata_target[400][600][9] = { 0 };
int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int bytesPerPixel = 1;
	const int height = 400;
	const int width = 600;
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
	int i, j, k, a, b, c, d;
	const int N = 3; // Window Size
	const int n = (N - 1) / 2; // Padding parameter
	const int disp = 2 * n;//Number of extra rows and columns to be added
	unsigned char Imagedata_Big[height + disp][width + disp][bytesPerPixel] = { 0 };
	unsigned char Imagedata_Pad[height + disp][width + disp][bytesPerPixel] = { 0 };
	
	//unsigned char Imagedata_final[height][width][bytesPerPixel] = { 0 };
	double filterBank[3][3][9] = { 0 };
	double filter_conv[3][3][9] = { 0 };
	double E3[3] = {-1,0,1};
	double S3[3] = {-1,2,-1};
	double L3[3] = {1,2,1};

	double** E3_E3 = tensor_Prod_3D(E3, E3);
	double** E3_S3 = tensor_Prod_3D(E3, S3);
	double** E3_L3 = tensor_Prod_3D(E3, L3);
	double** S3_E3 = tensor_Prod_3D(S3, E3);
	double** S3_S3 = tensor_Prod_3D(S3, S3);
	double** S3_L3 = tensor_Prod_3D(S3, L3);
	double** L3_E3 = tensor_Prod_3D(L3, E3);
	double** L3_S3 = tensor_Prod_3D(L3, S3);
	double** L3_L3 = tensor_Prod_3D(L3, L3);


	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j <3; j++)
	//	{
	//		cout << E3_E3[i][j] << endl;

	//	}
	//	//cout << endl;
	//}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][0] = E3_E3[i][j];
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][1] = E3_S3[i][j];
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][2] = E3_L3[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][3] = S3_E3[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][4] = S3_S3[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][5] = S3_L3[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][6] = L3_E3[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][7] = L3_S3[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			filterBank[i][j][8] = L3_L3[i][j];
		}
	}

	// Image Processing code starts here
	// Padding the image
	for (i = n; i < height + n; i++)
	{
		for (j = n; j < width + n; j++)
		{
			Imagedata_Pad[i][j][0] = Imagedata[i - n][j - n][0];
		}
	}


	// Inverting the filter bank for convolution
	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				filter_conv[i][j][k] = filterBank[3 - i - 1][3 - j - 1][k];
			}
		}
	}
	for (k = 0; k < 9; k++)
	{
		for (a = n; a < height + n; a++)
		{
			for (b = n; b < width + n; b++)
			{
				double sum = 0;
				for (c = a - n; c <= a + n; c++)
				{
					for (d = b - n; d <= b + n; d++)
					{
						sum = sum + (double)Imagedata_Pad[c][d][0] * filter_conv[c%N][d%N][k];
					}
				}
				Imagedata_Out[a-n][b-n][k] = sum;
				
			}
		}
		
	}





	//Padding the final image
	const int M = 13; // Window Size
	const int m = (M - 1) / 2; // Padding parameter
	const int ext = 2 * m;//Number of extra rows and columns to be added
	
	for (k = 0; k < 9; k++)
	{
		for (i = m; i < height + m; i++)
		{
			for (j = m; j < width + m; j++)
			{
				Imagedata_extend[i][j][k] = Imagedata_Out[i - m][j - m][k];
			}
		}
	}


	//Copying the padded rows and columns with the Image row and column data
	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < m; i++)
		{
			for (j = m; j < width + m; j++)
			{
				Imagedata_extend[i][j][k] = Imagedata_extend[m][j][k];
			}
		}
	}
	for (k = 0; k < 9; k++)
	{
		for (i = height + m; i < height + ext; i++)
		{
			for (j = m; j < width + m; j++)
			{
				Imagedata_extend[i][j][k] = Imagedata_extend[height + m - 1][j][k];
			}
		}
	}
	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < height + ext; i++)
		{
			for (j = 0; j < m; j++)
			{
				Imagedata_extend[i][j][k] = Imagedata_extend[i][m][k];
			}
		}
	}

	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < height + ext; i++)
		{
			for (j = width + m; j < width + ext; j++)
			{
				Imagedata_extend[i][j][k] = Imagedata_extend[i][width + m - 1][k];
			}
		}
	}




	for (k = 0; k < 9; k++)
	{
		for (a = m; a < height + m; a++)
		{
			for (b = m; b < width + m; b++)
			{
				double summer = 0;
					for (c = a - m; c <= a + m; c++)
					{
						for (d = b - m; d <= b + m; d++)
						{
							
							summer += Imagedata_extend[c][d][k] * Imagedata_extend[c][d][k];

						}

					}
					
					Imagedata_extend_Out[a - m][b - m][k] = summer / (double)(M*M);

				
			}
		}
	}


	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			for (k = 0; k < 9; k++)
			{
				Imagedata_target[i][j][k] = Imagedata_extend_Out[i][j][k] / Imagedata_extend_Out[i][j][8];
			}
		}
	}









	//// To calculate the average energy for the image to obtain the feature vector
	//double featureVector[9] = { 0 };
	//for (k = 0; k < 9; k++)
	//{
	//	int val = 0;
	//	double energy = 0;
	//	for (i = 0; i < height; i++)
	//	{
	//		for (j = 0; j < width; j++)
	//		{
	//			val = val + (int)Imagedata_Out[i][j][k] * (int)Imagedata_Out[i][j][k];
	//		}
	//	}
	//	energy = (double)val / (double)(height*width);
	//	featureVector[k] = energy;
	//}

	//for (k = 0; k < 9; k++)
	//{
	//	cout << featureVector[k] << endl;
	//}
	//for (i = 0; i < height; i++)
	//{
	//	for (j = 0; j < width; j++)
	//	{
	//		Imagedata_final[i][j][0] = Imagedata_Out[i][j][8];
	//	}
	//}



	
		for (int k = 0; k<9; k++)
		{
			cout << Imagedata_target[593][393][k] << endl;

		}
		//cout << endl;
	



		double centroid[4][9] = { { 27744.4,26993.2,28092.5,27433.2,27091.1,29012.5,28199.6,29108,26716.3 },
		{ 26519.7,25244,23144.8,25057.3,28310,25892,22266.9,24885.6,20372.6 },
		{ 23082.7,23099,18810.3,23920.8,25190.6,20034,19025.8,20995.9,15211.7 },
		{ 15665,16319.9,10632.9,16989.2,19867.7,13251.6,10647.2,13099.5,7620.16 } };

		double feature_vector[12][9] = { { 27744.4,26993.2,28092.5,27433.2,27091.1,29012.5,28199.6,29108,26716.3 },
		{ 26519.7,25244,23144.8,25057.3,28310,25892,22266.9,24885.6,20372.6 },
		{ 23082.7,23099,18810.3,23920.8,25190.6,20034,19025.8,20995.9,15211.7 },
		{ 28853.5,28895.9,27679.2,28925.2,27408.2,27166.8,27410.2,27778.7,27576.2 },
		{ 23917.5,24124.1,20678.8,24414.7,25948.5,21399.4,21204.4,23005.6,15958.1 },
		{ 28491.1,28270.3,28107.7,27135.8,28253.1,28434,27420,27946.1,27427.3 },
		{ 15665,16319.9,10632.9,16989.2,19867.7,13251.6,10647.2,13099.5,7620.16 },
		{ 14537.2,17591,12626.1,17684.8,17983.8,12962.2,12561.5,13576.3,7167.75 },
		{ 26380.5,28047,23655.2,26575.3,27316.1,24361,23403.9,23551.8,21473.1 },
		{ 14609.4,16024.5,7038.19,15262.6,17489.3,9325.27,8646.25,10387.3,3847.92 },
		{ 21301.3,22711.9,17590.7,22592.8,22954.5,18880,16884.1,17096.8,11890.5 },
		{ 26380.5,28047,23655.2,26575.3,27316.1,24361,23403.9,23551.8,21473.1 } };


		bool classified = false;

		while (classified == false)
		{
			int label[12] = { 0 };
			for (k = 0; k < 12; k++)
			{
				double minval = (double)INT_MAX;
				double fv[9] = { 0.0 };
				for (i = 0; i < 9; i++)
				{
					fv[i] = feature_vector[k][i];
				}
				for (j = 0; j < 4; j++)
				{
					double c[9] = { 0.0 };
					for (a = 0; a < 9; a++)
					{
						c[a] = centroid[j][a];
					}
					double dist = distance(fv, c);

					if (dist < minval)
					{
						minval = dist;
						label[k] = j + 1;

					}


				}
			}

			double new_Centroid[4][9] = { 0.0 };

			int cluster_1[3] = { 0 };
			int cluster_2[3] = { 0 };
			int cluster_3[3] = { 0 };
			int cluster_4[3] = { 0 };

			int x1 = 0, x2 = 0, x3 = 0, x4 = 0;
			for (i = 0; i < 12; i++)
			{
				if (label[i] == 1)
				{
					cluster_1[x1] = i;
					x1 += 1;
				}
				if (label[i] == 2)
				{
					cluster_2[x2] = i;
					x2 += 1;
				}
				if (label[i] == 3)
				{
					cluster_3[x3] = i;
					x3 += 1;
				}
				if (label[i] == 4)
				{
					cluster_4[x4] = i;
					x4 += 1;
				}
			}

			/*for (i = 0; i < 3; i++)
			{
			cout << cluster_1[i] << " " << cluster_2[i] << " " << cluster_3[i] << " " << cluster_4[i] << endl;
			}*/


			for (i = 0; i < 9; i++)
			{
				new_Centroid[0][i] = (feature_vector[cluster_1[0]][i] + feature_vector[cluster_1[1]][i] + feature_vector[cluster_1[2]][i]) / 3.0;

				new_Centroid[1][i] = (feature_vector[cluster_2[0]][i] + feature_vector[cluster_2[1]][i] + feature_vector[cluster_2[2]][i]) / 3.0;

				new_Centroid[2][i] = (feature_vector[cluster_3[0]][i] + feature_vector[cluster_3[1]][i] + feature_vector[cluster_3[2]][i]) / 3.0;

				new_Centroid[3][i] = (feature_vector[cluster_4[0]][i] + feature_vector[cluster_4[1]][i] + feature_vector[cluster_4[2]][i]) / 3.0;

			}

			int count = 0;
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 9; j++)
				{

					if (centroid[i][j] - new_Centroid[i][j] == 0)
					{
						count += 1;
					}
				}
			}
			//	cout << "count: " << count << endl;
			if (count == 36)
			{
				classified = true;
				


				cout << "1 =" << cluster_1[0] + 1 << " " << cluster_1[1] + 1 << " " << cluster_1[2] + 1 << endl;
				cout << "2 =" << cluster_2[0] + 1 << " " << cluster_2[1] + 1 << " " << cluster_2[2] + 1 << endl;
				cout << "3 =" << cluster_3[0] + 1 << " " << cluster_3[1] + 1 << " " << cluster_3[2] + 1 << endl;
				cout << "4 =" << cluster_4[0] + 1 << " " << cluster_4[1] + 1 << " " << cluster_4[2] + 1 << endl;

			}

			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 9; j++)
				{
					centroid[i][j] = new_Centroid[i][j];

				}
			}
		}



	//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		cout << Imagedata_target[i][j][8] << endl;

	//	}
	//	//cout << endl;
	//}
	cin.get();
	

	//// Write image data (filename specified by second argument) from image data matrix
	//if (!(file = fopen(argv[2], "wb"))) {
	//	cout << "Cannot open file: " << argv[2] << endl;
	//	exit(1);
	//}
	//fwrite(Imagedata_Out, sizeof(unsigned char), height*width*bytesPerPixel, file);
	//fclose(file);

	return 0;
}