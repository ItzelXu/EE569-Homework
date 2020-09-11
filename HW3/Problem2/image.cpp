//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/03/2020

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "image.h"

#define _USE_MATH_DEFINES

using namespace std;

//Conditional Mask Matrix of Shrinking
const unsigned char CMP_S[58] = 
{
	//S1
	32, 128, 4, 1,
	//S2
	8, 64, 16, 2,
	//S3
	40, 96, 192, 144, 20, 6, 3, 9,
	//STK1
	41, 224, 148, 7,
	//ST1
	200, 73, 112, 42,
	//ST2
	104, 208, 22, 11,
	//ST3
	201, 116,
	//STK2
	232, 105, 240, 212, 150, 23, 15, 43,
	//STK3
	233, 244, 151, 47,
	//STK4
	107, 248, 214, 31,
	//STK5
	235, 111, 252, 249, 246, 215, 159, 63,
	//STK6
	239, 253, 247, 191
};

//Conditional Mask Matrix of Thinning
const unsigned char CMP_T[46] = 
{
	//TK
	72, 80, 18, 10,
	//STK1
	41, 224, 148, 7,
	//ST1
	200, 73, 112, 42,
	//ST2
	104, 208, 22, 11,
	//ST3
	201, 116,
	//STK2
	232, 105, 240, 212, 150, 23, 15, 43,
	//STK3
	233, 244, 151, 47,
	//STK4
	107, 248, 214, 31,
	//STK5
	235, 111, 252, 249, 246, 215, 159, 63,
	//STK6
	239, 253, 247, 191
};

const unsigned char CMP_K[40] = 
{
	//TK
	72, 80, 18, 10,
	//STK1
	41, 224, 148, 7,
	//STK2
	232, 105, 240, 212, 150, 23, 15, 43,
	//STK3
	233, 244, 151, 47,
	//STK4
	107, 248, 214, 31,
	//STK5
	235, 111, 252, 249, 246, 215, 159, 63,
	//STK6
	239, 253, 247, 191,
	//K
	251, 254, 223, 127
};


//Unconditional Mask Matrix Shrinking Thinning
const unsigned char UMP_ST[332] = 
{
	//Spur
	32, 128,
	//Single 4-connection
	2, 8,
	//L Cluster
	40, 96, 192, 144, 20, 6, 3, 9,
	//4-connected Offset
	112, 200, 73, 42,
	//Spur Corner Cluster
	44, 100, 108, 
	145, 193, 209, 
	38, 52, 54, 
	137, 131, 139,
	//Corner Cluster
	208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 
	240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
	//11,  15,  27,  31,  43,  47,  59,  63,  75,  79,  91,  95,  107, 111, 123, 127, 
	//139, 143, 155, 159, 171, 175, 187, 191, 203, 207, 219, 223, 235, 239, 251, 255,
	//Tee Branch
	88, 92, 216, 220, 
	88, 89, 120, 121, 
	26, 27, 58, 59,
	26, 30, 154, 158,
	82, 114, 210, 242,
	82, 83, 86, 87, 
	74, 75, 78, 79, 
	74, 106, 202, 234,
	//Vee Branch
	161, 162, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175, 177, 178,
	179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191, 
	225, 226, 227, 228, 229, 230, 231, 233, 234, 235, 236, 237, 238, 239, 241, 242, 
	243, 244, 245, 246, 247, 249, 250, 251, 252, 253, 254, 255, 

	133, 140, 141, 164, 165, 172, 173, 135, 142, 143, 166, 167, 174, 175, 149, 156, 
	157, 180, 181, 188, 189, 151, 158, 159, 182, 183, 190, 191, 
	197, 204, 205, 228, 229, 236, 237, 199, 206, 207, 230, 231, 238, 239, 213, 220, 
	221, 244, 245, 252, 253, 215, 222, 223, 246, 247, 254, 255,

	37,  39,  45,  47,  53,  55,  61,  63,  69,  71,  77,  79,  85,  87,  93,  95, 
	101, 103, 109, 111, 117, 119, 125, 127, 133, 135, 141, 143, 
	149, 151, 157, 159, 165, 167, 173, 175, 181, 183, 189, 191, 197, 199, 205, 207, 
	213, 215, 221, 223, 229, 231, 237, 239, 245, 247, 253, 255,

	37,  39,  45,  47,  49,  51,  53,  55,  57,  59,  61,  63,  101, 103, 109, 111, 
	113, 115, 117, 119, 121, 123, 125, 127, 161, 163, 165, 167, 
	169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 225, 227, 229, 231, 
	233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255,

	//Diagonal Branch
	76, 77, 204, 205, 
	50, 51, 178, 179, 
	81, 85, 113, 117, 
	138, 142, 170, 174
};

