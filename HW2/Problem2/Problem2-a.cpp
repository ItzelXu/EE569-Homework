//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 02/16/2020

#include <iostream>
#include <math.h>
#include "image.h"

using namespace std;

int main(int argc, char* argv[])
{
	//argv[0] : Program Name
	//argv[1] : File Name
	//argv[2] : Methods
	//argv[3] : Image Width
	//argv[4] : Image Height
	//argv[5] : Bytes
	//argv[6] : Threshold / Random Seed / Matrix Width

	//Default Light Image Size
	int light_width = 750;
	int light_height = 500;
	int bpp = 1;

	//Image File Names
	char method = 'F';
	char light_input[50];
	char light_fixed[50] = "Images/LightHouse_Fixed.raw";
	char light_random[50] = "Images/LightHouse_Random.raw";
	char light_matrix[50] = "Images/LightHouse_Matrix__.raw";

	//Multiple Input
	unsigned char thresh = 128;	//Default Threshold
	unsigned char tSeed = 5;	//Default Time Seed
	int N = 2;	//Default Matrix Width

	strcpy(light_input, argv[1]);

	if (argc > 2)
		method = (char)argv[2][0];

	if (argc > 3)
	{
		light_width = atoi(argv[3]);
		light_height = atoi(argv[4]);
	}
	if (argc > 5)
		bpp = atoi(argv[5]);

	if (argc > 6)
	{
		if (method == 'F') 
			thresh = (unsigned char)atoi(argv[6]);
		else if (method == 'R')
			tSeed = (unsigned char)atoi(argv[6]);
		else if (method == 'M')
		{
			N = atoi(argv[6]);
			light_matrix[25] = '0' + log2(N);
		}
		else
		{
			cout << "The Matrix Choice Can Only be F, R or M." << endl;
			return 0;
		}
	}

	//Construct the Objects
	Image lightInput(light_width, light_height, bpp, light_input);
	Image lightFixed(light_width, light_height, bpp, light_fixed);
	Image lightRandom(light_width, light_height, bpp, light_random);
	Image lightMatrix(light_width, light_height, bpp, light_matrix);

	//Initialize Objects
	lightInput.initialize();
	lightFixed.initialize();
	lightRandom.initialize();
	lightMatrix.initialize();

	//Read the Input Files
	lightInput.readFile();

	if (method == 'F')
	{
		//Half Toning Fixed Thresh
		lightInput.toneFixed(lightFixed, thresh);
		//Write Result in File
		lightFixed.writeFile();
		return 0;
	}
	else if (method == 'R')
	{
		//Half Toning Random Thresh
		lightInput.toneRand(lightRandom, tSeed);
		//Write Result in File
		lightRandom.writeFile();
		return 0;
	}
	else if (method == 'M')
	{
		//Half Toning Dithering Matrix 
		lightInput.toneDither(lightMatrix, N);
		//Write Result in File
		lightMatrix.writeFile();
		return 0;
	}
	else
	{
		cout << "The Matrix Choice Can Only be F, R or M." << endl;
		return 0;
	}
}