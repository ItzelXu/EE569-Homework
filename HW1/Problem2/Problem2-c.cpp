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
	//argv[5] : Compare Window Size
	//argv[6] : Search Window Size
	//argv[7] : h
	//argv[8] : Sigma

	//Default Corn Size
	int corn_width = 320;
	int corn_height = 320;
	int bpp = 1;

	//Default Window Sizes and Sigmas
	int compare_window = 5;
	int search_window = 7;
	double h = 30;
	double sigma = 1.0;

	//Image File Names
	char corn_input[256];
	char corn_origin[50] = "Images/Corn_gray.raw";
	char corn_denoiseNLM[50] = "Images/Corn_NLM.raw";

	//Multiple Input
	strcpy(corn_input, argv[1]);
	//Image Parameter
	if (argc > 2)
	{
		corn_width = atoi(argv[2]);
		corn_height = atoi(argv[3]);
	}
	if (argc > 4)
		bpp = atoi(argv[4]);

	//Compare Window Size
	if (argc > 5)
		compare_window = atoi(argv[5]);

	//Search Window Size
	if (argc > 6)
		search_window = atoi(argv[6]);

	//h Value
	if (argc > 7)
		h = atof(argv[7]);

	//Sigma Value
	if (argc > 8)
		sigma = atof(argv[8]);

	//Construct Objects
	Image cornInput(corn_width, corn_height, bpp, corn_input);
	Image cornOringin(corn_width, corn_height, bpp, corn_origin);
	Image cornDenoiseNLM(corn_width, corn_height, bpp, corn_denoiseNLM);

	//Initialize Objects
	cornInput.initialize();
	cornOringin.initialize();
	cornDenoiseNLM.initialize();

	//Read the Input Files
	cornInput.readFile();
	cornOringin.readFile();

	//Noisy PSNR
	cornInput.imgPSNR(cornOringin);

	//Denoising
	cornInput.imgDenoiseNLM(cornDenoiseNLM, compare_window, search_window, h, sigma);

	//Compute the PSNR value
	cornDenoiseNLM.imgPSNR(cornOringin);

	//Write Results in Files
	cornDenoiseNLM.writeFile();
}