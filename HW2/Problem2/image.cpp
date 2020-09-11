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

int generate(int N, int i, int j)
{
	if (N == 2)
	{
		if (i == 0 && j == 0)
			return 1;
		if (i == 0 && j == 1)
			return 2;
		if (i == 1 && j == 0)
			return 3;
		if (i == 1 && j == 1)			
			return 0;
	}
	else
	{
		if (i < N/2 && j < N/2)
			return 4 * generate(N/2, i, j) + 1;
		if (i < N/2 && j >= N/2)
			return 4 * generate(N/2, i, j-N/2) + 2;
		if (i >= N/2 && j < N/2)
			return 4 * generate(N/2, i-N/2, j) + 3;
		if (i >= N/2 && j >= N/2)		
			return 4 * generate(N/2, i-N/2, j-N/2);
	}
	return -1;
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

//Copy the Image Data From 3D-Extended into Double
double*** Image::copy2double(int pad_width)
{
	double*** Img = new double **[height + 2 * pad_width]();
	for (int i = 0; i < height + 2 * pad_width; i++)
	{
		Img[i] = new double*[width + 2 * pad_width]();
		for (int j = 0; j < width + 2 * pad_width; j++)
		{
			Img[i][j] = new double[bpp]();
			for (int k = 0; k < bpp; k++)
				Img[i][j][k] = 0;
		}
	}

	//Copy
	for (int i = 0; i < height + 2 * pad_width; i++)
		for (int j = 0; j < width + 2 * pad_width; j++)
			for (int k = 0; k < bpp; k++)
			{
				Img[i][j][k] = image3D_Extended[i][j][k];
			}
	return Img;
}

//Transfer the Image Between RGB and CMY space
void Image::transferSpaces(Image result)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < bpp; k++)
				result.image3D[i][j][k] = 255 - image3D[i][j][k];
	cout << "Image Has Been Transfered to RGB or CMY Space." << endl;
}

//Find the Pyramid Of MBVQ
/*
	1. CMYW;
	2. MYGC;
	3. RGMY;
	4. KRGB;
	5. RGBM;
	6. CMGB;
*/
int Image::findPyramid(double RGB[])
{
	//Extract Three Colors
	double R = RGB[0];
	double G = RGB[1];
	double B = RGB[2];

	//Get the Corresponding Pyramid
	if((R+G) > 255)
		if((G+B) > 255)
			if((R+G+B) > 510)
				return 1;
			else
				return 2;
		else
			return 3;
	else
		if(!((G+B) > 255))
			if(!((R+G+B) > 255))
				return 4;
			else
				return 5;
		else
			return 6;
}

//Find the Vertex Of the Pixel
/*
	1. White
	2. Yellow;
	3. Cyan;
	4. Magenta;
	5. Green;
	6. Red;
	7. Blue;
	8. Black
*/
int Image::findVertex(int pyramid, double thresh, double RGB[])
{
	//Extract Three Colors
	double R = RGB[0];
	double G = RGB[1];
	double B = RGB[2];

	switch(pyramid)
	{
		//In the CMYW Pyramid
		case 1:
			if (R < thresh)
				if (R <= G)
					if (R <= B)
						return 3;	//Cyan
			if (G < thresh)
				if (G <= R)
					if (G <= B)
						return 4;	//Magenta
			if (B < thresh)
				if (B <= R)
					if (B <= G)
						return 2;	//Yellow
			return 1;				//White

		//In the MYGC Pyramid
		case 2:
			if (G >= B)
				if (R >= B)
				{
					if (R >= thresh)
						return 2;	//Yellow
					else
						return 5;	//Green
				}
			if (G >= R)
				if (B >= R)
				{
					if (B >= thresh)
						return 3;	//Cyan
					else
						return 5;	//Green
				}
			return 4;				//Magenta

		//In the RGMY Pyramid
		case 3:
			if (B > thresh)
            	if (R > thresh)
            	{
                	if (B >= G)
                    	return 4;	//Magenta
                	else
                    	return 2;	//Yellow
                }
            	else
            	{
                	if (G > B + R)
                    	return 5;	//Green
               		else 
                    	return 4;	//Magenta
                }
        	else
	            if (R >= thresh)
	            {
	                if (G >= thresh)
	                    return 2;	//Yellow
	                else
	                    return 6;	//Red
	            }
	            else
	            {
	                if (R >= G)
	                    return 6;	//Red
	                else
	                    return 5;	//Green
	            }

	    //In the KRGB Pyramid
		case 4:
			if (B > thresh)
				if (B >= R)
					if (B >= G)
						return 7;	//Blue
			if (G > thresh)
				if (G >= B)
					if (G >= R)
						return 5;	//Green
			if (R > thresh)
				if (R >= B)
					if (R >= G)
						return 6;	//Red
			return 8;				//Black

		//In the RGBM Pyramid
		case 5:
			if (R > G)
				if (R >= B)
				{
					if (B < thresh)
						return 6;	//Red
					else
						return 4;	//Magenta
				}
			if (B > G)
				if (B >= R)
				{
					if (R < thresh)
						return 7;	//Blue
					else
						return 4;	//Magenta
				}
			return 5;				//Green

		//In the CMGB Pyramid
		case 6:
			if (B > thresh)
				if (R > thresh)
				{
					if (G >= R)
						return 3;	//Cyan
					else
						return 4;	//Magenta
				}
				else
				{
					if (G > thresh)
						return 3;	//Cyan
					else
						return 7;	//Blue
				}
			else
				if (R > thresh)
				{
					if (R - G + B >= thresh)
						return 4;	//Magenta
					else
						return 5;	//Green
				}
				else
				{
					if (G >= B)
						return 5;	//Green
					else
						return 7;	//Blue
				}
	}
	//If Wrong Return -1
	return -1;
}

