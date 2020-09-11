//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 01/28/2020

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
	image2D = allocate_2D(width, height);
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

//Initializer
void Image::initialize()
{
	image1D = allocate_1D(width, height, bpp);
	image2D = allocate_2D(width, height);
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
	char histoFile[50] = "Data/Histogram___.txt";
	histoFile[15] = type;
	for (int k = 0; k < bpp; k++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				int value = (int)image3D[i][j][k];
				histo3D[k][value]++;
			}
	//Write Histogram data Into File
	for (int i = 0; i < bpp; i++)
	{
		if (i == 0)
			histoFile[16] = 'R';
		else if(i == 1)
			histoFile[16] = 'G';
		else
			histoFile[16] = 'B';
		FILE* HistoFile = fopen(histoFile, "wb");
		for (int j = 0; j < 256; j++)
			fprintf(HistoFile, "%d ", histo3D[i][j]);
		fclose(HistoFile);
	}
	cout << "Histogram File Write Successfully." << endl;
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

//Extend the Image Boundary by Reflection For Problem1a & 1b
int Image::imgPaddingDemosaic(int N)
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
						image3D_Extended[i][j][k] = image3D[pad_width-i][pad_width-j][k];
					//Upper Boundary
					else if (j < width + pad_width)
						image3D_Extended[i][j][k] = image3D[pad_width-i][j-pad_width][k];
					//Upper-Right Corner
					else
						image3D_Extended[i][j][k] = image3D[pad_width-i][2*width+pad_width-j-2][k];
				}
				//Left and Right Boundary 
				else if (i < height + pad_width)
				{
					//Left Boundary
					if (j < pad_width)
						image3D_Extended[i][j][k] = image3D[i-pad_width][pad_width-j][k];
					//Image Data
					else if (j < width + pad_width)
						image3D_Extended[i][j][k] = image3D[i-pad_width][j-pad_width][k];
					//Right Boundary
					else
						image3D_Extended[i][j][k] = image3D[i-pad_width][2*width+pad_width-j-2][k];
				}
				//Lower Boundary and Corners
				else
				{
					//Lower-Left Corner
					if (j < pad_width)
						image3D_Extended[i][j][k] = image3D[2*height+pad_width-i-2][pad_width-j][k];
					//Lower Boundary
					else if (j < width + pad_width)
						image3D_Extended[i][j][k] = image3D[2*height+pad_width-i-2][j-pad_width][k];
					//Lower-Right Corner
					else
						image3D_Extended[i][j][k] = image3D_Extended[i][2*width+2*pad_width-j-1][k];
				}
			}
	//Write into File to Verify the Algorithm is Working
	/*
	FILE* ExtendedFile = fopen("Images/image3D_Extended_P1.raw", "wb");
	for (int i = 0; i < height + 2 * pad_width; i++)
		for (int j = 0; j < width + 2 * pad_width; j++)
			for (int k = 0; k < bpp; k++)
				fprintf(ExtendedFile, "%c", image3D_Extended[i][j][k]);
	fclose(ExtendedFile);
	*/
	cout << "Image Extended Successfully." << endl;
	return pad_width;
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

/*------Problem1a Functions------*/
//Get the Demosaced Image by Bilinear Interpolation
void Image::imgDemosaicBil(Image result)
{
	//Pad the Image
	int pad_width = imgPaddingDemosaic(3);

	//loop for every pixels
	for (int i = pad_width; i < height + pad_width; i++)
		for (int j = pad_width; j < width + pad_width; j++)
		{
			int top_x = i - 1;
			int floor_x = i + 1;
			int left_y = j - 1;
			int right_y = j + 1;
			int new_i = i - pad_width;
			int new_j = j - pad_width;
			//Green Pixels
			if (i % 2 == j % 2)
			{
				result.image3D[new_i][new_j][0] = (image3D_Extended[i][left_y][0] + image3D_Extended[i][right_y][0]) / 2;
				result.image3D[new_i][new_j][1] = image3D_Extended[i][j][0];
				result.image3D[new_i][new_j][2] = (image3D_Extended[top_x][j][0] + image3D_Extended[floor_x][j][0]) / 2;
				//If on the even row, exchange R and B value
				if (i % 2 == 0)
				{
					unsigned char temp = result.image3D[new_i][new_j][0];
					result.image3D[new_i][new_j][0] = result.image3D[new_i][new_j][2];
					result.image3D[new_i][new_j][2] = temp;
				}
			}
			//Blue or Red Pixels
			else
			{
				result.image3D[new_i][new_j][0] = (image3D_Extended[top_x][left_y][0] + image3D_Extended[top_x][right_y][0] + image3D_Extended[floor_x][left_y][0] + image3D_Extended[floor_x][right_y][0]) / 4;
				result.image3D[new_i][new_j][1] = (image3D_Extended[top_x][j][0] + image3D_Extended[floor_x][j][0] + image3D_Extended[i][left_y][0] + image3D_Extended[i][right_y][0]) / 4;
				result.image3D[new_i][new_j][2] = image3D_Extended[i][j][0];
				//If On the even column, exchange R and B value
				if (j % 2 == 0)
				{
					unsigned char temp = result.image3D[new_i][new_j][0];
					result.image3D[new_i][new_j][0] = result.image3D[new_i][new_j][2];
					result.image3D[new_i][new_j][2] = temp;
				}
			}
		}
	cout << "Bilinear Demosaic Completed." << endl;
}