//Unconditional Mask Matrix Skeleton
const unsigned char UMP_SK[444] = 
{
	//Spur
	1, 4, 32, 128,
	//Single 4-connection
	2, 8, 16, 64,
	//L Corner
	72, 80, 10, 18,
	//Corner Cluster
	208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 
	240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
	11,  15,  27,  31,  43,  47,  59,  63,  75,  79,  91,  95,  107, 111, 123, 127, 
	139, 143, 155, 159, 171, 175, 187, 191, 203, 207, 219, 223, 235, 239, 251, 255,
	//Tee Branch
	88,  89,  90,  91,  92,  93,  94,  95,  120, 121, 122, 123, 124, 125, 126, 127, 
	216, 217, 218, 219, 220, 221, 222, 223, 248, 249, 250, 251, 252, 253, 254, 255,

	82,  83,  86,  87,  90,  91,  94,  95,  114, 115, 118, 119, 122, 123, 126, 127, 
	210, 211, 214, 215, 218, 219, 222, 223, 242, 243, 246, 247, 250, 251, 254, 255,

	26,  27,  30,  31,  58,  59,  62,  63,  90,  91,  94,  95,  122, 123, 126, 127, 
	154, 155, 158, 159, 186, 187, 190, 191, 218, 219, 222, 223, 250, 251, 254, 255,

	74,  75,  78,  79,  90,  91,  94,  95,  106, 107, 110, 111, 122, 123, 126, 127, 
	202, 203, 206, 207, 218, 219, 222, 223, 234, 235, 238, 239, 250, 251, 254, 255,
	//Vee Branch
	161, 162, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175, 177, 178,
	179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191, 
	225, 226, 227, 228, 229, 230, 231, 233, 234, 235, 236, 237, 238, 239, 241, 242, 
	243, 244, 245, 246, 247, 249, 250, 251, 252, 253, 254, 255, 

	133, 140, 141, 164, 165, 172, 173, 135, 142, 143, 166, 167, 174, 175, 149, 156, 
	157, 180, 181, 188, 189, 151, 158, 159, 182, 183, 190, 191, 
	197, 204, 205, 228, 229, 236, 237, 199, 206, 207, 230, 231, 238, 239, 213, 220, 
	221, 244, 245, 252, 253, 215, 222, 223, 246, 247, 254, 255,

	37,  39,  45,  47,  53,  55,  61,  63,  69,  71,  77,  79,  85,  87,  93,  95, 
	101, 103, 109, 111, 117, 119, 125, 127, 133, 135, 141, 143, 
	149, 151, 157, 159, 165, 167, 173, 175, 181, 183, 189, 191, 197, 199, 205, 207, 
	213, 215, 221, 223, 229, 231, 237, 239, 245, 247, 253, 255,

	37,  39,  45,  47,  49,  51,  53,  55,  57,  59,  61,  63,  101, 103, 109, 111, 
	113, 115, 117, 119, 121, 123, 125, 127, 161, 163, 165, 167, 
	169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 225, 227, 229, 231, 
	233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255,
	//Diagonal Branch
	76, 77, 204, 205, 
	50, 51, 178, 179, 
	81, 85, 113, 117, 
	138, 142, 170, 174
};

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

//Get the Mask Pattern
unsigned char getMask(unsigned char value[])
{
	unsigned char temp = 0;
	temp = temp + 128 * value[0];
	temp = temp + 64 * value[1];
	temp = temp + 32 * value[2];
	temp = temp + 16* value[3];
	temp = temp + 8 * value[5];
	temp = temp + 4 * value[6];
	temp = temp + 2 * value[7];
	temp = temp + 1 * value[8];
	return temp;
}

//Find Masks or Not
bool compareMask(unsigned char mask, const unsigned char pattern[], int N)
{
	for (int i = 0; i < N; i++)
		if (pattern[i] == mask)
			return true;
	return false;
}

//Get the Case for the Values
unsigned char getCase(int values[])
{
	int status = 0;
	int temp = 0;
	//Case 1
	for (int i = 0; i < 4; i++)
		if (values[i] != 0)
		{
			status = 1;
			temp = values[i];
			break;
		}
	//Case 2
	for (int i = 0; i < 4; i++)
		if (values[i] != 0 && values[i] != temp)
		{
			status = 2;
			break;
		}
	return status; 
}

