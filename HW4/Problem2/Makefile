all:
	#Compile Source Files
	g++ `pkg-config --cflags --libs opencv` -o Problem2b Problem2b.cpp image.cpp
	g++ `pkg-config --cflags --libs opencv` -o Problem2c Problem2c.cpp image.cpp
run:
	#Run Programs
	./Problem2b
	./Problem2c

clear:
	-rm -f Problem2b
	-rm -f Problem2c
