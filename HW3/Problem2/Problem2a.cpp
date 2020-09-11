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
	int imageWidth = 558;
	int imageHeight = 558;
	int cupWidth = 315;
	int cupHeight = 356;

	int bpp = 1;

	//File Names Definition
	char cup_input[50] = "Images/cup.raw";
	char fan_input[50] = "Images/fan.raw";
	char maze_input[50] = "Images/maze.raw";

	char cup_mask[50] = "Images/cup_mask.raw";
	char cup_shrink[50] = "Images/cup_shrink.raw";
	char cup_thin[50] = "Images/cup_thin.raw";
	char cup_skeleton[50] = "Images/cup_skeleton.raw";

	char fan_mask[50] = "Images/fan_mask.raw";
	char fan_shrink[50] = "Images/fan_shrink.raw";
	char fan_thin[50] = "Images/fan_thin.raw";
	char fan_skeleton[50] = "Images/fan_skeleton.raw";

	char maze_mask[50] = "Images/maze_mask.raw";
	char maze_shrink[50] = "Images/maze_shrink.raw";
	char maze_thin[50] = "Images/maze_thin.raw";
	char maze_skeleton[50] = "Images/maze_skeleton.raw";

	//Construct the Objects
	Image cupInput(cupWidth, cupHeight, bpp, cup_input);
	Image fanInput(imageWidth, imageHeight, bpp, fan_input);
	Image mazeInput(imageWidth, imageHeight, bpp, maze_input);

	Image cupMask(cupWidth, cupHeight, bpp, cup_mask);
	Image cupShrink(cupWidth, cupHeight, bpp, cup_shrink);
	Image cupThin(cupWidth, cupHeight, bpp, cup_thin);
	Image cupSkeleton(cupWidth, cupHeight, bpp, cup_skeleton);

	Image fanMask(imageWidth, imageHeight, bpp, fan_mask);
	Image fanShrink(imageWidth, imageHeight, bpp, fan_shrink);
	Image fanThin(imageWidth, imageHeight, bpp, fan_thin);
	Image fanSkeleton(imageWidth, imageHeight, bpp, fan_skeleton);

	Image mazeMask(imageWidth, imageHeight, bpp, maze_mask);
	Image mazeShrink(imageWidth, imageHeight, bpp, maze_shrink);
	Image mazeThin(imageWidth, imageHeight, bpp, maze_thin);
	Image mazeSkeleton(imageWidth, imageHeight, bpp, maze_skeleton);

	//Initialize Objects
	cupInput.initialize();
	fanInput.initialize();
	mazeInput.initialize();

	cupMask.initialize();
	cupShrink.initialize();
	cupThin.initialize();
	cupSkeleton.initialize();

	fanMask.initialize();
	fanShrink.initialize();
	fanThin.initialize();
	fanSkeleton.initialize();

	mazeMask.initialize();
	mazeShrink.initialize();
	mazeThin.initialize();
	mazeSkeleton.initialize();

	//Read the Input Files
	cupInput.readFile();
	fanInput.readFile();
	mazeInput.readFile();

	//Do the Shrinking Job
	cupInput.imgShrink(cupMask, cupShrink, 128);
	fanInput.imgShrink(fanMask, fanShrink, 128);
	mazeInput.imgShrink(mazeMask, mazeShrink, 128);

	//Do the Thinning Job
	cupInput.imgThin(cupMask, cupThin, 128);
	fanInput.imgThin(fanMask, fanThin, 128);
	mazeInput.imgThin(mazeMask, mazeThin, 128);

	//Do the Skeletonizing Job
	cupInput.imgSkeleton(cupMask, cupSkeleton, 128);
	fanInput.imgSkeleton(fanMask, fanSkeleton, 128);
	mazeInput.imgSkeleton(mazeMask, mazeSkeleton, 128);

	//Write File
	fanShrink.writeFile();
	cupShrink.writeFile();
	mazeShrink.writeFile();

	cupThin.writeFile();
	fanThin.writeFile();
	mazeThin.writeFile();

	cupSkeleton.writeFile();
	fanSkeleton.writeFile();
	mazeSkeleton.writeFile();

	return 0;
}