//Union
void unionFunc(int large, int small, int parent[])
{
	int i = large;
    int j = small;
    while (0 != parent[i])
        i = parent[i];
    while (0 != parent[j])
        j = parent[j];
    if (i != j)
        parent[i] = j;
}

//Find the Corresponding Value
int findRoot(int value, int parent[]) 
{
    int i = value;
    while (0 != parent[i])
        i = parent[i];
    return i;
}

//Find Minimum Positive Number
int min(int values[], int len)
{
	int mini = 10000;
	for (int i = 0; i < len; i++)
		if (values[i] != 0 && values[i] < mini)
			mini = values[i];
	return mini;
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
				Img[i][j][k] = 0;
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

//Compare Images Same or Not
bool Image::compareImage(Image other)
{
	for (int k = 0; k < bpp; k++)
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
				if (other.image3D[i][j][k] != image3D[i][j][k])
					return false;
	return true;	
}

//Extend the Image Boundary by Reflection
int Image::zeroPadding(int N)
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
				//Image Data
				if (i >= pad_width && i < height + pad_width && j >= pad_width && j < width + pad_width)
					image3D_Extended[i][j][k] = image3D[i-pad_width][j-pad_width][k];
				else
					image3D_Extended[i][j][k] = 0;
			}
	cout << "Image Zero Extended Successfully." << endl;
	return pad_width;
}

//Image Shrinking Function
void Image::imgShrink(Image MaskImage, Image result, int thresh)
{
	int N = 3;
	int pad_width = 1;

	//Copy the Data
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (image3D[i][j][0] > thresh)
				image3D[i][j][0] = 255;
			else
				image3D[i][j][0] = 0;
		}

	//Start the Loop
	bool finish = false;
	int iter = 0;
	while(!finish)
	{
		iter++;
		//Loop Over --- Conditional
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
			{
				//Construct Value Arrays
				MaskImage.image3D[i][j][0] = 0;
				int count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = image3D[i+m][j+n][0] / 255;
						count++;
					}
				//Conditional
				unsigned char mask = getMask(values);
				bool hit1 = compareMask(mask, CMP_S, 58);
				if (hit1)
					MaskImage.image3D[i][j][0] = (image3D[i][j][0] && hit1);
			}
		//Loop Over --- Unconditional
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
			{
				//Construct Value Arrays
				int count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = MaskImage.image3D[i+m][j+n][0];
						count++;
					}
				//Unconditional
				unsigned char mask = getMask(values);
				bool hit2 = compareMask(mask, UMP_ST, 332);
				image3D[i][j][0] = (image3D[i][j][0] && (!MaskImage.image3D[i][j][0] || hit2)) * 255;
			}
		//Check Finish
		finish = compareImage(result);
		//Loop Result Stored Temp
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
				result.image3D[i][j][0] = image3D[i][j][0];
	}
	getImage3D();
	cout << "Shrinking Completed. Iteration = " << iter << endl;
}

//Image Thinning Function
void Image::imgThin(Image MaskImage, Image result, int thresh)
{
	getImage1D();
	int N = 3;
	int pad_width = 1;

	//Copy the Data
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (image3D[i][j][0] > thresh)
				image3D[i][j][0] = 255;
			else
				image3D[i][j][0] = 0;
		}

	//Start the Loop
	bool finish = false;
	int iter = 0;
	while(!finish)
	{
		iter++;
		//Loop Over --- Conditional
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
			{
				//Construct Value Arrays
				MaskImage.image3D[i][j][0] = 0;
				int count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = image3D[i+m][j+n][0] / 255;
						count++;
					}
				//Conditional
				unsigned char mask = getMask(values);
				bool hit1 = compareMask(mask, CMP_T, 46);
				MaskImage.image3D[i][j][0] = (image3D[i][j][0] && hit1);
			}
		//Loop Over --- Unconditional
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
			{
				//Construct Value Arrays
				int count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = MaskImage.image3D[i+m][j+n][0];
						count++;
					}
				//Unconditional
				unsigned char mask = getMask(values);
				bool hit2 = compareMask(mask, UMP_ST, 332);
				image3D[i][j][0] = (image3D[i][j][0] && (!MaskImage.image3D[i][j][0] || hit2)) * 255;
			}
		//Check Finish
		finish = compareImage(result);
		//Loop Result Stored Temp
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
				result.image3D[i][j][0] = image3D[i][j][0];
	}
	getImage3D();
	cout << "Thinning Completed. Iteration = " << iter << endl;
}

