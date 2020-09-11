//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/22/2020

#include <iostream>
#include "image.h"

using namespace std;

#define TEST_SIZE 12
#define TRAIN_SIZE 9
#define SAMPLE_SIZE 36

int main()
{
	//Define the Size the Gallery Image
	int imageWidth = 128;
	int imageHeight = 128;
	int bpp = 1;

	/*================================Set Names=================================*/
	//File Names Definition
	char test_input1[50] = "Images/test/_.raw";
	char test_input2[50] = "Images/test/1_.raw";
	char rice_input[50] = "Images/train/rice_.raw";
	char grass_input[50] = "Images/train/grass_.raw";
	char brick_input[50] = "Images/train/brick_.raw";
	char blanket_input[50] = "Images/train/blanket_.raw";
	char testNames[TEST_SIZE][50];
	char riceNames[TRAIN_SIZE][50]; 
	char grassNames[TRAIN_SIZE][50]; 
	char brickNames[TRAIN_SIZE][50];
	char blanketNames[TRAIN_SIZE][50];
	//Train Name Sets
	for (int i = 0; i < TRAIN_SIZE; i++)
	{
		strcpy(riceNames[i], rice_input);
		riceNames[i][17] = '1' + i;
		strcpy(grassNames[i], grass_input);
		grassNames[i][18] = '1' + i;
		strcpy(brickNames[i], brick_input);
		brickNames[i][18] = '1' + i;
		strcpy(blanketNames[i], blanket_input);
		blanketNames[i][20] = '1' + i;
	}
	//Test Name Sets
	for (int i = 0; i < TEST_SIZE; i++)
	{
		if (i < 9)
		{
			strcpy(testNames[i], test_input1);
			testNames[i][12] = '1' + i;
		}
		else
		{
			strcpy(testNames[i], test_input2);
			testNames[i][13] = '0' + i - 9;
		}
	}
	
	/*================================Objects Construction============================*/
	//Construct the Objects
	Image testImage[TEST_SIZE];
	Image riceTrain[TRAIN_SIZE];
	Image grassTrain[TRAIN_SIZE];
	Image brickTrain[TRAIN_SIZE];
	Image blancketTrain[TRAIN_SIZE];
	//Train Objects Construction
	for (int i = 0; i < TRAIN_SIZE; i++)
	{
		riceTrain[i] = Image(imageWidth, imageHeight, bpp, riceNames[i]);
		grassTrain[i] = Image(imageWidth, imageHeight, bpp, grassNames[i]);
		brickTrain[i] = Image(imageWidth, imageHeight, bpp, brickNames[i]);
		blancketTrain[i] = Image(imageWidth, imageHeight, bpp, blanketNames[i]);
		//Initialize
		riceTrain[i].initialize();
		grassTrain[i].initialize();
		brickTrain[i].initialize();
		blancketTrain[i].initialize();
	}
	//Test Objects Construction
	for (int i = 0; i < TEST_SIZE; i++)
	{
		testImage[i] = Image(imageWidth, imageHeight, bpp, testNames[i]);;
		//Initialize
		testImage[i].initialize();
	}
	//Read Files
	for (int i = 0; i < TRAIN_SIZE; i++)
	{
		riceTrain[i].readFile();
		grassTrain[i].readFile();
		brickTrain[i].readFile();
		blancketTrain[i].readFile();
	}
	cout << "Train Sets Constructed." << endl;
	for (int i = 0; i < TEST_SIZE; i++)
		testImage[i].readFile();
	cout << "Test Sets Constructed." << endl;

 	/*================================Train Set Compute=================================*/
	//Construct the 25D Feature Matrix
	double** feature25DTrain = riceTrain[0].allocate_2D_Double(25, SAMPLE_SIZE);
	for (int i = 0; i < TRAIN_SIZE; i++)
	{
		feature25DTrain[i] = riceTrain[i].featureExtract();
		feature25DTrain[i+9] = grassTrain[i].featureExtract();
		feature25DTrain[i+18] = brickTrain[i].featureExtract();
		feature25DTrain[i+27] = blancketTrain[i].featureExtract();
	}
	//Construct the 15D Feature Matrix
	double** feature15DTrain = riceTrain[0].allocate_2D_Double(15, SAMPLE_SIZE);
	feature15DTrain = riceTrain[0].getFeatures15D(feature25DTrain, SAMPLE_SIZE, true);
	double** feature14DTrain = testImage[0].allocate_2D_Double(14, SAMPLE_SIZE);
	for (int i = 0; i < SAMPLE_SIZE; i++)
		for (int j = 0; j < 14; j++)
			feature14DTrain[i][j] = feature15DTrain[i][j+1];
	//Construct Train 3D Feature matrix
	double** feature3DTrain = riceTrain[0].allocate_2D_Double(3, SAMPLE_SIZE);
	feature3DTrain = riceTrain[0].PCA(feature14DTrain, SAMPLE_SIZE, 14);

	/*================================Test Set Compute=================================*/
	//Construct the 25D Feature Matrix
	double** feature25DTest = testImage[0].allocate_2D_Double(25, TEST_SIZE);
	for (int i = 0; i < TEST_SIZE; i++)
		feature25DTest[i] = testImage[i].featureExtract();
	//Construct the 15D Feature Matrix
	double** feature15DTest = testImage[0].allocate_2D_Double(15, TEST_SIZE);
	feature15DTest = testImage[0].getFeatures15D(feature25DTest, TEST_SIZE, true);
	double** feature14DTest = testImage[0].allocate_2D_Double(14, TEST_SIZE);
	for (int i = 0; i < TEST_SIZE; i++)
		for (int j = 0; j < 14; j++)
			feature14DTest[i][j] = feature15DTest[i][j+1];
	//Construct Test 3D Feature matrix
	double** feature3DTest = testImage[0].allocate_2D_Double(3, TEST_SIZE);
	feature3DTest = testImage[0].PCA(feature14DTest, TEST_SIZE, 14);

	/*================================PCA and K-Means================================*/
	clock_t t1 = clock();
	double** feature15DTest_NoNorm = testImage[0].allocate_2D_Double(15, TEST_SIZE);
	feature15DTest_NoNorm = testImage[0].getFeatures15D(feature25DTest, TEST_SIZE, false);
	//Do the K means
	cout << "K-Means by 15-D Features" << endl;
	riceTrain[0].Kmeans(feature15DTest_NoNorm, 4, TEST_SIZE, 15);
	cout << "K-Means by 3-D Features" << endl;
	riceTrain[0].Kmeans(feature3DTest, 4, TEST_SIZE, 3);
	//cout << (double)(clock() - t1) << endl;
	/*================================Random Forest================================*/
	//Construct the Label Array
	double* labels = riceTrain[0].allocate_1D_Double(SAMPLE_SIZE, 1, 1);
	for (int i = 0; i < TRAIN_SIZE; i++)
	{
		labels[i] = 0;
		labels[i+9] = 1;
		labels[i+18] = 2;
		labels[i+27] = 3;
	}
	cout << "Random Forest by 3D Features" << endl;
	riceTrain[0].randomForest(feature3DTrain, feature3DTest, labels, SAMPLE_SIZE, TEST_SIZE, 3);
	cout << "Support Vector Machine by 3D Features" << endl;
	riceTrain[0].SupportVectorMachine(feature3DTrain, feature3DTest, labels, SAMPLE_SIZE, TEST_SIZE, 3);
	//testImage[0].printMatrix(feature3DTest, TEST_SIZE, 3);

	return 0;
}
