//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 02/16/2020

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
		//Get the difference between Two Images
		void imgPSNR(Image origin);
		//Get the Grayscale Image from RGB
		void color2Gray(Image gray);
		//Copy the Image Data From 3D into Double
		double*** copy2double(int pad_width);
		//Transfer the Image Between RGB and CMY space
		void transferSpaces(Image result);
		//Find the Pyramid Of the Pixel
		int findPyramid(double RGB[]);
		//Find the Vertex Of the PIXel
		int findVertex(int pyramid, double thresh, double RGB[]);
		//Set the Color from Vertex
		double* getColors(int vertex);

		/*-----------Problem Methods-------------*/
		//Sobel Edge Detector
		void sobelEdge(Image result, Image grayX, Image grayY, double ratio);
		//Half toning Fixed 
		void toneFixed(Image result, unsigned char thresh);
		//Half toning Random
		void toneRand(Image result, unsigned char tSeed);
		//Half toning Dithering Matrix
		void toneDither(Image result, int N);
		//Error Diffusion Floyd-Steinberg
		void errorFS(Image result, double thresh);
		//Error Diffusion
		void errorDiff(Image result, double thresh, int N, int deno, double filter_ori[], double filter_flp[]);
		//MBVQ Method
		void MBVQ_errDiff(Image result, double thresh, int N, int deno, double filter_ori[], double filter_flp[]);
};