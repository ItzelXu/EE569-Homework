#(1) Name : Zhiwei Deng
#(2) USC ID Number : 3669230452
#(3) USC Email : zhiweide@usc.edu
#(4) Submission Date : 02/16/2020

all:
	#Part A Source Files
	g++ -o Problem2-a Problem2-a.cpp image.cpp

	#Part B Source Files
	g++ -o Problem2-b Problem2-b.cpp image.cpp

	#Part C Source Files
	g++ -o Problem2-c-SED Problem2-c-SED.cpp image.cpp
	g++ -o Problem2-c-MBVQ Problem2-c-MBVQ.cpp image.cpp

run:
	#Part A Run
	./Problem2-a Images/LightHouse.raw F 750 500 1 128
	./Problem2-a Images/LightHouse.raw R 750 500 1 9
	./Problem2-a Images/LightHouse.raw M 750 500 1 2
	./Problem2-a Images/LightHouse.raw M 750 500 1 8
	./Problem2-a Images/LightHouse.raw M 750 500 1 32
	#Part B Run
	./Problem2-b Images/LightHouse.raw F 750 500 1 127
	./Problem2-b Images/LightHouse.raw J 750 500 1 127
	./Problem2-b Images/LightHouse.raw S 750 500 1 127
	#Part C Run
	./Problem2-c-SED Images/Rose.raw F 640 480 3 128
	./Problem2-c-SED Images/Rose.raw J 640 480 3 128
	./Problem2-c-SED Images/Rose.raw S 640 480 3 128
	./Problem2-c-MBVQ Images/Rose.raw F  640 480 3 128
	./Problem2-c-MBVQ Images/Rose.raw J  640 480 3 128
	./Problem2-c-MBVQ Images/Rose.raw S  640 480 3 128

clear:
	-rm -f Problem2-a
	-rm -f Problem2-b
	-rm -f Problem2-c-SED
	-rm -f Problem2-c-MBVQ
	-rm -f Images/LightHouse_Fixed.raw
	-rm -f Images/LightHouse_Random.raw
	-rm -f Images/LightHouse_Matrix_1.raw
	-rm -f Images/LightHouse_Matrix_3.raw
	-rm -f Images/LightHouse_Matrix_5.raw
	-rm -f Images/LightHouse_FS.raw
	-rm -f Images/LightHouse_JN.raw
	-rm -f Images/LightHouse_SK.raw
	-rm -f Images/Rose_FS.raw
	-rm -f Images/Rose_JN.raw
	-rm -f Images/Rose_SK.raw
	-rm -f Images/Rose_MBVQ_FS.raw
	-rm -f Images/Rose_MBVQ_JN.raw
	-rm -f Images/Rose_MBVQ_SK.raw