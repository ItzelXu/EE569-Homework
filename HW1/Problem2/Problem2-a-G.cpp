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
	//argv[5] : Window Size
	//argv[6] : Sigma

	//Default Corn Size
	int corn_width = 320;
	int corn_height = 320;
	int bpp = 1;

	//Default Window Size and Sigma
	int window_size = 5;
	double sigma = 1.0;

	//Image File Names
	char corn_input[256];
	char corn_origin[50] = "Images/Corn_gray.raw";
	char corn_denoiseLFG[50] = "Images/Corn_LFG.raw";

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

	//Window Size
	if (argc > 5)
		window_size = atoi(argv[5]);

	//Sigma Value
	if (argc > 6)
		sigma = atof(argv[6]);

	//Construct Objects
	Image cornInput(corn_width, corn_height, bpp, corn_input);
	Image cornOringin(corn_width, corn_height, bpp, corn_origin);
	Image cornDenoiseLFG(corn_width, corn_height, bpp, corn_denoiseLFG);

	//Initialize Objects
	cornInput.initialize();
	cornOringin.initialize();
	cornDenoiseLFG.initialize();

	//Read the Input Files
	cornInput.readFile();
	cornOringin.readFile();

	//Noisy PSNR
	cornInput.imgPSNR(cornOringin);

	//Denoising
	cornInput.imgDenoiseLFG(cornDenoiseLFG, window_size, sigma);

	//Compute the PSNR value
	cornDenoiseLFG.imgPSNR(cornOringin);

	//Write Results in Files
	cornDenoiseLFG.writeFile();
}