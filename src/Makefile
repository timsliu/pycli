#makefile for pycli
#

OBJS = planet.o model.o parser.o utils.o
CXX = g++
CXXFLAGS = -std=c++11 -fopenmp -g -Wall -Werror #-O3

# dependencies

all: pycli

model.o: model.h model.cc utils.cc constant.h

planet.o: planet.h planet.cc utils.cc constant.h

parser.o: parser.cc planet.h utils.cc model.h

utils.o: utils.cc utils.h

pycli: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	mv *.o ../bin
	mv $@ ../bin

test:
	./../bin/pycli small_test -v -m serial

test_big:
	./../bin/pycli large_random -v -m serial
	./../bin/pycli large_random -v -m accel

earth:
	./../bin/pycli earth -v -m serial
	./../bin/pycli earth -v -m accel

earth_big:
	./../bin/pycli earth_big -v -m serial
	./../bin/pycli earth_big -v -m accel

omp: omp_test.cc
	g++ omp_test.cc -std=c++11 -fopenmp -g -o ../bin/omp_test
	./../bin/omp_test

clean:
	rm -rf *.o ../bin/*.o ../bin/pycli ../bin/omp_test

.PHONY: all clean
