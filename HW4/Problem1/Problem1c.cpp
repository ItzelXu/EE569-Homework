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
	int imageWidth = 600;
	int imageHeight = 450;
	int bpp = 1;

	//File Names Definition
	char comp_input[50] = "Images/comp.raw";
	char seg_input1[50] = "Images/result_3D.raw";
	char seg_input2[50] = "Images/result_14D.raw";

	//Object Definition
	Image compInput(imageWidth, imageHeight, bpp, comp_input);
	Image compSegm1(imageWidth, imageHeight, 1, seg_input1);
	Image compSegm2(imageWidth, imageHeight, 1, seg_input2);

	//Initialization
	compInput.initialize();
	compSegm1.initialize();
	compSegm2.initialize();

	//Read File
	compInput.readFile();

	//Segmentation
	compInput.imgSegment(compSegm1, 41, 6, true);
	compInput.imgSegment(compSegm2, 41, 6, false);
	
	return 0;
}