//Get the Demosaced Image by MHC
void Image::imgDemosaicMHC(Image result)
{
	//Pad the Image
	int pad_width = imgPaddingDemosaic(5);

	//loop for every pixels
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int new_i = i + pad_width;
			int new_j = j + pad_width;

			int top_x1 = new_i - 2;
			int top_x2 = new_i - 1;
			int floor_x1 = new_i + 1;
			int floor_x2 = new_i + 2;
			
			int left_y1 = new_j - 2;
			int left_y2 = new_j - 1;
			int right_y1 = new_j + 1;
			int right_y2 = new_j + 2;

			unsigned char pix_values[13];

			pix_values[0] = image3D_Extended[top_x1][new_j][0];
			pix_values[1] = image3D_Extended[top_x2][left_y2][0];
			pix_values[2] = image3D_Extended[top_x2][new_j][0];
			pix_values[3] = image3D_Extended[top_x2][right_y1][0];
			pix_values[4] = image3D_Extended[new_i][left_y1][0];
			pix_values[5] = image3D_Extended[new_i][left_y2][0];
			pix_values[6] = image3D_Extended[new_i][new_j][0];
			pix_values[7] = image3D_Extended[new_i][right_y1][0];
			pix_values[8] = image3D_Extended[new_i][right_y2][0];
			pix_values[9] = image3D_Extended[floor_x1][left_y2][0];
			pix_values[10] = image3D_Extended[floor_x1][new_j][0];
			pix_values[11] = image3D_Extended[floor_x1][right_y1][0];
			pix_values[12] = image3D_Extended[floor_x2][new_j][0];

			//Green Pixels
			if (i % 2 == j % 2)
			{
				result.image3D[i][j][0] = bound((pix_values[0] - 2 * (pix_values[1] + pix_values[3] + pix_values[4] + pix_values[8] + pix_values[9] + pix_values[11]) + pix_values[12] + 8 * (pix_values[5] + pix_values[7]) + 10 * pix_values[6]) / 16);
				result.image3D[i][j][1] = pix_values[6];
				result.image3D[i][j][2] = bound((pix_values[4] - 2 * (pix_values[0] + pix_values[1] + pix_values[3] + pix_values[9] + pix_values[11] + pix_values[12]) + pix_values[8] + 8 * (pix_values[2] + pix_values[10]) + 10 * pix_values[6]) / 16);
				//If on the odd row, exchange R and B value
				if (i % 2 == 1)
				{
					unsigned char temp = result.image3D[i][j][0];
					result.image3D[i][j][0] = result.image3D[i][j][2];
					result.image3D[i][j][2] = temp;
				}
				continue;
			}
			//Blue and Red Pixels
			else
			{
				result.image3D[i][j][0] = pix_values[6];
				result.image3D[i][j][1] = bound((4 * pix_values[6] - (pix_values[0] + pix_values[4] + pix_values[8] + pix_values[12]) + 2 * (pix_values[2] + pix_values[5] + pix_values[7] + pix_values[10])) / 8);
				result.image3D[i][j][2] = bound((4 * (pix_values[1] + pix_values[3] + pix_values[9] + pix_values[11]) + 12 * pix_values[6] - 3 * (pix_values[0] + pix_values[4] + pix_values[8] + pix_values[12])) / 16);
				if (j % 2 == 0)
				{
					unsigned char temp = result.image3D[i][j][0];
					result.image3D[i][j][0] = result.image3D[i][j][2];
					result.image3D[i][j][2] = temp;
				}
			}		
		}
	cout << "MHC Demosaic Completed." << endl;
}

