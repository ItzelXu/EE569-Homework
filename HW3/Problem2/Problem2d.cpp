//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/03/2020

#include <iostream>
#include "image.h"

using namespace std;

int main()
{
	//Define the Size the Gallery Image
	int gearWidth = 250;
	int gearHeight = 250;
	int bpp = 1;

	//Output Names
	char gear_input[50] = "Images/Geartooth.raw";
	char gear_mask[50] = "Images/Geartooth_mask.raw";
	char gear_reverse[50] = "Images/Geartooth_reverse.raw";
	char gear_shrink[50] = "Images/Geartooth_shrink.raw";
	char gear_thin[50] = "Images/Geartooth_thin.raw";
	char gear_skeleton[50] = "Images/Geartooth_skeleton.raw";
	char gear_miss[50] = "Images/Geartooth_miss.raw";

	//Construct Image Objects
	Image gearInput(gearWidth, gearHeight, bpp, gear_input);
	Image gearReverse(gearWidth, gearHeight, bpp, gear_reverse);
	Image gearMask(gearWidth, gearHeight, bpp, gear_mask);
	Image gearShrink(gearWidth, gearHeight, bpp, gear_shrink);
	Image gearThin(gearWidth, gearHeight, bpp, gear_thin);
	Image gearSkeleton(gearWidth, gearHeight, bpp, gear_skeleton);
	Image gearMiss(gearWidth, gearHeight, bpp, gear_miss);

	//Read File
	gearInput.readFile();

	//Analyze the Geaer
	//Reverse the Image
	gearInput.imgReverse(gearReverse, 128);
	//Shrink the Reverse Image
	gearReverse.imgShrink(gearMask, gearShrink, 128);
	gearInput.imgThin(gearMask, gearThin, 50);
	//Analyze the Gear
	gearShrink.analyzeGear(gearInput, gearReverse, gearMiss, gearThin);

	//Write File
	gearReverse.writeFile();
	gearShrink.writeFile();
	gearThin.writeFile();
	gearMiss.writeFile();
}