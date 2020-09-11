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
	int pcbWidth = 372;
	int pcbHeight = 239;
	int bpp = 1;

	//Output Names
	char pcb_input[50] = "Images/PCB.raw";
	char pcb_mask[50] = "Images/PCB_mask.raw";
	char pcb_count[50] = "Images/PCB_count.raw";
	char pcb_reverse[50] = "Images/PCB_reverse.raw";
	char pcb_shrink[50] = "Images/PCB_shrink.raw";
	char pcb_thin[50] = "Images/PCB_thin.raw";
	char pcb_skeleton[50] = "Images/PCB_skeleton.raw";

	//Construct Image Objects
	Image pcbInput(pcbWidth, pcbHeight, bpp, pcb_input);
	Image pcbReverse(pcbWidth, pcbHeight, bpp, pcb_reverse);
	Image pcbMask(pcbWidth, pcbHeight, bpp, pcb_mask);
	Image pcbCount(pcbWidth, pcbHeight, bpp, pcb_count);
	Image pcbShrink(pcbWidth, pcbHeight, bpp, pcb_shrink);
	Image pcbThin(pcbWidth, pcbHeight, bpp, pcb_thin);
	Image pcbSkeleton(pcbWidth, pcbHeight, bpp, pcb_skeleton);

	//Read File
	pcbInput.readFile();


	//Find # of Holes
	pcbInput.imgShrink(pcbMask, pcbShrink, 50);
	pcbShrink.countPoints(pcbInput);

	//Find Path Ways
	pcbInput.imgReverse(pcbReverse, 50);
	pcbReverse.writeFile();
	pcbReverse.imgThin(pcbMask, pcbThin, 128);
	pcbThin.imgConnect(pcbCount, 128, 50, false);

	//Write File
	pcbShrink.writeFile();
	pcbThin.writeFile();
	pcbCount.writeFile();
}