//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/03/2020

class Image
{
	public:
		//Image height
		int height;
		//Image width;
		int width;
		//Number of Bytes Per pixel
		int bpp;
		//The Histogram of Image
		int** histo3D;
		//The Image FileName
		char* fileName;
		//The Image 1D array
		unsigned char* image1D;
		//The Image 3D array
		unsigned char*** image3D;
		//The Boundary-Extended Image 3D array
		unsigned char*** image3D_Extended;
		//Constructor
		Image(int imgwidth, int imgheight, int imgbpp, char *imgfileName);
		//Read File Method
		void readFile();
		//Write File Method
		void writeFile();
		//Initializer
		void initialize();
		//Histogram Arrays Initialize
		int** initHisto(int bpp);
		//Get the Image's Hsitogram
		void imgHistoRGB(char type);
		//Allocate 1D array
		unsigned char* allocate_1D(int width, int height, int bpp);
		//Allocate 2D array
		unsigned char** allocate_2D(int width, int height);
		//Allocate 3D array
		unsigned char*** allocate_3D(int width, int height, int bpp);
		//Get 3D Image from 1D Image
		void getImage3D();
		//Get 1D Image from 3D Image
		void getImage1D();
		//Extend the Image Boundary by Reflection
		int imgPadding(int N);
		//Extend the Image Boundary by Zeros
		int zeroPadding(int N);
		//Compare Images
		bool compareImage(Image other);
		//Shrinking Image Method
		void imgShrink(Image MaskImage, Image result, int thresh);
		//Thinning Image Method
		void imgThin(Image MaskImage, Image result, int thresh);
		//Skeletonizing Image Method
		void imgSkeleton(Image MaskImage, Image result, int thresh);
		//Connected Component Analysis
		void imgConnect(Image result, int thresh, int minRegion,bool histflag);
		//Get the Inverse Binary Image
		void imgReverse(Image result, int thresh);
		//PCB Count Holes
		void countPoints(Image original);
		//Find the Center and Radius of Gear
		void analyzeGear(Image original, Image reverse, Image miss, Image thin);
		//Count Stars
		void countStar(Image shrink);
		//Locate the Teeth
		void teethLocate(Image result, double x_center, double y_center, double radius);
		//Find the missing Teeth
		void findTeeth(Image result, double x_center, double y_center, double radius);
};