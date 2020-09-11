//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 02/16/2020

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "image.h"

#define _USE_MATH_DEFINES

using namespace std;

//Keep the Values Don't Overflow
int bound(double value)
{
	value = value > 255 ? 255 : value;
	value = value < 0 ? 0 : value;
	return (int)value;
}

//Convolution
double convolute(double filter[], unsigned char value[], int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum = sum + value[i] * filter[i];
	return sum;
}

//Convolution ReLoad
double convolute1(double filter[], int value[], int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum = sum + value[i] * filter[i];
	return sum;
}

//Allocate 2D array
double** allocate_2DArray(int width, int height)
{
	double** Array = new double *[height]();
	for (int i = 0; i < height; i++)
	{
		Array[i] = new double[width];
		for (int j = 0; j < width; j++)
			Array[i][j] = 0;
	}
	return Array;
}

//Find Maximum Value from Array
double findMax(double** array, int height, int width)
{
	double maximum = array[0][0];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (array[i][j] > maximum)
				maximum = array[i][j];
	return maximum;
}

//Find Minimum Value from Array
double findMin(double** array, int height, int width)
{
	double minimum = array[0][0];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (array[i][j] < minimum)
				minimum = array[i][j];
	return minimum;
}

/*----------------------Member Functions------------------------*/
/*------Accessory Functions-----*/
//Constructor1
Image::Image(int imgwidth, int imgheight, int imgbpp, char imgfileName[])
{
	width = imgwidth;
	height = imgheight;
	bpp = imgbpp;
	fileName = imgfileName;
	image1D = allocate_1D(width, height, bpp);
	image3D = allocate_3D(width, height, bpp);
}

//Allocate 1D array
unsigned char* Image::allocate_1D(int width, int height, int bpp)
{
	int pixCount = width * height * bpp;
	unsigned char* Img = new unsigned char[pixCount]();
	for (int i = 0; i < pixCount; i++)
		Img[i] = 0;
	return Img;
}

//Allocate 2D array
unsigned char** Image::allocate_2D(int width, int height)
{
	unsigned char** Img = new unsigned char *[height]();
	for (int i = 0; i < height; i++)
	{
		Img[i] = new unsigned char[width];
		for (int j = 0; j < width; j++)
			Img[i][j] = 0;
	}
	return Img;
}

//Allocate 3D array
unsigned char*** Image::allocate_3D(int width, int height, int bpp)
{
	unsigned char*** Img = new unsigned char **[height]();
	for (int i = 0; i < height; i++)
	{
		Img[i] = new unsigned char*[width]();
		for (int j = 0; j < width; j++)
		{
			Img[i][j] = new unsigned char[bpp]();
			for (int k = 0; k < bpp; k++)
				Img[i][j][k] = 255;
		}
	}
	return Img;
}

//Histogram Arrays Initialize
int** Image::initHisto(int bpp)
{
	int** Histo = new int *[bpp]();
	for (int i = 0; i < bpp; i++)
	{
		Histo[i] = new int[256];
		for (int j = 0; j < 256; j++)
			Histo[i][j] = 0;
	}
	return Histo;
}

//Get the Histogram of RGB Image
void Image::imgHistoRGB(char type)
{
	char histoFile[50] = "Images/Histogram___.txt";
	histoFile[17] = type;
	for (int k = 0; k < bpp; k++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				int value = (int)image3D[i][j][k];
				histo3D[k][value]++;
			}
	//Write Histogram data Into File
	/*for (int i = 0; i < bpp; i++)
	{
		if (i == 0)
			histoFile[18] = 'R';
		else if(i == 1)
			histoFile[18] = 'G';
		else
			histoFile[18] = 'B';
		FILE* HistoFile = fopen(histoFile, "wb");
		for (int j = 0; j < 256; j++)
			fprintf(HistoFile, "%d ", histo3D[i][j]);
		fclose(HistoFile);
	}*/
	cout << "Histogram File Write Successfully." << endl;
}

//Initializer
void Image::initialize()
{
	image1D = allocate_1D(width, height, bpp);
	image3D = allocate_3D(width, height, bpp);
	histo3D = initHisto(bpp);
}

