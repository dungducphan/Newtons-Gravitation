LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -fopenmp -lm -DINFO=1

clean:
	- rm -rf gravitation

utils.o: utils.cpp
	- $(CXX) -c utils.cpp -o utils.o

gravitation: utils.o
	- $(CXX) gravitation.cpp utils.o $(CXXFLAGS) $(LIBS) -o gravitation

all: clean gravitation