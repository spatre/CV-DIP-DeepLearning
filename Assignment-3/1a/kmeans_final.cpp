#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include "myHeader.h"

using namespace std;

int main(int argc, char *argv[])

{

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int i, j, k,a, b, c, d;


	double centroid[4][9] = { { 27744.4,26993.2,28092.5,27433.2,27091.1,29012.5,28199.6,29108,26716.3},
								{ 26519.7,25244,23144.8,25057.3,28310,25892,22266.9,24885.6,20372.6},
								{ 23082.7,23099,18810.3,23920.8,25190.6,20034,19025.8,20995.9,15211.7},
								{ 15665,16319.9,10632.9,16989.2,19867.7,13251.6,10647.2,13099.5,7620.16} };

		double feature_vector[12][9] = { {27744.4,26993.2,28092.5,27433.2,27091.1,29012.5,28199.6,29108,26716.3},
									{ 26519.7,25244,23144.8,25057.3,28310,25892,22266.9,24885.6,20372.6},
									{ 23082.7,23099,18810.3,23920.8,25190.6,20034,19025.8,20995.9,15211.7},
									{ 28853.5,28895.9,27679.2,28925.2,27408.2,27166.8,27410.2,27778.7,27576.2},
									{ 23917.5,24124.1,20678.8,24414.7,25948.5,21399.4,21204.4,23005.6,15958.1},
									{ 28491.1,28270.3,28107.7,27135.8,28253.1,28434,27420,27946.1,27427.3},
									{ 15665,16319.9,10632.9,16989.2,19867.7,13251.6,10647.2,13099.5,7620.16},
									{ 14537.2,17591,12626.1,17684.8,17983.8,12962.2,12561.5,13576.3,7167.75},
									{ 26380.5,28047,23655.2,26575.3,27316.1,24361,23403.9,23551.8,21473.1},
									{ 14609.4,16024.5,7038.19,15262.6,17489.3,9325.27,8646.25,10387.3,3847.92},
									{21301.3,22711.9,17590.7,22592.8,22954.5,18880,16884.1,17096.8,11890.5},
									{ 26380.5,28047,23655.2,26575.3,27316.1,24361,23403.9,23551.8,21473.1} };


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
				cout << " Texture Classification using Kmeans Algorithm" << endl;
				
					
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

		
		cout << " Texture Classification by Visual Inspection" << endl;
		cout << "1 ==" << "1 4 6"<< endl;
		cout << "2 ==" << "2 9 12"<< endl;
		cout << "3 ==" << "3 5 11"<< endl;
		cout << "4 ==" << "7 8 10"<< endl;

		cout << " Cluster label definitions are as below" << endl;
		cout << "1 is" << "ROCK" << endl;
		cout << "2 is" << "GRASS" << endl;
		cout << "3 is" << "WEAVE" << endl;
		cout << "4 is" << "SAND" << endl;
			
			//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		cout << (int)Imagedata_Out[i][j][0] << endl;

	//	}
	//	//cout << endl;
	//}
	cin.get();

	// Write image data (filename specified by second argument) from image data matrix
	/*if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_final, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);*/

	return 0;
}