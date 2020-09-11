# EE569 Homework Assignment #2
# Date: Feb 16, 2020
# Name: Zhiwei Deng
# ID: 3669230452
# email: zhiweide@usc.edu
#
# Compiled on MAC OS Mojave 10.14.6
# gcc/g++ version 4.2.1

# OtherPlatforms
# Matlab R2019a on Windows for Problem1 (b)(c)(d)

# Folder Arrangement

###############################################################################
	Please put the input image and Ground Truth Images into the
	'Images' folder. Please DO NOT delete 'Images' Folder.
###############################################################################

# Folder 'Problem1' 
	It Contains the Source Code and Makefile for Problem1
	'Images' Folder should be used to store the Image Files for clear organization. Every result Image including Original Image should be put into this folder.
	Please Do Not Remove this Folder.

	#IMPORTANT#
	Please place the SE Toolbox and Pdollar Toolbox in the 'Problem1' folder. Name them as 'edges-master' and 'toolbox-master' respectively.

# Folder 'Problem2'
	It Contains the Source Code and Makefile for Problem2
	'Images' Folder should be used to store the Image Files for clear organization. Every result Image including Original Image should be put into this folder.
	Please Do Not Remove this Folder.

# Compile

# Problem1 a
	For compiling Problem1-a source codes, you need to go into the 'Problem1' folder from your command window first.
	Then just use 'make all' command to compile all the source code into object file

# Problem1 b-d
	These parts of function are written in Matlab. Does not need compile

# Problem2
	For compiling Problem2 source codes, you need to go into the 'Problem2' folder from your command window first.
	Then just use 'make all' command to compile all the source code into object file

# Run Code

###############################################################################
	Please Follow the Command Exactly as the Example Shows, the Name
	of the Output Images Matters to the Evaluation Process. 
	Please Don't Change them.
##############################################################################

# For Problem1-a, there is a Makefile in the folder 'Problem1', for easily run the command below,
# Just run below command in your command window within 'Problem1' folder
# 'make run'

###############################################################################
	Please Follow the Example Command to run the Program.
	For Canny Detector, The Output File name Should be
	'Dogs_CA_Map.raw', 'Gallery_CA_Map.raw' - Canny Detector

	For SE Detector, The Map File name Should be
	'Dogs_SE_Map.raw', 'Gallery_SE_Map.raw' - SE Detector

	For Evaluation Process, The Input Images name should be
	'Dogs_SB_Map.raw', 'Gallery_SB_Map.raw' - Sobel Detector
	'Dogs_CA_Map.raw', 'Gallery_CA_Map.raw' - Canny Detector
	'Dogs_SE_Map.raw', 'Gallery_SE_Map.raw' - SE Detector
###############################################################################

# For Problem 1 a, run below command in your command window within 'Problem1' folder
	the command is './Problem1-a <Threshold for Gallery> <Threshold for Dogs>'
	EXAMPLE: './Problem1-a 0.07 0.10'
	#Note: If you want to see the results of gray image and Gradients Images, you can uncomment the Write file Lines.

# For Problem 1 b, run below command in your Matlab command window within 'Problem1' folder
	the command is 'run_canny(<Input File Path>, <Output File Path>, <Image Height>, <Image Width>, <Lower Thresh>, <Upper Thresh>)'
	EXAMPLE1: 'run_canny('Images/Gallery.jpg', 'Images/Gallery_CA_Map.raw', 321, 481, 0.13, 0.20)'
	EXAMPLE2: 'run_canny('Images/Dogs.jpg', 'Images/Dogs_CA_Map.raw', 321, 481, 0.23, 0.35)'

# For Problem 1 c, run below command in your Matlab command window within 'Problem1' folder
	the command is 'run_structured(<Input File Path>, <Output File Path>, <Map file Path>, <Image Height>, <Image Width>, <Threshold>)'
	EXAMPLE1: 'run_structured('Images/Gallery.jpg', 'Images/Gallery_SE.raw', 'Images/Gallery_SE_Map.raw', 321, 481, 220)'
	EXAMPLE2: 'run_structured('Images/Dogs.jpg', 'Images/Dogs_SE.raw', 'Images/Dogs_SE_Map.raw', 321, 481, 220)'

# For Problem 1 d, run below command in your Matlab command window within 'Problem1' folder
	the command is 'run_evaluate(<File Type>, <Edge Type>, <Number of Thresholds>)'
	#-------------------Evaluate Sobel Maps------------------#
	EXAMPLE1: 'run_evaluate('gallery', 'SB', 99)'
	EXAMPLE2: 'run_evaluate('dogs', 'SB', 99)'
	#-------------------Evaluate Canny Results------------------#
	EXAMPLE3: 'run_evaluate('gallery', 'CA', 1)'
	EXAMPLE4: 'run_evaluate('dogs', 'CA', 1)'
	#-------------------Evaluate SE Maps------------------#
	EXAMPLE1: 'run_evaluate('gallery', 'SE', 99)'
	EXAMPLE2: 'run_evaluate('dogs', 'SE', 99)'

