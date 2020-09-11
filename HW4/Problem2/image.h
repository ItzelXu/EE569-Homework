//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/22/2020

#include <opencv2/opencv.hpp>
using namespace cv;

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
		//The Image 3D array Double
		double*** image3D_Double;
		//The Boundary-Extended Image 3D array
		unsigned char*** image3D_Extended;
		//The Boundary-Extended Image 3D array - Double
		double*** image3D_Extended_Double;
		//Constructor1
		Image();
		//Constructor2
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
		//Allocate 1D array Double
		double* allocate_1D_Double(int width, int height, int bpp);
		//Allocate 2D array
		unsigned char** allocate_2D(int width, int height);
		//Allocate 2D array Double
		double** allocate_2D_Double(int width, int height);
		//Allocate 3D array
		unsigned char*** allocate_3D(int width, int height, int bpp);
		//Allocate 3D Double array
		double*** allocate_3D_Double(int width, int height, int bpp);
		//Get 3D Image from 1D Image
		void getImage3D();
		//Get 1D Image from 3D Image
		void getImage1D();
		//Extend the Image Boundary by Reflection
		int imgPadding(int N);
		//Extend the Image Boundary by Reflection - Double
		int imgPaddingDouble(int N);
		//Extend the Image Boundary by Zeros
		int zeroPadding(int N);
		//Compare Images
		bool compareImage(Image other);
		//===============================Homework4==================================//
		//Show the Matrix to Check
		void printMatrix(double** matrix, int len1, int len2);
		//Shrink the Features into 15D
		double** getFeatures15D(double **features, int size);
		//Feature Extraction
		double* featureExtract();
		//Subtract the Global Mean of the Image
		void meanSubtract();
		//Get Absolute Values
		void absoluteValues(double*** image3D_Double, int layers);
		//Calculate Standard Deviation
		double* calcSTD(double **features, int size);
		//PCA Function
		double** PCA(double** matrix, int size, int dimension);
		//K-means
		unsigned char* Kmeans(double **features3D, int num, int size, int dimension);
		//K-means Center
		double** KmeansCenter(double **features, int num, int size, int dimension);
		//Random Forest
		void randomForest(double **trainSet, double **testSet, double *label, int sample_size, int test_size, int dimension);
		//Support Vector Machine
		void SupportVectorMachine(double **trainSet, double **testSet, double *label, int sample_size, int test_size, int dimension);
		//Image Segmentation Function
		void imgSegment(Image result, int wndsize, int num, bool flag3D);
		//SIFT Function
		double** imgSift(Image another, int KeyNum, int num, bool showflag, int flag);
		//Find Largest Keypoints
		int LargestKeypoint(Mat discriptor1, int KeyPtsNum);
		//Find Nearest Keypoints
		int NearestKeyPoint(Mat discriptor1, Mat discriptor2, int largest_index, int KeyPtsNum);
		//Sort the Centroids
		double** sortCentroids(double** centroid, double** target, int num, int dimension);
		//Compute the Histogram Intersection
		int histIntersect(int histo1[], int histo2[], int num);
};






























