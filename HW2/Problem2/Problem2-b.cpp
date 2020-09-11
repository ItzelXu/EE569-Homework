//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 02/16/2020

#include <iostream>
#include "image.h"

using namespace std;

//Define Matrixes
double filter_FS_ori[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 7.0, 3.0, 5.0, 1.0};
double filter_FS_flp[9] = {0.0, 0.0, 0.0, 7.0, 0.0, 0.0, 1.0, 5.0, 3.0};
double filter_JJN_ori[25] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.0, 5.0, 3.0, 5.0, 7.0, 5.0, 3.0, 1.0, 3.0, 5.0, 3.0, 1.0};
double filter_JJN_flp[25] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0, 7.0, 0.0, 0.0, 0.0, 3.0, 5.0, 7.0, 5.0, 3.0, 1.0, 3.0, 5.0, 3.0, 1.0};
double filter_STK_ori[25] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 8.0, 4.0, 2.0, 4.0, 8.0, 4.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0};
double filter_STK_flp[25] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.0, 8.0, 0.0, 0.0, 0.0, 2.0, 4.0, 8.0, 4.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0};

int main(int argc, char* argv[])
{
	//argv[0] : Program Name
	//argv[1] : File Name
	//argv[2] : Matrix
	//argv[3] : Image Width
	//argv[4] : Image Height
	//argv[5] : Bytes
	//argv[6] : Threshold

	//Default Light Image Size
	int light_width = 750;
	int light_height = 500;
	int bpp = 1;

	//Image File Names
	char matrix = 'F';
	char light_input[50];
	char light_errorFS[50] = "Images/LightHouse_FS.raw";
	char light_errorJN[50] = "Images/LightHouse_JN.raw";
	char light_errorSK[50] = "Images/LightHouse_SK.raw";

	//Multiple Input
	double thresh = 128;	//Default Threshold
	strcpy(light_input, argv[1]);

	if (argc > 2)
		matrix = (char)argv[2][0];

	if (argc > 3)
	{
		light_width = atoi(argv[3]);
		light_height = atoi(argv[4]);
	}
	if (argc > 5)
		bpp = atoi(argv[5]);
	if (argc > 6)
		thresh = atof(argv[5]);

	//Construct the Objects
	Image lightInput(light_width, light_height, bpp, light_input);
	Image lightErrorFS(light_width, light_height, bpp, light_errorFS);
	Image lightErrorJN(light_width, light_height, bpp, light_errorJN);
	Image lightErrorSK(light_width, light_height, bpp, light_errorSK);

	//Initialize Objects
	lightInput.initialize();
	lightErrorFS.initialize();
	lightErrorJN.initialize();
	lightErrorSK.initialize();

	//Read the Input Files
	lightInput.readFile();

	//Check Using Which Matrix
	if (matrix == 'F')
	{
		//Half Toning Floyd-Steinberg
		lightInput.errorDiff(lightErrorFS, thresh, 3, 16, filter_FS_ori, filter_FS_flp);
		//Write Result in File
		lightErrorFS.writeFile();
		return 0;
	}
	else if (matrix == 'J')
	{
		//Half Toning JJN
		lightInput.errorDiff(lightErrorJN, thresh, 5, 48, filter_JJN_ori, filter_JJN_flp);
		//Write Result in File
		lightErrorJN.writeFile();
		return 0;
	}
	else if (matrix == 'S')
	{
		//Half Toning Floyd-Steinberg
		lightInput.errorDiff(lightErrorSK, thresh, 5, 42, filter_STK_ori, filter_STK_flp);
		//Write Result in File
		lightErrorSK.writeFile();
		return 0;
	}
	else
		cout << "The Matrix Choice Can Only be F, J or S." << endl;
}