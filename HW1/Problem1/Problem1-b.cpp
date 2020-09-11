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
	int dog_width = 600;
	int dog_height = 532;
	int bpp = 1;

	//Image File Names
	char dog_input[256];
	char dog_origin[50] = "Images/Dog_ori.raw";
	char dog_demosaicMHC[50] = "Images/Dog_demosaicMHC.raw";

	//Multiple Input
	strcpy(dog_input, argv[1]);

	if (argc > 2)
	{
		dog_width = atoi(argv[2]);
		dog_height = atoi(argv[3]);
	}
	if (argc > 4)
		bpp = atoi(argv[4]);

	//Construct Objects
	Image dogInput(dog_width, dog_height, bpp, dog_input);
	Image dogOrigin(dog_width, dog_height, 3, dog_origin);
	Image dogDemosaicMHC(dog_width, dog_height, 3, dog_demosaicMHC);

	//Initialize Objects
	dogInput.initialize();
	dogOrigin.initialize();
	dogDemosaicMHC.initialize();

	//Read the Input Files
	dogInput.readFile();
	dogOrigin.readFile();

	//Do the Jobs of Demosaicing MHC
	dogInput.imgDemosaicMHC(dogDemosaicMHC);

	//Compute the PSNR value
	dogDemosaicMHC.imgPSNR(dogOrigin);

	//Write Results in Files
	dogDemosaicMHC.writeFile();
}