//Read File Method
void Image::readFile()
{
	FILE* file = fopen(fileName, "rb");
	if (file == NULL)
	{
		cout << "File Open Failed." << endl;
		return;
	}
	else
		fread(image1D, sizeof(unsigned char), width*height*bpp, file);
	fclose(file);
	getImage3D();
	cout << "File Read Successfully." << endl;
}

//Write File Method
void Image::writeFile()
{
   	FILE* out_file = fopen(fileName, "wb");
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < bpp; k++)
				fprintf(out_file, "%c", image3D[i][j][k]);
	cout << "File Write Successfully." << endl;
	fclose(out_file);
}

//Get 3D Image from 1D Image
void Image::getImage3D()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < bpp; k++)
			{
				int temp = (i * width + j) * bpp + k;
				image3D[i][j][k] = image1D[temp];
			}
	//cout << "Get 3D Image Completed." << endl;
}

//Get 1D Image from 3D Image
void Image::getImage1D()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < bpp; k++)
			{
				int temp = (i * width + j) * bpp + k;
				image1D[temp] = image3D[i][j][k];
			}
}

//Extend the Image Boundary by Reflection
int Image::imgPadding(int N)
{
	if (!(N % 2))
	{
		cout << "The Window Size Cannot Be Even." << endl;
		return -1;
	}
	//Define the Padding width
	int pad_width = (N-1) / 2;

	//Initialize the Array for Storing the Image
	image3D_Extended = allocate_3D(width + 2 * pad_width, height + 2 * pad_width, bpp);

	//Store the 3D Image Data into it
	for (int i = 0; i < height + 2 * pad_width; i++)
		for (int j = 0; j < width + 2 * pad_width; j++)
			for (int k = 0; k < bpp; k++)
			{
				//Upper Boundary and Corners
				if (i < pad_width)
				{
					//Upper-Left Corner
					if (j < pad_width)
						image3D_Extended[i][j][k] = image3D[pad_width-1-i][pad_width-1-j][k];
					//Upper Boundary
					else if (j < width + pad_width)
						image3D_Extended[i][j][k] = image3D[pad_width-1-i][j-pad_width][k];
					//Upper-Right Corner
					else
						image3D_Extended[i][j][k] = image3D[pad_width-1-i][2*width+pad_width-j-1][k];
				}
				//Left and Right Boundary 
				else if (i < height + pad_width)
				{
					//Left Boundary
					if (j < pad_width)
						image3D_Extended[i][j][k] = image3D[i-pad_width][pad_width-1-j][k];
					//Image Data
					else if (j < width + pad_width)
						image3D_Extended[i][j][k] = image3D[i-pad_width][j-pad_width][k];
					//Right Boundary
					else
						image3D_Extended[i][j][k] = image3D[i-pad_width][2*width+pad_width-j-1][k];
				}
				//Lower Boundary and Corners
				else
				{
					//Lower-Left Corner
					if (j < pad_width)
						image3D_Extended[i][j][k] = image3D[2*height+pad_width-i-1][pad_width-1-j][k];
					//Lower Boundary
					else if (j < width + pad_width)
						image3D_Extended[i][j][k] = image3D[2*height+pad_width-i-1][j-pad_width][k];
					//Lower-Right Corner
					else
						image3D_Extended[i][j][k] = image3D_Extended[i][2*width+2*pad_width-j-1][k];
				}
			}
	//Write into File to Verify the Algorithm is Working
	/*	
	FILE* ExtendedFile = fopen("Images/image3D_Extended.raw", "wb");
	for (int i = 0; i < height + 2 * pad_width; i++)
		for (int j = 0; j < width + 2 * pad_width; j++)
			for (int k = 0; k < bpp; k++)
				fprintf(ExtendedFile, "%c", image3D_Extended[i][j][k]);
	fclose(ExtendedFile);
	*/
	cout << "Image Extended Successfully." << endl;
	return pad_width;
}

