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
	//argv[6] : Sigmac
	//argv[7] : Sigmas

	//Default Corn Size
	int corn_width = 320;
	int corn_height = 320;
	int bpp = 1;

	//Default Window Size and Sigmas
	int window_size = 5;
	double sigmac = 1.0;
	double sigmas = 50;

	//Image File Names
	char corn_input[256];
	char corn_origin[50] = "Images/Corn_gray.raw";
	char corn_denoiseBIF[50] = "Images/Corn_BIF.raw";

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

	//Sigmac Value
	if (argc > 6)
		sigmac = atof(argv[6]);

	//Sigmas Value
	if (argc > 7)
		sigmas = atof(argv[7]);

	//Construct Objects
	Image cornInput(corn_width, corn_height, bpp, corn_input);
	Image cornOringin(corn_width, corn_height, bpp, corn_origin);
	Image cornDenoiseBIF(corn_width, corn_height, bpp, corn_denoiseBIF);

	//Initialize Objects
	cornInput.initialize();
	cornOringin.initialize();
	cornDenoiseBIF.initialize();

	//Read the Input Files
	cornInput.readFile();
	cornOringin.readFile();

	//Noisy PSNR
	cornInput.imgPSNR(cornOringin);

	//Denoising
	cornInput.imgDenoiseBIF(cornDenoiseBIF, window_size, sigmac, sigmas);

	//Compute the PSNR value
	cornDenoiseBIF.imgPSNR(cornOringin);

	//Write Results in Files
	cornDenoiseBIF.writeFile();
}