//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 01/28/2020

#include <iostream>
#include "image.h"

using namespace std;

int main(int argc, char* argv[])
{
	//argv[0] : Program Name
	//argv[1] : File Name
	//argv[2] : Image Width
	//argv[3] : Image Height
	//argv[4] : Bytes

	//Default Dog Size
	int toy_width = 400;
	int toy_height = 560;
	int bpp = 3;

	//Image File Names
	char toy_input[256];
	char toy_equalizedA[50] = "Images/Toy_equalizedA.raw";

	//Multiple Input
	strcpy(toy_input, argv[1]);

	if (argc > 2)
	{
		toy_width = atoi(argv[2]);
		toy_height = atoi(argv[3]);
	}
	if (argc > 4)
		bpp = atoi(argv[4]);

	//Construct Objects
	Image toyInput(toy_width, toy_height, bpp, toy_input);
	Image toyEqualizedA(toy_width, toy_height, bpp, toy_equalizedA);

	//Initialize Objects
	toyInput.initialize();
	toyEqualizedA.initialize();

	//Read the Input Files
	toyInput.readFile();

	//Get the Histogram of the Toy Image and Do the Job of Equalization
	toyInput.imgHistoRGB('O'); // 'O' means original
	toyInput.imgHistoTransfer(toyEqualizedA);

	//Write Results in Files
	toyEqualizedA.writeFile();
}