//Image Skeletonizing Function
void Image::imgSkeleton(Image MaskImage, Image result, int thresh)
{
	int N = 3;
	int pad_width = 1;

	//Filter the Data
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (image3D[i][j][0] > thresh)
				image3D[i][j][0] = 255;
			else
				image3D[i][j][0] = 0;
		}

	//Start the Loop
	bool finish = false;
	int iter = 0;
	while(!finish)
	{
		iter++;
		//Loop Over --- Conditional
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
			{
				//Construct Value Arrays
				MaskImage.image3D[i][j][0] = 0;
				int count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = image3D[i+m][j+n][0] / 255;
						count++;
					}
				//Conditional
				unsigned char mask = getMask(values);
				bool hit1 = compareMask(mask, CMP_K, 40);
				if (hit1)
					MaskImage.image3D[i][j][0] = (image3D[i][j][0] && hit1);
			}
		//Loop Over --- Unconditional
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
			{
				//Construct Value Arrays
				int count = 0;
				unsigned char values[N*N];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = MaskImage.image3D[i+m][j+n][0];
						count++;
					}
				//Unconditional
				unsigned char mask = getMask(values);
				bool hit2 = compareMask(mask, UMP_SK, 444);
				image3D[i][j][0] = (image3D[i][j][0] && (!MaskImage.image3D[i][j][0] || hit2)) * 255;
			}
		//Check Finish
		finish = compareImage(result);
		//Loop Result Stored Temp
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++)
				result.image3D[i][j][0] = image3D[i][j][0];
	}
	getImage3D();
	cout << "Skeletonizing Completed. Iteration = " << iter << endl;
}

//Reverse Binary Image
void Image::imgReverse(Image result, int thresh)
{
	//Filter the Data
	for (int i = 2; i < height-2; i++)
		for (int j = 2; j < width-2; j++)
		{
			if (image3D[i][j][0] > thresh)
				result.image3D[i][j][0] = 0;
			else
				result.image3D[i][j][0] = 255;
		}
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || i == height-1 || j == 0 || j == width-1)
				result.image3D[i][j][0] = 0;
		}
	result.getImage1D();
}

//Connected Component Analysis
void Image::imgConnect(Image result, int thresh, int minRegion, bool histflag)
{
	int tag = 0;
	int parent[800] = {0};
	int region[800] = {0};
	int histog[800] = {0};
	//Histogram File
	char funcFile[50] = "Images/StarHistogram.txt";

	int imagedata[height][width][1];
	//Filter the Data
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (image3D[i][j][0] > thresh)
				imagedata[i][j][0] = 1;
			else
				imagedata[i][j][0] = 0;
		}
	//First Scan
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
		{
			if (imagedata[i][j][0] == 0)
				continue;
			//Get the Previous Pixels
			int values[4];
			values[0] = imagedata[i-1][j-1][0];
			values[1] = imagedata[i-1][j][0];
			values[2] = imagedata[i-1][j+1][0];
			values[3] = imagedata[i][j-1][0];
			//Get the Minimum Tag
			int mintag = min(values, 4);
			//Three Cases
			unsigned char status = getCase(values);
			if (status == 0)
				imagedata[i][j][0] = ++tag;
			else if (status == 1)
				imagedata[i][j][0] = mintag;
			else
			{
				imagedata[i][j][0] = mintag;
				for (int m = 0; m < 4; m++)
					if (values[m] != 0)
						unionFunc(values[m], mintag, parent);				
			}
		}
	//Max Tag Number
	int maxtag = tag;

	//Count the Child Label
	int num = 0;
	for (int i = 0; i < 800; i++)
		if (parent[i] != 0)
			num++;

	//Get the Merged Tag Numbers
	tag = tag - num;

	//Second Scan
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
			if (imagedata[i][j][0] != 0)
				imagedata[i][j][0] = findRoot(imagedata[i][j][0], parent);

	//Get the Pixel Numbers of Each Region
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (imagedata[i][j][0] != 0)
				region[imagedata[i][j][0]]++;

	//Filter too Small Pathways
	for (int i = 0; i < maxtag; i++)
		if (region[i] != 0 && region[i] < minRegion)
			tag--;

	//Get the Histogram
	if (histflag)
	{
		//Get the Histgram Data
		for (int i = 0; i < maxtag+1; i++)
			if (region[i] != 0)
				histog[region[i]]++;

		//for (int i = 0; i < 300; i++)
		//		cout << histog[i] << endl;

		//Write the Histogram File
		FILE* FuncFile = fopen(funcFile, "wb");
		for (int j = 0; j < maxtag; j++)
			fprintf(FuncFile, "%d ", histog[j]);
		fclose(FuncFile);
	}

	//Write File into Result
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
			result.image3D[i][j][0] = (unsigned char)imagedata[i][j][0];
	
	cout << "Counting Done." << endl;
	cout << "The Number of Distinct Objects is " << tag << endl;
}