/*------Problem1c Functions------*/
//Get the Histogram Equalization Image Transfer
void Image::imgHistoTransfer(Image result)
{
	//Define the Transfer Function Name
	char funcFile[50] = "Data/Transfer__.txt";
	//Compute The New Gray Level in Each Channel
	for (int k = 0; k < bpp; k++)
	{
		int currValues = 0;
		int newGray[256] = {0};

		//Calculate the Map / CDF
		for (int i = 0; i < 256; i++)
		{
			currValues += (int)histo3D[k][i];
			newGray[i] = round((currValues * 255.0) / (width * height));
		}

		//Update the New Pixel Values
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				result.image3D[i][j][k] = (unsigned char)newGray[image3D[i][j][k]];

		//Write the Transfer Function into File
		if (k == 0)
			funcFile[14] = 'R';
		else if(k == 1)
			funcFile[14] = 'G';
		else
			funcFile[14] = 'B';

		FILE* FuncFile = fopen(funcFile, "wb");
		for (int j = 0; j < 256; j++)
			fprintf(FuncFile, "%d ", newGray[j]);
		fclose(FuncFile);
	}
	//Compute the Histogram
	result.imgHistoRGB('A');
	cout << "Histogram Equalization A Completed." << endl;
}

//Get the Histogram Equalization Image Acumulative
void Image::imgHistoAcumulative(Image result)
{
	int total = width * height;
	int num = width * height / 256;
	//Create the Sorted Pixel No Array and Initialize
	int** sortArray = new int*[bpp]();
	for (int i = 0; i < bpp; i++)
	{
		sortArray[i] = new int[total]();
		for (int j = 0; j < total; j++)
			sortArray[i][j] = 0;
	}

	//Store the Pixel No in Sorted Array
	for (int k = 0; k < bpp; k++)
	{
		int count = 0;
		for (int m = 0; m < 256; m++)
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j ++)
					if (image3D[i][j][k] == m)
					{
						sortArray[k][count] = i * width + j;
						count++;
					}
	}
	//Write into The result Image 3D Array
	for (int k = 0; k < bpp; k++)
		for (int m = 0; m < 256; m++)
			for (int i = 0; i < num; i++)
			{
				int index = sortArray[k][m * num + i];
				int row = index / width;
				int col = index - row * width;
				result.image3D[row][col][k] = m;
			}

	//Compute the Histogram
	result.imgHistoRGB('B');

	//Write the Accumulative function of Result
	char cumuFile[50] = "Data/Cumulative__.txt";
	for (int k = 0; k < bpp; k++)
	{
		//Write the Cumulation Histogram into File
		if (k == 0)
			cumuFile[16] = 'R';
		else if(k == 1)
			cumuFile[16] = 'G';
		else
			cumuFile[16] = 'B';

		int count = 0;
		FILE* CumuFile = fopen(cumuFile, "wb");
		for (int j = 0; j < 256; j++)
		{
			count += result.histo3D[k][j];
			fprintf(CumuFile, "%d ", count);
		}
		fclose(CumuFile);
	}
	cout << "Histogram Equalization B Completed." << endl;
}

/*------Problem1c Functions------*/
//Get the Denosed Image by Uniform Linear Filter
void Image::imgDenoiseLFU(Image result, int N)
{
	//Initialize the Extended Image
	int pad_width = imgPadding(N); 
	if (pad_width < 0)
		return;

	//Construct the Uniform Filter Kernel
	double filterUniform[N*N];
	for (int i = 0; i < N * N; i++)
		filterUniform[i] = 1.0 / N / N;

	//Start the Loop
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
			for (int j = pad_width; j < width + pad_width; j++)
			{
				//Construct the Values Array
				int count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = image3D_Extended[i+m][j+n][k];
						count++;
					}

				//Compute the Covolution
				result.image3D[i-pad_width][j-pad_width][k] = (unsigned char)round(convolute(filterUniform, values, N*N));
			}
	cout << "Denoise by Uniform Linear Filter Completed." << endl;
}

//Get the Denosed Image by Gaussian Linear Filter
void Image::imgDenoiseLFG(Image result, int N, double sigma)
{
	//Initialize the Extended Image
	int pad_width = imgPadding(N); 
	if (pad_width < 0)
		return;

	//Construct the Gaussian Filter Kernel
	int count = 0;
	double sum = 0;
	double filterGauss[N*N];

	//Get the Gaussian Function
	for (int m = -pad_width; m <= pad_width; m++)
		for (int n = -pad_width; n <= pad_width; n++)
			{
				filterGauss[count] =  exp(-(m * m + n * n) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
				sum += filterGauss[count];
				count++;
			}
	//Divided by Sum
	for (int i = 0; i < N * N; i++)
		filterGauss[i] = filterGauss[i] / sum;

	//Start the Loop
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
			for (int j = pad_width; j < width + pad_width; j++)
			{
				//Construct the Values Array
				count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = image3D_Extended[i+m][j+n][k];
						count++;
					}

				//Compute the Covolution
				result.image3D[i-pad_width][j-pad_width][k] = (unsigned char)round(convolute(filterGauss, values, N*N));
			}
	cout << "Denoise by Gaussian Linear Filter Completed." << endl;
}