//Set the Color from Vertex
double* Image::getColors(int vertex)
{
	/*
		1. White
		2. Yellow;
		3. Cyan;
		4. Magenta;
		5. Green;
		6. Red;
		7. Blue;
		8. Black
	*/
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
	switch(vertex)
	{
		//White
		case 1:
			R = 255.0;
			G = 255.0;
			B = 255.0;
			break;
		//Yellow
		case 2:
			R = 255.0;
			G = 255.0;
			B = 0.0;
			break;
		//Cyan
		case 3:
			R = 0.0;
			G = 255.0;
			B = 255.0;
			break;
		//Magenta
		case 4:
			R = 255.0;
			G = 0.0;
			B = 255.0;
			break;
		//Green
		case 5:
			R = 0.0;
			G = 255.0;
			B = 0.0;
			break;
		//Red
		case 6:
			R = 255.0;
			G = 0.0;
			B = 0.0;
			break;
		//Blue
		case 7:
			R = 0.0;
			G = 0.0;
			B = 255.0;
			break;
		//Black
		case 8:
			R = 0.0;
			G = 0.0;
			B = 0.0;
			break;
	}
	//Update Pixel Values
	double* RGB = new double[3]();
	RGB[0] = R;
	RGB[1] = G;
	RGB[2] = B;
	return RGB;
}

/*-------------------Problems Methods--------------------------------*/

//Sobel Edge Detector
void Image::sobelEdge(Image result, Image grayX, Image grayY, double ratio)
{
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
	for (int k = 0; k < bpp; k++)
		for (int i = 1; i < height + 1; i++)
			for (int j = 1; j < width + 1; j++)
			{
				//Construct the Values Array
				int count = 0;
				unsigned char values[9];
				for (int p = -pad_width; p <= pad_width; p++)
					for (int l = -pad_width; l <= pad_width; l++)
					{
						values[count] = image3D_Extended[i+p][j+l][k];
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
			result.image3D[i][j][0] = (unsigned char)gradient[i][j];
		}

	//Sort the Pixel Values
	int count = 0;
	int sortArray[height * width];
	for (int k = 255; k >= 0; k--)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (result.image3D[i][j][0] == k)
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
			result.image3D[row][col][0] = 0;
		else
			result.image3D[row][col][0] = 255;
	}
}

//Half toning Fixed 
void Image::toneFixed(Image result, unsigned char thresh)
{
	for (int k = 0; k < bpp; k++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (image3D[i][j][k] < thresh)
					result.image3D[i][j][k] = 0;
				else
					result.image3D[i][j][k] = 255;
			}
	cout << "Toned by Fixed Threshold Completed." << endl;
}