void Image::countPoints(Image original)
{
	int num = 0;
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
		{
			if (image3D[i][j][0] == 0 || original.image3D[i][j][0] == 0)
				continue;
			//Count Individual Pixels
			int sum = 0;
			for (int m = -1; m <= 1; m++)
				for (int n = -1; n <= 1; n++)
					sum += image3D[i+m][j+n][0];
			//Surrounding Pixels are 0
			if (sum == 255)
				num++;
		}
	cout << "The Number of Holes is " << num << endl;
}

//Find the Center and Radius of Gear
void Image::analyzeGear(Image original, Image reverse, Image miss, Image thin)
{
	int index = 0;
	float x_center = 0.0;
	float y_center = 0.0;
	int radius = 0;
	int first_y = 0;
	int x_coords[4] = {0};
	int y_coords[4] = {0};
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			//If the Black Pixels, Skip
			if (image3D[i][j][0] == 0)
				continue;
			//Count Individual Pixels
			int sum = 0;
			for (int m = -1; m <= 1; m++)
				for (int n = -1; n <= 1; n++)
					sum += image3D[i+m][j+n][0];
			//Surrounding Pixels are 0
			if (sum == 255)
			{
				x_coords[index] = j;
				y_coords[index] = i;
				index++;
			}
		}
	//Compute the Center
	x_center = (x_coords[0] + x_coords[1] + x_coords[2] + x_coords[3]) / 4;
	y_center = (y_coords[0] + y_coords[1] + y_coords[2] + y_coords[3]) / 4;

	//Compute the Out Side Radius
	bool found = false;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			if (original.image3D[i][j][0] == 255)
			{
				first_y = i;
				found = true;
				break;
			}
		if (found)
			break;
	}
	radius = y_center - first_y;

	//Locate the teethes Position
	thin.teethLocate(reverse, x_center, y_center, radius);

	reverse.image3D[(int)y_center][(int)x_center][0] = 255;
	original.findTeeth(miss, x_center, y_center, radius);

	//Output On the Screen
	cout << "The Center of the Gear is (" << x_center << "," << y_center << ")." << endl;
	cout << "The Out Radius of the Gear is " << radius << "." << endl;
}

//Locate the Teeth
void Image::teethLocate(Image result, double x_center, double y_center, double radius)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			double dist = sqrt((i-y_center) * (i-y_center) + (j-x_center) * (j-x_center));
			if (image3D[i][j][0] == 0 || abs(dist - radius + 11) > 0.5)
				continue;
			cout << "The Teeth Location is (" << i << "," << j << ")" << endl;
			result.image3D[i][j][0] = 255;
			//Chek the Teeth Besides it Construct the Vector
			int x = round((j - x_center) * 0.866 - (y_center - i) * 0.5 + x_center);
			int y = round(y_center - (j - x_center) * 0.5 - (y_center - i) * 0.866);
			if (result.image3D[x][y][0] == 255)
			{
				cout << "The Missing Teeth Location is (" << x << "," << y << ")" << endl;
				result.image3D[x][y][0] = 0;
			}
		}
	result.imgReverse(result, 128);
}

//Find the missing Teeth
void Image::findTeeth(Image result, double x_center, double y_center, double radius)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			result.image3D[i][j][0] = image3D[i][j][0];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			double dist = sqrt((i-y_center) * (i-y_center) + (j-x_center) * (j-x_center));
			double sin_angle = abs(i - y_center) / dist;
			//Too far or not missing
			if (dist > radius ||image3D[i][j][0] > 128 || dist < 90)
				continue;
			//If the pixel not in 0-5, 25-35, 55-65, 85-90 Ignore
			if (!(sin_angle < 0.084 || (sin_angle > 0.44 && sin_angle < 0.56) || (sin_angle > 0.84 && sin_angle < 0.89) || sin_angle > 0.998))
				continue;
			result.image3D[i][j][0] = 0;
		}
}

