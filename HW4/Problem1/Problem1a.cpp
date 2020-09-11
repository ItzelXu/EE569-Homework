//(1) Name : Zhiwei Deng
//(2) USC ID Number : 3669230452
//(3) USC Email : zhiweide@usc.edu
//(4) Submission Date : 03/22/2020

#include <iostream>
#include "image.h"

using namespace std;

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
	char rice_input[50] = "Images/train/rice_.raw";
	char grass_input[50] = "Images/train/grass_.raw";
	char brick_input[50] = "Images/train/brick_.raw";
	char blanket_input[50] = "Images/train/blanket_.raw";
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
	/*================================Objects Construction============================*/
	//Construct the Objects
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
	//Read Files
	for (int i = 0; i < TRAIN_SIZE; i++)
	{
		riceTrain[i].readFile();
		grassTrain[i].readFile();
		brickTrain[i].readFile();
		blancketTrain[i].readFile();
	}
	cout << "Train Sets Constructed." << endl;

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
	feature15DTrain = riceTrain[0].getFeatures15D(feature25DTrain, SAMPLE_SIZE, false);

	/*================================Standard Deviation==============================*/
	//Construct Standard Deviation
	double* standDevTrain = riceTrain[0].allocate_1D_Double(15, 1, 1);
	standDevTrain = riceTrain[0].calcSTD(feature15DTrain, SAMPLE_SIZE);
	cout << "Standard Deviation" << endl;
	for (int i = 0; i < 15; i++)
		cout << standDevTrain[i] << "  ";
	cout << endl;

	/*======================================PCA======================================*/
	//Construct Train matrix
	double** feature3DTrain = riceTrain[0].allocate_2D_Double(3, SAMPLE_SIZE);
	feature3DTrain = riceTrain[0].PCA(feature15DTrain, SAMPLE_SIZE, 15);
	cout << "PCA 3D Feature Matrix" << endl;
	riceTrain[0].printMatrix(feature3DTrain, SAMPLE_SIZE, 3);

	return 0;
}