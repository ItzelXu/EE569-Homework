# EE569 Homework Assignment #3
# Date: Mar 03, 2020
# Name: Zhiwei Deng
# ID: 3669230452
# email: zhiweide@usc.edu
#
# Compiled on MAC OS Mojave 10.14.6
# gcc/g++ version 4.2.1

# OtherPlatforms
# Matlab R2019a on Macbook Pro for Problem1

# Folder Arrangement

###############################################################################
	Please put the input image and Ground Truth Images into the
	'Images' folder. Please DO NOT delete 'Images' Folder.
###############################################################################

# Folder 'Problem1' 
	It Contains the Source Code and Makefile for Problem1
	'Images' Folder should be used to store the Image Files for clear organization. Every Input Image including Original Image should be put into this folder.
	Please Do Not Remove this Folder.

# Folder 'Problem2'
	It Contains the Source Code and Makefile for Problem2
	'Images' Folder should be used to store the Image Files for clear organization. Every Input Image including Original Image should be put into this folder.
	Please Do Not Remove this Folder.

# Compile

# Problem1
	For this part, the code is written in Matlab, no compile needed

# Problem2
	For compiling Problem2 source codes, you need to go into the 'Problem2' folder from your command window first.
	Then just use 'make all' command to compile all the source code into object file

# Run Code

###############################################################################
	Please Follow the Command Exactly as the Example Shows, the Name
	of the Output Images Matters to the Evaluation Process. 
	Please Don't Change them.
##############################################################################

# For Problem 1 a, run below command in your Matlab command window within 'Problem1' folder
	the command is 'run_warp'
	#Note: The wraping and reverse process are all going to be done in this Program

# For Problem 1 b, run below command in your Matlab command window within 'Problem1' folder
	the command is 'run_stitch'
	#Note: You can comment or uncomment certain lines to get different results, like different methods of interpolation and control points

###############################################################################
	For Problem2, there is a Makefile in the folder 'Problem2', for easily 
	run all the commands below at same time. Just run below command in your 
	command window within 'Problem2' folder. Use 'make run' to run them.
###############################################################################

# For Problem 2 a, run below command in your command window within 'Problem2' folder
	the command is './Problem2a'
	#Note: the 3 images are processed in the same time in one Program.

# For Problem 2 b, run below command in your command window within 'Problem2' folder
	the command is './Problem2b'
	#Note: The two methods of counting are all implemented in one program, you can comment the certain line if you only want to use one of them

# For Problem 2 c, run below command in your command window within 'Problem2' folder
	the command is './Problem2c'

# For Problem 2 d, run below command in your command window within 'Problem2' folder
	the command is './Problem2d'

# For show the histograms, Just open the folder in your Matlab Command window and run 'show' command after running the code.

# Results
	For Problem 1, The result images will be created in the 'Problem1' folder. 
	For Problem 2, The result images will be created in the 'Images' folder. 
	Every program has its own output filename.
	
	The count of the stars and the PCB ogjects are going to be displayed on your command window screen.

# Code Review
	The code's only hard coded part is the Reading image part. Please do not remove any folders.
	If there is any issues about the compiling and variables, please feel free to contact me.
