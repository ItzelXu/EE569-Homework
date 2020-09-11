//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 02/16/2020

#include <iostream>
#include "image.h"

using namespace std;

int main(int argc, char* argv[])
{
	//argv[0] : Program Name
	//argv[1] : Threshold for Gallery
	//argv[2] : Threshold for Dogs

	//Define the Size the Gallery Image
	int gallery_width = 481;
	int gallery_height = 321;
	int dog_width = 481;
	int dog_height = 321;
	double thresh1 = 0.1;
	double thresh2 = 0.1;

	if (argc > 1)
		thresh1 = atof(argv[1]);
	if (argc > 2)
		thresh2 = atof(argv[2]);

	//File Names Defination
	char gallery_input[50] = "Images/Gallery.raw";
	char gallery_gray[50] = "Images/Gallery_Gray.raw";
	char gallery_grayX[50] = "Images/Gallery_GrayX.raw";
	char gallery_grayY[50] = "Images/Gallery_GrayY.raw";
	char gallery_map[50] = "Images/Gallery_SB_Map.raw";
	char gallery_edges[50] = "Images/Gallery_Edges.raw";

	char dog_input[50] = "Images/Dogs.raw";
	char dog_gray[50] = "Images/Dogs_Gray.raw";
	char dog_grayX[50] = "Images/Dogs_GrayX.raw";
	char dog_grayY[50] = "Images/Dogs_GrayY.raw";
	char dog_map[50] = "Images/Dogs_SB_Map.raw";
	char dog_edges[50] = "Images/Dogs_Edges.raw";

	//Construct the Objects
	Image galleryInput(gallery_width, gallery_height, 3, gallery_input);
	Image galleryGray(gallery_width, gallery_height, 1, gallery_gray);
	Image galleryGrayX(gallery_width, gallery_height, 1, gallery_grayX);
	Image galleryGrayY(gallery_width, gallery_height, 1, gallery_grayY);
	Image galleryMap(gallery_width, gallery_height, 1, gallery_map);
	Image galleryEdges(gallery_width, gallery_height, 1, gallery_edges);

	Image dogInput(dog_width, dog_height, 3, dog_input);
	Image dogGray(dog_width, dog_height, 1, dog_gray);
	Image dogGrayX(dog_width, dog_height, 1, dog_grayX);
	Image dogGrayY(dog_width, dog_height, 1, dog_grayY);
	Image dogMap(dog_width, dog_height, 1, dog_map);
	Image dogEdges(dog_width, dog_height, 1, dog_edges);

	//Read the Input Files
	galleryInput.readFile();
	//Change to Grayscle
	galleryInput.color2Gray(galleryGray);
	//Do the Sobel Filter
	galleryGray.sobelEdge(galleryEdges, galleryGrayX, galleryGrayY, galleryMap, thresh1);

	//Write Files
	//galleryGray.writeFile();
	//galleryGrayX.writeFile();
	//galleryGrayY.writeFile();
	galleryMap.writeFile();
	galleryEdges.writeFile();

	//Read the Input Files
	dogInput.readFile();
	//Change to Grayscle
	dogInput.color2Gray(dogGray);
	//Do the Sobel Filter
	dogGray.sobelEdge(dogEdges, dogGrayX, galleryGrayY, dogMap, thresh2);

	//Write Files
	//dogGray.writeFile();
	//dogGrayX.writeFile();
	//dogGrayY.writeFile();
	dogMap.writeFile();
	dogEdges.writeFile();

	return 0;
}