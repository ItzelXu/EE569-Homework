#(1) Name : Zhiwei Deng
#(2) USC ID Number : 3669230452
#(3) USC Email : zhiweide@usc.edu
#(4) Submission Date : 03/22/2020
all:
	#Compile Source Files
	g++ `pkg-config --cflags --libs opencv` -o Problem1a Problem1a.cpp image.cpp
	g++ `pkg-config --cflags --libs opencv` -o Problem1b Problem1b.cpp image.cpp
	g++ `pkg-config --cflags --libs opencv` -o Problem1c Problem1c.cpp image.cpp
run:
	#Run Programs
	./Problem1a
	./Problem1b
	./Problem1c

clear:
	-rm -f Problem1a
	-rm -f Problem1b
	-rm -f Problem1c