//Get the Denosed Image by Bilateral Filter
void Image::imgDenoiseBIF(Image result, int N, double sigmac, double sigmas)
{
	//Initialize the Extended Image
	int pad_width = imgPadding(N); 
	if (pad_width < 0)
		return;

	//Start the Loop
	int count = 0;
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
			for (int j = pad_width; j < width + pad_width; j++)
			{
				//Construct the Bilateral Filter Kernel
				count = 0;
				double sum = 0;
				double filterBilate[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						double s1 = 2 * sigmac * sigmac;
						double s2 = 2 * sigmas * sigmas;
						double r1 = -(m * m + n * n) / 1.0;
						double r2 = abs(image3D_Extended[i][j][k] - image3D_Extended[i+m][j+n][k]);
						filterBilate[count] = exp(r1 / s1 - r2 * r2 / s2);
						sum += filterBilate[count];
						count++;
					}
				//Divided by Sum
				for (int i = 0; i < N * N; i++)
					filterBilate[i] = filterBilate[i] / sum;
				//Construct the Values Array
				count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = image3D_Extended[i+m][j+n][k];
						count++;
					}
				//Compute the Covolution
				result.image3D[i-pad_width][j-pad_width][k] = (unsigned char)round(convolute(filterBilate, values, N*N));
			}
	cout << "Denoise by Bilateral Filter Completed." << endl;
}

//Get the Denosed Image by None Local Mean Filter
void Image::imgDenoiseNLM(Image result, int N, int M, double h, double sigma)
{
	//Initialize the Extended Image
	int pad_width_total = imgPadding(N + M - 1);
	if (pad_width_total < 0)
		return;

	//Get the Search Pad Width of Comparing and Pad width of Search
	int pad_width_N = (N - 1) / 2;
	int pad_width_M = (M - 1) / 2; 

	//Compute the Gaussian Array
	int count = 0;
	double sum = 0;
	double filterGauss[N*N];
	for (int m = -pad_width_N; m <= pad_width_N; m++)
		for (int n = -pad_width_N; n <= pad_width_N; n++)
			{
				filterGauss[count] =  exp(-(m * m + n * n) / (2 * sigma * sigma)) / sqrt(2 * M_PI * sigma * sigma);
				sum += filterGauss[count];
				count++;
			}
	//Divided by Sum
	for (int i = 0; i < N * N; i++)
		filterGauss[i] = filterGauss[i] / sum;

	//Start the Loop
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width_total; i < height + pad_width_total; i++)
			for (int j = pad_width_total; j < width + pad_width_total; j++)
			{
				//Construct the Total Window Valuse Array
				count = 0;
				unsigned char t_values[M*M];
				for (int m = -pad_width_M; m <= pad_width_M; m++)
					for (int n = -pad_width_M; n <= pad_width_M; n++)
					{
						t_values[count] = image3D_Extended[i+m][j+n][k];
						count++;
					}
				//Construct the Current Window Values Array
				count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width_N; m <= pad_width_N; m++)
					for (int n = -pad_width_N; n <= pad_width_N; n++)
					{
						values[count] = image3D_Extended[i+m][j+n][k];
						count++;
					}
				//Construct the NLM Filter Array
				sum = 0;
				count = 0;
				double filterNLM[M*M];
				for (int m = -pad_width_M; m <= pad_width_M; m++)
					for (int n = -pad_width_M; n <= pad_width_M; n++)
					{
						//Construct the Comparing Window Values Array
						int c_count = 0;
						unsigned char c_values[N*N];
						for (int p = -pad_width_N; p <= pad_width_N; p++)
							for (int q = -pad_width_N; q <= pad_width_N; q++)
							{
								c_values[c_count] = image3D_Extended[i+m+p][j+n+q][k];
								c_count++;
							}
						//Subtract the Comparing Window from the Current Window
						int s_values[N*N];
						for (int p = 0; p < N * N; p++)
						{
							int s = values[p] - c_values[p];
							s_values[p] = s * s;
						}
						//Compute the Euclidian Distance and the F Function
						double distance = convolute1(filterGauss, s_values, N*N);
						//cout << distance << endl;
						filterNLM[count] = exp(- distance / h / h);
						sum += filterNLM[count];
						count++;
					}
				//Divided by Sum
				for (int m = 0; m < M * M; m++)
					filterNLM[m] = filterNLM[m] / sum;

				//Convolution of the Filter and The Total Values
				result.image3D[i-pad_width_total][j-pad_width_total][k] = (unsigned char)bound(round(convolute(filterNLM, t_values, M*M)));
			}
	cout << "Denoise by None Local Mean Filter Completed." << endl;
}