//Half toning Random
void Image::toneRand(Image result, unsigned char tSeed)
{
	//Initialize the time seed
	srand(tSeed);
	for (int k = 0; k < bpp; k++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				unsigned char thresh = rand() % 256;
				if (image3D[i][j][k] < thresh)
					result.image3D[i][j][k] = 0;
				else
					result.image3D[i][j][k] = 255;
			}
	cout << "Toned by Random Completed." << endl;
}

//Half toning Dithering Matrix
void Image::toneDither(Image result, int N)
{
	//Check the Input
	if (log2(N)-(int)log2(N) != 0)
	{
		cout << "Log(N) Should Be Integer." << endl;
		return;
	}

	//Construct the Threshold Matrix
	int intensity[N][N];
	double thresh[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			intensity[i][j] = generate(N, i, j);
			thresh[i][j] = (intensity[i][j] + 0.5) * 255 / (N * N) ;
		}

	//Loop the Pixel
	for (int k = 0; k < bpp; k++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				int tempi = i % N;
				int tempj = j % N;
				if (image3D[i][j][k] <= thresh[tempi][tempj])
					result.image3D[i][j][k] = 0;
				else
					result.image3D[i][j][k] = 255;
			}
	cout << "Toned by Dithering Completed." << endl;
}

//Error Diffusion Floyd-Steinberg
void Image::errorFS(Image result, double thresh)
{
	//Image Extension
	int pad_width = imgPadding(3);

	//Copy the Image Data into Double Array
	double*** imageData = copy2double(pad_width);

	//Loop the Image
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
		{
			if (i % 2 == 1)
				for (int j = pad_width; j < width + pad_width; j++)
				{
					//Construct the Filter
					double filter_FS_ori[9] = {0, 0, 0, 0, 0, 7, 3, 5, 1};

					//Construct Value Arrays
					int count = 0;
					double error = 0;
					double values[9];
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							values[count] = imageData[i+m][j+n][k];
							count++;
						}

					//Compute the Error
					if (values[4] > thresh)
					{
						error = (values[4] - 255) / 16;
						values[4] = 255;
					}
					else
					{
						error = values[4] / 16;
						values[4] = 0;
					}

					//Reassign the Filter Values
					for (int m = 0; m < 9; m++)
					{
						filter_FS_ori[m] = filter_FS_ori[m] * error;
						values[m] = values[m] + filter_FS_ori[m];
					}

					//Update Pixel Values
					count = 0;
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							imageData[i+m][j+n][k] = values[count];
							count++;
						}
				}
			else
				for (int j = width + pad_width - 1; j >= pad_width ; j--)
				{
					//Construct the Filter
					double filter_FS_flp[9] = {0, 0, 0, 7, 0, 0, 1, 5, 3};

					//Construct Value Arrays
					int count = 0;
					double error = 0;
					double values[9];
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							values[count] = imageData[i+m][j+n][k];
							count++;
						}

					//Compute the Error
					if (values[4] > thresh)
					{
						error = (values[4] - 255) / 16;
						values[4] = 255;
					}
					else
					{
						error = values[4] / 16;
						values[4] = 0;
					}

					//Reassign the Filter Values
					for (int m = 0; m < 9; m++)
					{
						filter_FS_flp[m] = filter_FS_flp[m] * error;
						values[m] = values[m] + filter_FS_flp[m];
					}

					//Update Pixel Values
					count = 0;
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							imageData[i+m][j+n][k] = values[count];
							count++;
						}
				}
		}

	//Copy the Imagedata into Result
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
			for (int j = pad_width; j < width + pad_width; j++)
				result.image3D[i-pad_width][j-pad_width][k] = (unsigned char)imageData[i][j][k];

	cout << "Error Diffusion by Floyd-Steinberg Completed." << endl;
}

