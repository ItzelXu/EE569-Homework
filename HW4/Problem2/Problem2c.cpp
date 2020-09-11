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

	double** descriptor1 = husky1Input.allocate_2D_Double(128, KeyPtsNum);
	double** descriptor2 = husky2Input.allocate_2D_Double(128, KeyPtsNum);
	double** descriptor3 = husky3Input.allocate_2D_Double(128, KeyPtsNum);
	double** descriptor4 = puppy1Input.allocate_2D_Double(128, KeyPtsNum);

	double** descriptors = husky1Input.allocate_2D_Double(128, 4*KeyPtsNum);

	descriptor1 = husky1Input.imgSift(puppy1Input, KeyPtsNum, 8, false, false);
	descriptor2 = husky2Input.imgSift(husky2Input, KeyPtsNum, 8, false, false);
	descriptor3 = husky3Input.imgSift(husky1Input, KeyPtsNum, 8, false, false);
	descriptor4 = puppy1Input.imgSift(puppy1Input, KeyPtsNum, 8, false, false);

	for (int i = 0; i < 4 * KeyPtsNum; i++)
	{
		if (i < KeyPtsNum)
			descriptors[i] = descriptor1[i];
		else if (i < 2 * KeyPtsNum)
			descriptors[i] = descriptor2[i-KeyPtsNum];
		else if (i < 3 * KeyPtsNum)
			descriptors[i] = descriptor3[i-2*KeyPtsNum];
		else
			descriptors[i] = descriptor4[i-3*KeyPtsNum];
	}

	double** centers = husky1Input.allocate_2D_Double(129, 8);
	centers = husky1Input.KmeansCenter(descriptors, 8, 4*KeyPtsNum, 128);

	int histo1[8] = {0};
	int histo2[8] = {0};
	int histo3[8] = {0};
	int histo4[8] = {0};

	for (int i = 0; i < KeyPtsNum; i++)
	{
		int index = 0;
		double dist = 0;
		double mindist = 9999;
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 128; k++)
				dist += (descriptor1[i][k]-centers[j][k]) * (descriptor1[i][k]-centers[j][k]);
			dist = sqrt(dist);
			if (dist < mindist)
			{
				mindist = dist;
				index = j;
			}
		}
		histo1[index]++;
	}

	for (int i = 0; i < KeyPtsNum; i++)
	{
		int index = 0;
		double dist = 0;
		double mindist = 9999;
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 128; k++)
				dist += (descriptor2[i][k]-centers[j][k]) * (descriptor2[i][k]-centers[j][k]);
			dist = sqrt(dist);
			if (dist < mindist)
			{
				mindist = dist;
				index = j;
			}
		}
		histo2[index]++;
	}

	for (int i = 0; i < KeyPtsNum; i++)
	{
		int index = 0;
		double dist = 0;
		double mindist = 9999;
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 128; k++)
				dist += (descriptor3[i][k]-centers[j][k]) * (descriptor3[i][k]-centers[j][k]);
			dist = sqrt(dist);
			if (dist < mindist)
			{
				mindist = dist;
				index = j;
			}
		}
		histo3[index]++;
	}

	for (int i = 0; i < KeyPtsNum; i++)
	{
		int index = 0;
		double dist = 0;
		double mindist = 9999;
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 128; k++)
				dist += (descriptor4[i][k]-centers[j][k]) * (descriptor4[i][k]-centers[j][k]);
			dist = sqrt(dist);
			if (dist < mindist)
			{
				mindist = dist;
				index = j;
			}
		}
		histo4[index]++;
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