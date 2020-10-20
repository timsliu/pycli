#makefile for pycli
#

OBJS = planet.o model.o parser.o
CXX = g++
CXXFLAGS = -std=c++11 -fopenmp -g -Wall -Werror -O3

# dependencies

all: pycli

model.o: model.h model.cc

planet.o: planet.h planet.cc

parser.o: parser.cc planet.h model.h

pycli: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	mv *.o ../bin
	mv $@ ../bin

omp: omp_test.cc
	g++ omp_test.cc -std=c++11 -fopenmp -g -o ../bin/omp_test
	./../bin/omp_test

clean:
	rm -rf *.o ../bin/*.o ../bin/pycli ../bin/omp_test

.PHONY: all clean