//Error Diffusion
void Image::errorDiff(Image result, double thresh, int N, int deno, double filter_ori[], double filter_flp[])
{
	//Image Extension
	int pad_width = imgPadding(N);

	//Copy the Image Data into Double Array
	double*** imageData = copy2double(pad_width);

	//Loop the Image
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
		{
			if ((i - pad_width) % 2 == 0)
				for (int j = pad_width; j < width + pad_width; j++)
				{
					//Construct Value Arrays
					int count = 0;
					double values[N*N];
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							values[count] = imageData[i+m][j+n][k];
							count++;
						}

					//Compute the Error
					int index = (int)(N * N / 2);
					double error = values[index] > thresh ? (values[index] - 255) / deno : values[index] / deno;
					values[index] = values[index] > thresh ? 255 : 0;

					//Reassign the Filter Values
					for (int m = 0; m < N*N; m++)
						values[m] += filter_ori[m] * error;

					//Update Pixel Values
					count = 0;
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							imageData[i+m][j+n][k] = values[count];
							count++;
						}
				}
			else
				for (int j = width + pad_width -1; j >= pad_width; j--)
				{
					//Construct Value Arrays
					int count = 0;
					double values[N*N];
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							values[count] = imageData[i+m][j+n][k];
							count++;
						}

					//Compute the Error
					int index = (int)(N * N / 2);
					double error = values[index] > thresh ? (values[index] - 255) / deno : values[index] / deno;
					values[index] = values[index] > thresh ? 255 : 0;

					//Reassign the Filter Values
					for (int m = 0; m < N*N; m++)
						values[m] += filter_flp[m] * error;

					//Update Pixel Values
					count = 0;
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							imageData[i+m][j+n][k] = values[count];
							count++;
						}
				}
		}

	//Copy the Imagedata into Result
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
			for (int j = pad_width; j < width + pad_width; j++)
				result.image3D[i-pad_width][j-pad_width][k] = (unsigned char)imageData[i][j][k];

	cout << "Error Diffusion Completed." << endl;
}


//MBVQ Method
void Image::MBVQ_errDiff(Image result, double thresh, int N, int deno, double filter_ori[], double filter_flp[])
{
	//Image Extension
	int pad_width = imgPadding(N);

	//Copy the Image Data into Double Array
	double*** imageData = copy2double(pad_width);

	//Loop the Image
	for (int i = pad_width; i < height + pad_width; i++)
	{
		if ((i - pad_width) % 2 == 0)
			for (int j = pad_width; j < width + pad_width; j++)
			{
				//Compute the Pyramid, Vertex and Color
				double RGB[3] = {imageData[i][j][0], imageData[i][j][1], imageData[i][j][2]};
				int pyramid = findPyramid(RGB);
				int vertex = findVertex(pyramid, thresh, RGB);
				double* new_pix = getColors(vertex);

				for (int k = 0; k < bpp; k++)
				{
					//Construct Value Arrays
					int count = 0;
					double values[N*N];
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							values[count] = imageData[i+m][j+n][k];
							count++;
						}

					//Compute the Error
					int index = (int)(N * N / 2);
					double error = (values[index] - new_pix[k]) / (double)deno;
					values[index] = new_pix[k];

					//Reassign the Filter Values
					for (int m = 0; m < N*N; m++)
						values[m] += filter_ori[m] * error;

					//Update Pixel Values
					count = 0;
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							imageData[i+m][j+n][k] = values[count];
							count++;
						}
				}

			}
		else
			for (int j = width + pad_width -1; j >= pad_width; j--)
			{
				//Compute the Pyramid, Vertex and Color
				double RGB[3] = {imageData[i][j][0], imageData[i][j][1], imageData[i][j][2]};
				int pyramid = findPyramid(RGB);
				int vertex = findVertex(pyramid, thresh, RGB);
				double* new_pix = getColors(vertex);

				for (int k = 0; k < bpp; k++)
				{
					//Construct Value Arrays
					int count = 0;
					double values[N*N];
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							values[count] = imageData[i+m][j+n][k];
							count++;
						}

					//Compute the Error
					int index = (int)(N * N / 2);
					double error = (values[index] - new_pix[k]) / (double)deno;
					values[index] = new_pix[k];

					//Reassign the Filter Values
					for (int m = 0; m < N*N; m++)
						values[m] += filter_flp[m] * error;

					//Update Pixel Values
					count = 0;
					for (int m = -pad_width; m <= pad_width; m++)
						for (int n = -pad_width; n <= pad_width; n++)
						{
							imageData[i+m][j+n][k] = values[count];
							count++;
						}
				}
			}
	}

	//Copy the Imagedata into Result
	for (int k = 0; k < bpp; k++)
		for (int i = pad_width; i < height + pad_width; i++)
			for (int j = pad_width; j < width + pad_width; j++)
				result.image3D[i-pad_width][j-pad_width][k] = (unsigned char)imageData[i][j][k];

	cout << "Error Diffusion by MBVQ Completed." << endl;
}







