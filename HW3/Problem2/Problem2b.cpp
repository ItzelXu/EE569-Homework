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
	int starWidth = 640;
	int starHeight = 480;
	int bpp = 1;

	//Output Names
	char star_input[50] = "Images/stars.raw";
	char star_mask[50] = "Images/stars_mask.raw";
	char star_count[50] = "Images/stars_count.raw";
	char star_shrink[50] = "Images/stars_shrink.raw";
	char star_thin[50] = "Images/stars_thin.raw";
	char star_skeleton[50] = "Images/stars_skeleton.raw";

	//Construct Image Objects
	Image starInput(starWidth, starHeight, bpp, star_input);
	Image starMask(starWidth, starHeight, bpp, star_mask);
	Image starCount(starWidth, starHeight, bpp, star_count);
	Image starShrink(starWidth, starHeight, bpp, star_shrink);
	Image starThin(starWidth, starHeight, bpp, star_thin);
	Image starSkeleton(starWidth, starHeight, bpp, star_skeleton);

	//Read File
	starInput.readFile();

	//Do the Counting Job
	starInput.imgShrink(starMask, starShrink, 128);
	starInput.imgConnect(starCount, 128, 1, true);
	starInput.countStar(starShrink);

	//Write File
	starShrink.writeFile();
	starCount.writeFile();
}