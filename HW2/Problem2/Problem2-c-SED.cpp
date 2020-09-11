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
	int rose_width = 640;
	int rose_height = 480;
	int bpp = 3;

	//Image File Names
	char matrix = 'F';
	char rose_input[50];
	char rose_errorFS[50] = "Images/Rose_FS.raw";
	char rose_errorJN[50] = "Images/Rose_JN.raw";
	char rose_errorSK[50] = "Images/Rose_SK.raw";

	//Multiple Input
	double thresh = 128;	//Default Threshold
	strcpy(rose_input, argv[1]);

	if (argc > 2)
		matrix = (char)argv[2][0];

	if (argc > 3)
	{
		rose_width = atoi(argv[3]);
		rose_height = atoi(argv[4]);
	}
	if (argc > 5)
		bpp = atoi(argv[5]);
	if (argc > 6)
		thresh = atof(argv[6]);

	//Construct the Objects
	Image roseInput(rose_width, rose_height, bpp, rose_input);
	Image roseColorFS(rose_width, rose_height, bpp, rose_errorFS);
	Image roseColorJN(rose_width, rose_height, bpp, rose_errorJN);
	Image roseColorSK(rose_width, rose_height, bpp, rose_errorSK);

	//Initialize Objects
	roseInput.initialize();
	roseColorFS.initialize();
	roseColorJN.initialize();
	roseColorSK.initialize();

	//Read the Input Files
	roseInput.readFile();

	//Check Using Which Matrix
	if (matrix == 'F')
	{
		//Half Toning Floyd-Steinberg
		roseInput.transferSpaces(roseInput);
		roseInput.errorDiff(roseColorFS, thresh, 3, 16, filter_FS_ori, filter_FS_flp);
		roseColorFS.transferSpaces(roseColorFS);
		//Write Result in File
		roseColorFS.writeFile();
		return 0;
	}
	else if (matrix == 'J')
	{
		//Half Toning JJN
		roseInput.transferSpaces(roseInput);
		roseInput.errorDiff(roseColorJN, thresh, 5, 48, filter_JJN_ori, filter_JJN_flp);
		roseColorJN.transferSpaces(roseColorJN);
		//Write Result in File
		roseColorJN.writeFile();
		return 0;
	}
	else if (matrix == 'S')
	{
		//Half Toning Floyd-Steinberg
		roseInput.transferSpaces(roseInput);
		roseInput.errorDiff(roseColorSK, thresh, 5, 42, filter_STK_ori, filter_STK_flp);
		roseColorSK.transferSpaces(roseColorSK);
		//Write Result in File
		roseColorSK.writeFile();
		return 0;
	}
	else
		cout << "The Matrix Choice Can Only be F, J or S." << endl;
}