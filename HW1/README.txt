# EE569 Homework Assignment #1
# Date: Jan 28, 2020
# Name: Zhiwei Deng
# ID: 3669230452
# email: zhiweide@usc.edu
#
# Compiled on MAC OS Mojave 10.14.6
# gcc/g++ version 4.2.1

# OtherPlatforms
# Matlab R2019a only for BM3D Problem

# Folder Arrangement

###############################################################################
	Please put the input image and original and noise-free Image into the
	'Images' folder. Please DO NOT delete 'Images' and 'Data' Folder.
###############################################################################

# Folder 'Problem1' 
	It Contains the Source Code and Makefile for Problem1
	'Data' Folder should be used to store the Histogram files. Please Do Not Remove this Folder.
	'Images' Folder should be used to store the Image Files for clear organization. Every Image including Original Image should be put into this folder.
	Please Do Not Remove this Folder.

# Folder 'Problem2'
	It Contains the Source Code and Makefile for Problem2 a-c
	'Images' Folder should be used to store the Image Files for clear organization. Every Image including Original Image should be put into this folder.
	Please Do Not Remove this Folder.

# Folder 'BM3D'
	It Contains the Source Code for Problem2 d
	'Images' Folder should be used to store the Image Files for clear organization. Every Image including Original Image should be put into this folder.
	Please Do Not Remove this Folder.
	'Lib' Folder contains the tools and functions the algorithm needed. Please Do Not Remove this Folder.

# Compile

#Problem1
	For compiling Problem1 source codes, you need to go into the 'Problem1' folder from your command window first.
	Then just use 'make all' command to compile all the source code into '.exe' file
#Problem2 a-c
	For compiling Problem2 a-c source codes, you need to go into the 'Problem2' folder from your command window first.
	Then just use 'make all' command to compile all the source code into '.exe' file
#Problem2 d
	Problem2 d source codes doesn't need compile.

# Run Code

# For Problem 1 a, run below command in your command window within 'Problem1' folder
	the command is './Problem1-a.exe <Input Image Path> <Width> <Height> <BytePerPixel>'
	EXAMPLE: './Problem1-a.exe Images/Dog.raw 600 532 1'

# For Problem 1 b, run below command in your command window within 'Problem1' Folder
	the command is './Problem1-b.exe <Input Image Path> <Width> <Height> <BytePerPixel>'
	EXAMPLE: './Problem1-b.exe Images/Dog.raw 600 532 1'

# For Problem 1 c - Method A, run below command in your command window within 'Problem1' Folder
	the command is './Problem1-cA.exe <Input Image Path> <Width> <Height> <BytePerPixel>'
	EXAMPLE: './Problem1-cA.exe Images/Toy.raw 400 560 3'

# For Problem 1 c - Method B, run below command in your command window within 'Problem1' folder
	the command is './Problem1-cB.exe <Input Image Path> <Width> <Height> <BytePerPixel>'
	EXAMPLE: './Problem1-cB.exe Images/Toy.raw 400 560 3'

# For Problem 1 statistics,
#just go into the 'Problem1' folder in Matlab and Run 'show' command.
# The histograms and statistics graph will pop out.

# For Problem 2 a - Uniform Filter, run below command in your command window within 'Problem2' folder
	the command is './Problem2-a-U.exe <Input Image Path> <Width> <Height> <BytePerPixel> <Window Size>'
	EXAMPLE: './Problem2-a-U.exe Images/Corn_noisy.raw 320 320 1 5'

# For Problem 2 a - Gaussian Filter, run below command in your command window within 'Problem2' folder
	the command is './Problem2-a-G.exe <Input Image Path> <Width> <Height> <BytePerPixel> <Window Size> <Sigma>'
	EXAMPLE: './Problem2-a-G.exe Images/Corn_noisy.raw 320 320 1 5 1.0'

# For Problem 2 b, run below command in your command window within 'Problem2' folder
	the command is './Problem2-b.exe <Input Image Path> <Width> <Height> <BytePerPixel> <Window Size> <Sigmac> <Sigmas>'
	EXAMPLE: './Problem2-b.exe Images/Corn_noisy.raw 320 320 1 5 1.0 70'

# For Problem 2 c, run below command in your command window within 'Problem2' folder
	the command is './Problem2-c.exe <Input Image Path> <Width> <Height> <BytePerPixel> <Compare Window Size> <Search Window Size> <h> <sigma>'
	EXAMPLE: './Problem2-b.exe Images/Corn_noisy.raw 320 320 1 5 7 30 1.0'

# For Problem 2 d,
# just go into the 'BM3D' folder in Matlab and Run below command.
# the command is 'run_BM3D('Input Image Path', Height, Width, sigma)'
	EXAMPLE: 'run_BM3D('Images/Corn_noisy.raw', 320, 320, 0.09)'

###############################################################################
	Please put the input image and original Image into the 'Images' folder,
	because every code is going to calculate PSNR automatically which will 
	reference the original image from that folder. The FileName of noise
	free image and original image is hard-coded.
	I do recommend that following the example command is safe and change 
	its variables.
###############################################################################

# Results
	The result images will be created in the 'Images' folder. 
	Every program has its own output filename.
	Problem 1 a - 'Dog_demosaic.raw'
	Problem 1 b - 'Dog_demosaicMHC.raw'
	Problem 1 cA - 'Toy_equalizedA.raw'
	Problem 1 cB - 'Toy_equalizedB.raw'
	Problem 2 a Uniform - 'Corn_LFU.raw'
	Problem 2 a Gaussian - 'Corn_LFG.raw'
	Problem 2 b - 'Corn_BIF.raw'
	Problem 2 c - 'Corn_NLM.raw'
	Problem 2 d - 'Corn_BM3D.raw'
	
	PSNR will be displayed on your standard out put, i.e. your command window.

# Notes about Input
	Every window size should be odd, if it is even program will exit error.
	Heights and Widths should be same with the original image or program dump in PSNR function.

# Code Review
	The code's only hard coded part is the Original image part. Please do not remove the folders.
	If there is any issues about the compiling and variables, please feel free to contact me.
