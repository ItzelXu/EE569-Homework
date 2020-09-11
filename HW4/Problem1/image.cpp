//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/22/2020

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iomanip> 
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>  
#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/core.hpp>
#include "image.h"

#define _USE_MATH_DEFINES

#define TEST_SIZE 3
#define TRAIN_SIZE 9
#define TOTAL_SIZE 12
#define SAMPLE_SIZE 36

using namespace std;
using namespace cv;

//using namespace cv::ml;

//1D Filters
int FILTER1D[5][5] = 
{
	//L5
	{1, 4, 6, 4, 1},
	//E5
	{-1, -2, 0, 2, 1},
	//S5
	{-1, 0, 2, 0, -1},
	//W5
	{-1, 2, 0, -2, 1},
	//R5
	{1, -4, 6, -4, 1}
};

//2D Filters
int FILTER2D[25][25] = {0};

//Generate the Filters
void genFilters()
{
	int count = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			int num = 0;
			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
				{
					FILTER2D[count][num] = FILTER1D[i][m] * FILTER1D[j][n];
					num++;
				}
			count++;
		}
}

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

//Convolution - Reload
double convolute(int* filter, double value[], int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum = sum + value[i] * filter[i];
	return sum;
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
Image::Image()
{
}
//Constructor2
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

//Allocate 1D array Double
double* Image::allocate_1D_Double(int width, int height, int bpp)
{
	int pixCount = width * height * bpp;
	double* Img = new double[pixCount]();
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

//Allocate 2D array Double
double** Image::allocate_2D_Double(int width, int height)
{
	double** Img = new double *[height]();
	for (int i = 0; i < height; i++)
	{
		Img[i] = new double[width];
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

//Allocate 3D array double
double*** Image::allocate_3D_Double(int width, int height, int bpp)
{
	double*** Img = new double **[height]();
	for (int i = 0; i < height; i++)
	{
		Img[i] = new double*[width]();
		for (int j = 0; j < width; j++)
		{
			Img[i][j] = new double[bpp]();
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
	image3D_Double = allocate_3D_Double(width, height, bpp);
	histo3D = initHisto(bpp);
	genFilters();
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
	//cout << "File Read Successfully." << endl;
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

//Extend the Image Boundary by Reflection - Double
int Image::imgPaddingDouble(int N)
{
	if (!(N % 2))
	{
		cout << "The Window Size Cannot Be Even." << endl;
		return -1;
	}
	//Define the Padding width
	int pad_width = (N-1) / 2;

	//Initialize the Array for Storing the Image
	image3D_Extended_Double = allocate_3D_Double(width + 2 * pad_width, height + 2 * pad_width, bpp);

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
						image3D_Extended_Double[i][j][k] = image3D_Double[pad_width-1-i][pad_width-1-j][k];
					//Upper Boundary
					else if (j < width + pad_width)
						image3D_Extended_Double[i][j][k] = image3D_Double[pad_width-1-i][j-pad_width][k];
					//Upper-Right Corner
					else
						image3D_Extended_Double[i][j][k] = image3D_Double[pad_width-1-i][2*width+pad_width-j-1][k];
				}
				//Left and Right Boundary 
				else if (i < height + pad_width)
				{
					//Left Boundary
					if (j < pad_width)
						image3D_Extended_Double[i][j][k] = image3D_Double[i-pad_width][pad_width-1-j][k];
					//Image Data
					else if (j < width + pad_width)
						image3D_Extended_Double[i][j][k] = image3D_Double[i-pad_width][j-pad_width][k];
					//Right Boundary
					else
						image3D_Extended_Double[i][j][k] = image3D_Double[i-pad_width][2*width+pad_width-j-1][k];
				}
				//Lower Boundary and Corners
				else
				{
					//Lower-Left Corner
					if (j < pad_width)
						image3D_Extended_Double[i][j][k] = image3D_Double[2*height+pad_width-i-1][pad_width-1-j][k];
					//Lower Boundary
					else if (j < width + pad_width)
						image3D_Extended_Double[i][j][k] = image3D_Double[2*height+pad_width-i-1][j-pad_width][k];
					//Lower-Right Corner
					else
						image3D_Extended_Double[i][j][k] = image3D_Extended_Double[i][2*width+2*pad_width-j-1][k];
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
	//cout << "Image Extended Successfully." << endl;
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

//Extend the Image Boundary by Zero
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

//===============================Homework4==================================//

//Show the Matrix to Check
void Image::printMatrix(double** matrix, int len1, int len2)
{
	for (int i = 0; i < len1; i++)
	{
		for (int j = 0; j < len2; j++)
			cout << setprecision(5) << matrix[i][j] << " ";
		cout << endl;
	}
}

//Subtract the Global Mean of the Image
void Image::meanSubtract()
{
	//Normalize the Image
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			image3D_Double[i][j][0] = (double)image3D[i][j][0] / 255;
	//Compute the Mean
	double sum = 0;
	double mean = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			sum = sum + image3D_Double[i][j][0];
	mean = sum / (height * width);
	//Assign the Double Value
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			image3D_Double[i][j][0] = image3D_Double[i][j][0] - mean;
	//cout << "Image Mean Subtracted Successfully." << endl;
}

//Get Absolute Values
void Image::absoluteValues(double*** image3D_D, int layers)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < layers; k++)
				//image3D_D[i][j][k] = image3D_D[i][j][k] * image3D_D[i][j][k];
				image3D_D[i][j][k] = abs(image3D_D[i][j][k]);
	//cout << "Image Sqaured Positive Successfully." << endl;
}

//Calculate Standard Deviation
double* Image::calcSTD(double **features, int size)
{
	double* stds = allocate_1D_Double(15, 1, 1);
	for (int i = 0; i < 15; i++)
	{
		//Calculate the Mean of Each Feature
		double sum = 0;
		double std = 0;
		double mean = 0;
		for (int j = 0; j < size; j++)
			sum += features[j][i];
		mean = sum / size;
		//Calculate the Variance of Each Feature
		sum = 0;
		double var = 0;
		for (int j = 0; j < size; j++)
			sum += pow(features[j][i] - mean, 2);
		std = sum / size;
		stds[i] = sqrt(std);
		//cout << stds[i] << endl;
	}
	return stds;
}

//Calculate Squared Deviation
double* Image::calcSQD(double **features, int size)
{
	double* stds = allocate_1D_Double(15, 1, 1);
	for (int i = 0; i < 15; i++)
	{
		double sum = 0;
		double mean[4];
		double global_mean = 0;
		for (int j = 0; j < size; j++)
			sum += features[j][i];
		global_mean = sum / size;
		//class1
		sum = 0;
		for (int j = 0; j < 9; j++)
			sum += features[j][i];
		mean[0] = sum / 9;
		//class2
		sum = 0;
		for (int j = 9; j < 18; j++)
			sum += features[j][i];
		mean[1] = sum / 9;
		//class3
		sum = 0;
		for (int j = 18; j < 27; j++)
			sum += features[j][i];
		mean[2] = sum / 9;
		//class4
		sum = 0;
		for (int j = 27; j < 36; j++)
			sum += features[j][i];
		mean[3] = sum / 9;
		//inter-class
		double inter = pow(mean[0]-global_mean, 2) + pow(mean[1]-global_mean, 2) + pow(mean[2]-global_mean, 2) + pow(mean[3]-global_mean, 2);
		//intra-vlass
		double intra = 0;
		for (int j = 0; j < size; j++)
		{
			if (j < 9)
				intra += pow(features[j][i]-mean[0], 2);
			else if (j < 18)
				intra += pow(features[j][i]-mean[1], 2);
			else if (j < 27)
				intra += pow(features[j][i]-mean[2], 2);
			else
				intra += pow(features[j][i]-mean[3], 2);
		}

		stds[i] = inter / intra;

	}
	return stds;
}

//Shrink the Features into 15D
double** Image::getFeatures15D(double **features, int size, bool normflag)
{
	//Shrink to 15 Dimensional Features
	double** features15D = allocate_2D_Double(15, size);
	for (int i = 0; i < size; i++)
	{
		features15D[i][0] = features[i][0];
		features15D[i][1] = (features[i][1] + features[i][5]) / 2;
		features15D[i][2] = (features[i][7] + features[i][11]) / 2;
		features15D[i][3] = features[i][6];
		features15D[i][4] = (features[i][2] + features[i][10]) / 2;
		features15D[i][5] = (features[i][8] + features[i][16]) / 2;
		features15D[i][6] = features[i][12];
		features15D[i][7] = (features[i][3] + features[i][15]) / 2;
		features15D[i][8] = (features[i][9] + features[i][21]) / 2;
		features15D[i][9] = features[i][18];
		features15D[i][10] = (features[i][4] + features[i][20]) / 2;
		features15D[i][11] = (features[i][13] + features[i][17]) / 2;
		features15D[i][12] = features[i][24];
		features15D[i][13] = (features[i][19] + features[i][23]) / 2;
		features15D[i][14] = (features[i][14] + features[i][22]) / 2;
		//Normalization
		if (normflag)
		{
			for (int j = 0; j < 15; j++)
				features15D[i][j] = features15D[i][j] / features[i][0];
		}
	}
	return features15D;
}

//Feature Extraction
double* Image::featureExtract()
{
	//Image Mean Subtract
	meanSubtract();
	//Image Extension
	int pad_width = imgPaddingDouble(5);
	//Image Features Initialization
	double* features = allocate_1D_Double(5, 5, 1);
	//Apply 2D Filters Get Features
	for (int f = 0; f < 25; f++)
	{
		//Apply Different Filters
		for (int i = pad_width; i < height - pad_width; i++)
			for (int j = pad_width; j < width - pad_width; j++)
			{
				//Construct the Values Array
				int count = 0;
				double values[25];
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = image3D_Extended_Double[i+m][j+n][0];
						count++;
					}
				//Convolution
				image3D_Double[i-pad_width][j-pad_width][0] = convolute(FILTER2D[f], values, 25);
			}
		//Get Positive Values
		absoluteValues(image3D_Double, 1);
		//Get the Features
		double sum = 0;
		double mean = 0;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				sum += image3D_Double[i][j][0];
			}
		mean = sum / (height * width);
		features[f] = sqrt(mean);
	}
	return features;
}

//PCA Function
double** Image::PCA(double** matrix, int size, int dimension)
{
	//Copy the Data
	double inputMatrix[size][dimension];
	for(int i = 0; i < size; i++)
		for(int j = 0; j < dimension; j++)
			inputMatrix[i][j] = matrix[i][j];
	//Zero Mean Features
	for(int j = 0; j < dimension; j++)
	{
		double sum = 0;
		double mean = 0;
		for(int i = 0; i < size; i++)
			sum += inputMatrix[i][j];
		mean = sum / size;
		for(int i = 0; i < size; i++)
			inputMatrix[i][j] -= mean;
	}
	//double U[size][size];
	double D[size][dimension];
	double V[dimension][dimension];
	double VR[dimension][3];
	double YR[size][3];
	double** result = allocate_2D_Double(dimension, size);
	CvMat featureMatrix = cvMat(size, dimension, CV_64FC1, inputMatrix);
	//CvMat leftMatrix = cvMat(size, size, CV_64FC1, U);
	CvMat singMatrix = cvMat(size, dimension, CV_64FC1, D);
	CvMat rigtMatrix = cvMat(dimension, dimension, CV_64FC1, V);
	CvMat ritMatrixR = cvMat(dimension, 3, CV_64FC1, VR);
	CvMat rsltMatrix = cvMat(size, 3, CV_64FC1, YR);
	cvSVD(&featureMatrix, &singMatrix, NULL, &rigtMatrix);	

	//Get the First K Vectors
	for(int i = 0; i < dimension; i++)
		for(int j = 0; j < 3; j++)
			CV_MAT_ELEM(ritMatrixR, double, i, j) = CV_MAT_ELEM(rigtMatrix, double, i, j);

	//Do the Multiplication
	cvMatMul(&featureMatrix, &ritMatrixR, &rsltMatrix);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < dimension; j++)
			result[i][j] = CV_MAT_ELEM(featureMatrix, double, i, j);

	return result;
}

//K-means
unsigned char* Image::Kmeans(double **features, int num, int size, int dimension)
{
	unsigned char* classes = allocate_1D(num, 1, 1);
	double center[num][dimension];
	//Initialize with first n positions
	int r[num];
	srand(time(0));
	for (int i = 0; i < num; i++)
	{
		r[i] = rand() % size;
		for (int j = 0; j < i; j++)
			if (r[i] == r[j])
				i--;
	}
	for (int i = 0; i < num; i++)
		for (int j = 0; j < dimension; j++)
			center[i][j] = features[r[i]][j];

	int iter = 0;
	bool finish = false;
	while(!finish)
	{
		iter++;
		//Create the Temp to Campare
		int temp[size];
		for (int i = 0; i < size; i++)
			temp[i] = classes[i];

		//Compute the Distance with Centers
		for (int i = 0; i < size; i ++)
		{
			int index = 0;
			double mindist = 9999;
			for (int k = 0; k < num; k++)
			{
				double dist = 0;
				for (int j = 0; j < dimension; j++)
					dist += (features[i][j] - center[k][j]) * (features[i][j] - center[k][j]);
				//dist = sqrt(dist);
				if (dist < mindist)
				{
					mindist = dist;
					index = k;
				}
			}
			classes[i] = (unsigned char)index;
		}

		//Update Center
		for (int i = 0; i < num; i++)
		{
			int count = 0;
			double sum[dimension];
			//Initialize
			for (int j = 0; j < dimension; j++)
				sum[j] = 0;
			//Check Tags
			for (int j = 0; j < size; j++)
			{
				if (classes[j] == i)
				{
					for (int k = 0; k < dimension; k++)
						sum[k] += features[j][k];
					count++;
				}
			}
			for (int j = 0; j < dimension; j++)
				center[i][j] = sum[j] / count;
		}
		//Check the Finish Flag
		finish = true;
		for (int i = 0; i < size; i++)
			if (classes[i] != temp[i])
			{
				finish = false;
				break;
			}
	}
	if (size < 30)
	{
		for (int i = 0; i < size; i++)
			cout << (int)classes[i] << " ";
		cout << endl;
	}
	//cout << iter << endl;
	return classes;
}

//Random Forest Function
void Image::randomForest(double **trainSet, double **testSet, double *label, int sample_size, int test_size, int dimension)
{
	//using namespace cv;
	//Copy the Data
	float trainData[sample_size][dimension];
	float labelData[sample_size];
	float testData[sample_size][dimension];
	float result[test_size];
	for(int i = 0; i < sample_size; i++)
	{
		for(int j = 0; j < dimension; j++)
			trainData[i][j] = (float)trainSet[i][j];
		labelData[i] = (float)label[i];
	}
	for(int i = 0; i < test_size; i++)
		for(int j = 0; j < dimension; j++)
			testData[i][j] = (float)testSet[i][j];
	//Construct CV Matrix
	//cv::Mat testDataSet = cv::Mat(test_size, 3, CV_64FC1, testData);
	CvMat labelDataSet = cvMat(sample_size, 1, CV_32FC1, labelData);
	CvMat trainDataSet = cvMat(sample_size, dimension, CV_32FC1, trainData);
	//Parameters Configuration
    CvERTrees etrees;
	//CvRTParams params= CvRTParams(35, 1, 0.0001f, false, 4, 0, false, 0, 100, 0.0001f, CV_TERMCRIT_EPS); //2 Wrong
	CvRTParams params = CvRTParams(20, 1, 0.0001f, false, 4, 0, false, 0, 100, 0.0001f, CV_TERMCRIT_EPS);
	//Train
    etrees.train(&trainDataSet, CV_ROW_SAMPLE, &labelDataSet, NULL, NULL, NULL, NULL, params); 
    //Predict
    cout << "-----------------------------" << endl;
    for (int i = 0; i < test_size; i++)
    {
    	float sampleData[dimension];
    	for (int j = 0; j < dimension; j++)
    		sampleData[j] = testData[i][j];
    	cv::Mat sampleMat = cv::Mat(dimension, 1, CV_32FC1, sampleData);
    	result[i] = etrees.predict(sampleMat);  
    	cout << result[i] << " ";
    }
    cout << endl;
}

//Support Vector Machine
void Image::SupportVectorMachine(double **trainSet, double **testSet, double *label, int sample_size, int test_size, int dimension)
{
	//using namespace cv;
	//Copy the Data
	float trainData[sample_size][dimension];
	float labelData[sample_size];
	float testData[sample_size][dimension];
	float result[test_size];
	for(int i = 0; i < sample_size; i++)
	{
		for(int j = 0; j < dimension; j++)
			trainData[i][j] = (float)trainSet[i][j];
		labelData[i] = (float)label[i];
	}
	for(int i = 0; i < test_size; i++)
		for(int j = 0; j < dimension; j++)
			testData[i][j] = (float)testSet[i][j];
	//Construct CV Matrix
	//cv::Mat testDataSet = cv::Mat(test_size, 3, CV_64FC1, testData);
	CvMat labelDataSet = cvMat(sample_size, 1, CV_32FC1, labelData);
	CvMat trainDataSet = cvMat(sample_size, dimension, CV_32FC1, trainData);
	//Parameters Configuration
	CvSVMParams params;
	CvTermCriteria criteria; 
   	criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);  
	params = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 8.0, 1.0, 10.0, 0.5, 0.0001, NULL, criteria); 
	//Train
    CvSVM SVM;
    SVM.train(&trainDataSet, &labelDataSet, NULL, NULL, params);
    //Predict
    cout << "-----------------------------" << endl;
    for (int i = 0; i < test_size; i++)
    {
    	float sampleData[dimension];
    	for (int j = 0; j < dimension; j++)
    		sampleData[j] = testData[i][j];
    	cv::Mat sampleMat = cv::Mat(dimension, 1, CV_32FC1, sampleData);
    	result[i] = SVM.predict(sampleMat);
    	cout << result[i] << " ";
    }
    cout << endl;
}

//Segmentation Function
void Image::imgSegment(Image result, int wndsize, int num, bool flag3D)
{
	//Image Mean Subtract
	meanSubtract();
	//Image Extension
	int pad_width = imgPaddingDouble(5);
	//Copy the Data
	double*** temp = image3D_Extended_Double;
	//Image Features Initialization
	double*** img_feature25D = allocate_3D_Double(width, height, 25);
	double*** img_feature15D = allocate_3D_Double(width, height, 15);
	double** img_feature14D = allocate_2D_Double(14, width * height);
	//STEP1 :Different Filters
	for (int f = 0; f < 25; f++)
		//Apply Different Filters
		for (int i = pad_width; i < height + pad_width; i++)
			for (int j = pad_width; j < width + pad_width; j++)
			{
				//Construct the Values Array
				int count = 0;
				double values[25] = {0};
				for (int m = -pad_width; m <= pad_width; m++)
					for (int n = -pad_width; n <= pad_width; n++)
					{
						values[count] = temp[i+m][j+n][0];
						count++;
					}
				//Convolution
				img_feature25D[i-pad_width][j-pad_width][f] = convolute(FILTER2D[f], values, 25);
			}

	//Get Positive Values
	absoluteValues(img_feature25D, 25);

	//STEP2 : Get 15 Dimensional Features
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			//Pairwise and Normalization
			img_feature15D[i][j][0] = (img_feature25D[i][j][0]);
			img_feature15D[i][j][1] = (img_feature25D[i][j][1] + img_feature25D[i][j][5]) / 2;
			img_feature15D[i][j][2] = (img_feature25D[i][j][7] + img_feature25D[i][j][11]) / 2;
			img_feature15D[i][j][3] = (img_feature25D[i][j][6]);
			img_feature15D[i][j][4] = (img_feature25D[i][j][2] + img_feature25D[i][j][10]) / 2;
			img_feature15D[i][j][5] = (img_feature25D[i][j][8] + img_feature25D[i][j][16]) / 2;
			img_feature15D[i][j][6] = (img_feature25D[i][j][12]);
			img_feature15D[i][j][7] = (img_feature25D[i][j][3] + img_feature25D[i][j][15]) / 2;
			img_feature15D[i][j][8] = (img_feature25D[i][j][9] + img_feature25D[i][j][21]) / 2;
			img_feature15D[i][j][9] = (img_feature25D[i][j][18]);
			img_feature15D[i][j][10] = (img_feature25D[i][j][4] + img_feature25D[i][j][20]) / 2;
			img_feature15D[i][j][11] = (img_feature25D[i][j][13] + img_feature25D[i][j][17]) / 2;
			img_feature15D[i][j][12] = (img_feature25D[i][j][24]);
			img_feature15D[i][j][13] = (img_feature25D[i][j][19] + img_feature25D[i][j][23]) / 2;
			img_feature15D[i][j][14] = (img_feature25D[i][j][14] + img_feature25D[i][j][22]) / 2;
		}

	//STEP4 : Use Mean to Average the Energies
	for (int f = 0; f < 15; f++)
	{
		//Copy the Data into the Image Double
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				image3D_Double[i][j][0] = img_feature15D[i][j][f];
		//Image Extension
		int pad_width1 = imgPaddingDouble(wndsize);
		//Do the Average
		for (int i = pad_width1; i < height + pad_width1; i++)
			for (int j = pad_width1; j < width + pad_width1; j++)
			{
				//Construct the Values Array
				double sum = 0;
				for (int m = -pad_width1; m <= pad_width1; m++)
					for (int n = -pad_width1; n <= pad_width1; n++)
						sum += image3D_Extended_Double[i+m][j+n][0];
				img_feature15D[i-pad_width1][j-pad_width1][f] = sum / (wndsize * wndsize);
			}
	}

	//STEP5 : Normalization
	for (int f = 0; f < 15; f++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				img_feature15D[i][j][f] = img_feature15D[i][j][f] / img_feature15D[i][j][0];


	//STEP6 : Get 14 Dimensional Features
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < 14; k++)
				img_feature14D[i*width+j][k] = img_feature15D[i][j][k+1];

	//STEP7 : Get 3 Dimensional Features
	double** img_feature3D = allocate_2D_Double(3, height*width);
	img_feature3D = PCA(img_feature14D, height*width, 14);

	//STEP8 : K-Means Segmentation
	unsigned char* classes = allocate_1D(height, width, 1);
	if (flag3D)
		classes = Kmeans(img_feature3D, num, height * width, 3);
	else
		classes = Kmeans(img_feature14D, num, height * width, 14);

	//STEP9 : Get Results
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int temp = i * width + j;
			if (classes[temp] == 0)
				result.image3D[i][j][0] = 0;
			if (classes[temp] == 1)
				result.image3D[i][j][0] = 51;
			if (classes[temp] == 2)
				result.image3D[i][j][0] = 102;
			if (classes[temp] == 3)
				result.image3D[i][j][0] = 153;
			if (classes[temp] == 4)
				result.image3D[i][j][0] = 204;
			if (classes[temp] == 5)
				result.image3D[i][j][0] = 255;
		}
	result.writeFile();
}

//SIFT
void Image::imgSift()
{
	SIFT sift = SIFT(20, 3, 0.15, 10, 1.6);
}














