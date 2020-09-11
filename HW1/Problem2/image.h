//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 01/28/2020

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
		//The Image 2D array
		unsigned char** image2D;
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
		//Get the Image's Hsitogram
		void imgHistoRGB(char type);
		//Extend the Image Boundary by Reflection
		int imgPadding(int N);
		//Extend the Image Boundary by Reflection Using Problem1
		int imgPaddingDemosaic(int N);
		//Get the difference between Two Images
		void imgPSNR(Image origin);

		/*----Problem Functions-----*/
		//Problem1a --- Get the Demosaced Image by Bilinear Interpolation
		void imgDemosaicBil(Image result);
		//Problem1b --- Get the Demosaced Image by MHC
		void imgDemosaicMHC(Image result);
		//Problem1c --- Get the Histogram Equalization Transfer
		void imgHistoTransfer(Image result);
		//Problem1c --- Get the Histogram Equalization Cumulative
		void imgHistoAcumulative(Image result);
		//Problem2a --- Linear Filter-Uniform
		void imgDenoiseLFU(Image result, int N);
		//Problem2a --- Linear Filter-Gaussian
		void imgDenoiseLFG(Image result, int N, double sigma);
		//Problem2b --- Bilateral Filter
		void imgDenoiseBIF(Image result, int N, double sigmac, double sigmas);
		//Problem2c --- Bilateral Filter
		void imgDenoiseNLM(Image result, int N, int M, double h, double sigma);
};