//Count Stars
void Image::countStar(Image shrink)
{
	int x_coord[200] = {0};
	int y_coord[200] = {0};
	int star_count[200] = {0};
	int histog[300] = {0};

	//Filter the Data
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (image3D[i][j][0] > 128)
				image3D[i][j][0] = 255;
			else
				image3D[i][j][0] = 0;
		}
	//Get the coordinates of Stars
	int num = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (shrink.image3D[i][j][0] == 255)
			{
				x_coord[num] = i;
				y_coord[num] = j;
				num++;
			}
		}
	cout << "The number of the stars is " << num << endl;
	//Check which Star the pixel Belongs to
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (image3D[i][j][0] == 255)
			{
				int index = 0;
				double mindist = 500;
				for (int k = 0; k < num; k++)
				{
					double dist = sqrt((i-x_coord[k]) * (i-x_coord[k]) + (j-y_coord[k]) * (j-y_coord[k]));
					if (dist < mindist)
					{
						mindist = dist;
						index = k;
					}
				}
				star_count[index]++;
			}
		}
	//Get the Histgram Data
	for (int i = 0; i < num; i++)
		if (star_count[i] != 0)
			histog[star_count[i]]++;

	//for (int i = 0; i < 300; i++)
	//		cout << histog[i] << endl;

	char funcFile[50] = "Images/StarHistogram2.txt";
	//Write the Histogram File
	FILE* FuncFile = fopen(funcFile, "wb");
	for (int j = 0; j < 300; j++)
		fprintf(FuncFile, "%d ", histog[j]);
	fclose(FuncFile);
}

//Counting Using the DFS Algorithm
/*
void helper(int imagedata[][640], int height, int width, int i, int j, int& cnt, int& res) {
    int m = height, n = width;
    if (i < 0 || i >= height || j < 0 || j >= width || imagedata[i][j] <= 0) return;
    res = max(res, ++cnt);
    imagedata[i][j] = -1;
    helper(imagedata, height, width, i - 1, j, cnt, res);
    helper(imagedata, height, width, i + 1, j, cnt, res);
    helper(imagedata, height, width, i, j - 1, cnt, res);
    helper(imagedata, height, width, i, j - 1, cnt, res);
    helper(imagedata, height, width, i - 1, j - 1, cnt, res);
    helper(imagedata, height, width, i - 1, j + 1, cnt, res);
    helper(imagedata, height, width, i + 1, j - 1, cnt, res);
    helper(imagedata, height, width, i + 1, j + 1, cnt, res);
}

int maxAreaOfIsland(int imagedata[][640], int height, int width) 
{
    int res = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (imagedata[i][j] != 1) continue;
            int cnt = 0;
            helper(imagedata, height , width, i, j, cnt, res);
        }
    }
    return res;
}

void helper1(int imagedata[][640], int height, int width, bool visited[][640], int i, int j) 
{
    if (i < 0 || i >= height || j < 0 || j >= width || imagedata[i][j] == 0 || visited[i][j]) return;
    visited[i][j] = true;
    helper1(imagedata, height, width, visited, i - 1, j);
    helper1(imagedata, height, width, visited, i + 1, j);
    helper1(imagedata, height, width, visited, i, j - 1);
    helper1(imagedata, height, width, visited, i, j + 1);
    helper1(imagedata, height, width, visited, j - 1, j - 1);
    helper1(imagedata, height, width, visited, i + 1, j - 1);
    helper1(imagedata, height, width, visited, i - 1, j + 1);
    helper1(imagedata, height, width, visited, i + 1, j + 1);
}

int numIslands(int imagedata[][640], int height, int width) 
{
	int res = 0;
	bool visited[height][640];
	for (int i = 0; i < height; ++i) {
	    for (int j = 0; j < width; ++j) {
	        if (imagedata[i][j] == 0 || visited[i][j]) continue;
	        helper1(imagedata, height, width, visited, i, j);
	        ++res;
	    }
	}
	return res;
}

void Image::imgConnect(Image result)
{
	//vector<vector<int>> imagedata[height][width];
	//Filter the Data
	int imagedata[height][640];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (image3D[i][j][0] > 200)
			{
				imagedata[i][j] = 1;
				result.image3D[i][j][0] = 255;
			}
			else
			{
				imagedata[i][j]= 0;
				result.image3D[i][j][0] = 0;
			}
		}
	int res = numIslands(imagedata, height, width);
	cout << res << endl;
}   
*/

