# For Problem2, there is a Makefile in the folder 'Problem2', for easily run all the commands below at same time,
# Just run below command in your command window within 'Problem2' folder
# 'make run'

# For Problem 2 a, run below command in your command window within 'Problem2' folder
	the command is './Problem2-a <Input Image Path> <Method Type> <Image Width> <Image Height> <BytePerPixle> <Threshold/Random Seed/Matrix Width>'
	#-------------------Fixed Thresholding---------------------------#
	EXAMPLE1: './Problem2-a Images/LightHouse.raw F 750 500 1 128'

	#-------------------Random Thresholding--------------------------#
	EXAMPLE2: './Problem2-a Images/LightHouse.raw R 750 500 1 9'

	#-------------------Dithering Matrix-----------------------------#
	EXAMPLE3: './Problem2-a Images/LightHouse.raw M 750 500 1 2'
	EXAMPLE4: './Problem2-a Images/LightHouse.raw M 750 500 1 8'
	EXAMPLE5: './Problem2-a Images/LightHouse.raw M 750 500 1 32'

# For Problem 2 b, run below command in your command window within 'Problem2' folder
	the command is './Problem2-b <Input Image Path> <Filter Type> <Image Width> <Image Height> <BytePerPixle> <Threshold>'
	#-------------------Floyd Steinberg---------------------------#
	EXAMPLE1: './Problem2-b Images/LightHouse.raw F 750 500 1 127'

	#-------------------JJN Filter--------------------------------#
	EXAMPLE2: './Problem2-b Images/LightHouse.raw J 750 500 1 127'

	#-------------------Stucki-----------------------------------#
	EXAMPLE3: './Problem2-b Images/LightHouse.raw S 750 500 1 127'

# For Problem 2 c - Separable Diffusion, run below command in your command window within 'Problem2' folder
	the command is './Problem2-c-SED <Input Image Path> <Filter Type> <Image Width> <Image Height> <BytePerPixle> <Threshold>'
	#-------------------Floyd Steinberg---------------------------#
	EXAMPLE1: './Problem2-c-SED Images/Rose.raw F 640 480 3 128'

	#-------------------JJN Filter--------------------------------#
	EXAMPLE2: './Problem2-c-SED Images/Rose.raw J 640 480 3 128'

	#-------------------Stucki-----------------------------------#
	EXAMPLE3: './Problem2-c-SED Images/Rose.raw S 640 480 3 128'

# For Problem 2 c - MBVQ, run below command in your command window within 'Problem2' folder
	the command is './Problem2-c-MBVQ <Input Image Path> <Filter Type> <Image Width> <Image Height> <BytePerPixle> <Threshold>'
	#-------------------Floyd Steinberg---------------------------#
	EXAMPLE1: './Problem2-c-MBVQ Images/Rose.raw F 640 480 3 128'

	#-------------------JJN Filter--------------------------------#
	EXAMPLE2: './Problem2-c-MBVQ Images/Rose.raw J 640 480 3 128'

	#-------------------Stucki-----------------------------------#
	EXAMPLE3: './Problem2-c-MBVQ Images/Rose.raw S 640 480 3 128'

# Results
	The result images will be created in the 'Images' folder. 
	Every program has its own output filename.
	Problem 1 a - 'Dogs_Edges.raw' and 'Gallery_Edges.raw'
	Problem 1 b - 'Dogs_CA_Map.raw' and 'Gallery_CA_Map.raw'
	Problem 1 c - 'Dogs_SE.raw' and 'Gallery_SE.raw'
	Problem 1 d - Output will show in the Command Window
	Problem 2 a - 'LightHouse_Fixed.raw' and 'LightHouse_Random.raw' and 'LightHouse_Matrix_N.raw' where N is log2(window size)
	Problem 2 b - 'LightHouse_FS.raw' and 'LightHouse_JN.raw' and 'LightHouse_SK.raw'
	Problem 2 c - Separable - 'Rose_FS.raw' and 'Rose_JN.raw' and 'Rose_SK.raw'
	Problem 2 c - MBVQ - 'Rose_MBVQ_FS.raw' and 'Rose_MBVQ_JN.raw' and 'Rose_MBVQ_SK.raw'
	
	F-Score, mean Precision and mean Recall will be displayed on your Matlab command window.

# Notes about Input
	Every window size should be odd, if it is even program will exit error.

# Code Review
	The code's only hard coded part is the Reading image part. Please do not remove any folders.
	If there is any issues about the compiling and variables, please feel free to contact me.
