//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/22/2020

#include <iostream>
#include "image.h"

using namespace std;

int main()
{
	//Define the Size the Gallery Image
	int imageWidth = 640;
	int imageHeight = 420;
	int bpp = 3;

	//File Names Definition
	char husky1_input[50] = "Images/Husky_1.jpg";
	char husky2_input[50] = "Images/Husky_2.jpg";
	char husky3_input[50] = "Images/Husky_3.jpg";
	char puppy1_input[50] = "Images/Puppy_1.jpg";

	//Object Definition
	Image husky1Input(imageWidth, imageHeight, bpp, husky1_input);
	Image husky2Input(imageWidth, imageHeight, bpp, husky2_input);
	Image husky3Input(imageWidth, imageHeight, bpp, husky3_input);
	Image puppy1Input(imageWidth, imageHeight, bpp, puppy1_input);

	//Initialization
	husky1Input.initialize();
	husky2Input.initialize();
	husky3Input.initialize();
	puppy1Input.initialize();

	//Get Codebooks
	int KeyPtsNum = 100;

	double** centroids1 = husky1Input.allocate_2D_Double(129, 8);
	double** centroids2 = husky2Input.allocate_2D_Double(129, 8);
	double** centroids3 = husky3Input.allocate_2D_Double(129, 8);
	double** centroids4 = puppy1Input.allocate_2D_Double(129, 8);

	centroids1 = husky1Input.imgSift(puppy1Input, KeyPtsNum, 8, false, true);//Change the false Parameter if Want to View the results
	centroids2 = husky2Input.imgSift(husky2Input, KeyPtsNum, 8, false, true);//Change the false Parameter if Want to View the results
	centroids3 = husky3Input.imgSift(husky1Input, KeyPtsNum, 8, false, true);//Change the false Parameter if Want to View the results
	centroids4 = puppy1Input.imgSift(puppy1Input, KeyPtsNum, 8, false, true);//Change the false Parameter if Want to View the results

	centroids1 = husky1Input.sortCentroids(centroids1, centroids3, 8, 128);
	centroids2 = husky1Input.sortCentroids(centroids2, centroids3, 8, 128);
	centroids3 = husky1Input.sortCentroids(centroids3, centroids3, 8, 128);
	centroids4 = husky1Input.sortCentroids(centroids4, centroids3, 8, 128);

	int histo1[8] = {0};
	int histo2[8] = {0};
	int histo3[8] = {0};
	int histo4[8] = {0};

	for (int i = 0; i < 8; i++)
	{
		histo1[i] = (int)centroids1[i][128];
		histo2[i] = (int)centroids2[i][128];
		histo3[i] = (int)centroids3[i][128];
		histo4[i] = (int)centroids4[i][128];
	}
	for (int i = 0; i < 8; i++)
		cout << histo1[i] << "  ";
	cout << endl;
	for (int i = 0; i < 8; i++)
		cout << histo2[i] << "  ";
	cout << endl;
	for (int i = 0; i < 8; i++)
		cout << histo3[i] << "  ";
	cout << endl;
	for (int i = 0; i < 8; i++)
		cout << histo4[i] << "  ";
	cout << endl;

	int intersect1 = husky1Input.histIntersect(histo1, histo3, 8);
	int intersect2 = husky1Input.histIntersect(histo2, histo3, 8);
	int intersect3 = husky1Input.histIntersect(histo3, histo3, 8);
	int intersect4 = husky1Input.histIntersect(histo4, histo3, 8);

	cout << (double)intersect1 / KeyPtsNum * 100 << "%" <<endl;
	cout << (double)intersect2 / KeyPtsNum * 100 << "%" <<endl;
	cout << (double)intersect3 / KeyPtsNum * 100 << "%" <<endl;
	cout << (double)intersect4 / KeyPtsNum * 100 << "%" <<endl;
	return 0;
}