//Get the Differences between Two Images
void Image::imgPSNR(Image origin)
{
	double mse = 0;
	//loop for every pixels
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < bpp; k++)
			{
				double temp = (double)abs(origin.image3D[i][j][k] - image3D[i][j][k]);
				mse += (temp * temp / (width * height * bpp * 1.0));
			}
	double PSNR = 0;
	PSNR = 10 * log10(255 * 255 / mse);
	cout << "The PSNR of " << fileName << " is " << PSNR << endl;
}

//Get the Grayscale Image from RGB
void Image::color2Gray(Image gray)
{
	if (bpp < 3)
		cout << "The Input Object is Not Colorful. Please Check." << endl;
	if (gray.bpp > 1)
		cout << "The Output Object is Not Grayscale. Please Check." << endl;
 	//loop for every pixel
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			gray.image3D[i][j][0] = (unsigned char)round(0.2989 * image3D[i][j][0] + 0.5870 * image3D[i][j][1] + 0.1140 * image3D[i][j][2]);
}

//Sobel Edge Detector
void Image::sobelEdge(Image result, Image grayX, Image grayY, Image edgeMap,double ratio)
{
	if (bpp > 1)
	{
		cout << "The Input is not Grayscaled Image." << endl;
		return ;
	}
	//Image Extension
	int pad_width = imgPadding(3);

	//Constrcut Sobel Filters
	double sobel_X[9] = {-0.25, 0, 0.25, -0.5, 0, 0.5, -0.25, 0, 0.25};
	double sobel_Y[9] = {0.25, 0.5, 0.25, 0, 0, 0, -0.25, -0.5, -0.25};

	//Loop to Calculate the Magnitude
	double **grayMapX = allocate_2DArray(width, height);
	double **grayMapY = allocate_2DArray(width, height);
	double **gradient = allocate_2DArray(width, height);

	int n_count = 0;
	for (int i = 1; i < height + 1; i++)
		for (int j = 1; j < width + 1; j++)
		{
			//Construct the Values Array
			int count = 0;
			unsigned char values[9];
			for (int p = -pad_width; p <= pad_width; p++)
				for (int l = -pad_width; l <= pad_width; l++)
				{
					values[count] = image3D_Extended[i+p][j+l][0];
					count++;
				}
			grayMapX[i-pad_width][j-pad_width] = abs(convolute(sobel_X, values, 9));
			grayMapY[i-pad_width][j-pad_width] = abs(convolute(sobel_Y, values, 9));
			gradient[i-pad_width][j-pad_width] = sqrt(grayMapX[i-pad_width][j-pad_width] * grayMapX[i-pad_width][j-pad_width] + grayMapY[i-pad_width][j-pad_width] * grayMapY[i-pad_width][j-pad_width]);
		}

	//Normalize the Gradients
	double max_X = findMax(grayMapX, height, width);
	double min_X = findMin(grayMapX, height, width);
	double max_Y = findMax(grayMapY, height, width);
	double min_Y = findMin(grayMapY, height, width);
	double max_G = findMax(gradient, height, width);
	double min_G = findMin(gradient, height, width);
	//Do the Normalization
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			grayMapX[i][j] = 255 * (grayMapX[i][j] - min_X) / (max_X - min_X);
			grayMapY[i][j] = 255 * (grayMapY[i][j] - min_Y) / (max_Y - min_Y);
			gradient[i][j] = 255 * (gradient[i][j] - min_G) / (max_G - min_G);
		}

	//Get the Gradient Magnitude
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			grayX.image3D[i][j][0] = (unsigned char)grayMapX[i][j];
			grayY.image3D[i][j][0] = (unsigned char)grayMapY[i][j];
			edgeMap.image3D[i][j][0] = (unsigned char)gradient[i][j];
		}

	//Sort the Pixel Values
	int count = 0;
	int sortArray[height * width];
	for (int k = 255; k >= 0; k--)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (edgeMap.image3D[i][j][0] == k)
				{
					sortArray[count] = i * width + j;
					count++;
				}
			}

	//Get Binary Image
	int num = round(ratio * height * width);
	for (int k = 0; k < height * width; k++)
	{
		int index = sortArray[k];
		int row = index / width;
		int col = index - row * width;
		if (k <= num)
			result.image3D[row][col][0] = (unsigned char)0;
		else
			result.image3D[row][col][0] = (unsigned char)255;
	}
}



















