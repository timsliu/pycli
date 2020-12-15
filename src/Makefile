# makefile for pycli
#

# add new object files here 
OBJS = planet.o model.o parser.o utils.o
TEST_OBJS = test/conv_test.o 
CXX = g++
CXXFLAGS = -std=c++11 -fopenmp -g -Wall -Werror #-O3

# dependencies

all: pycli

model.o: model.h model.cc utils.cc constant.h conv.h

planet.o: planet.h planet.cc utils.cc constant.h

parser.o: parser.cc planet.h utils.cc model.h

utils.o: utils.cc utils.h

test/conv_test.o: test/conv_test.cc

# build rules
pycli: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	mv *.o ../bin
	mv $@ ../bin

conv_test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test_big:
	./../bin/pycli large_random -v -m serial
	./../bin/pycli large_random -v -m accel

earth:
	./../bin/pycli earth -v -m serial
	#./../bin/pycli earth -v -m accel

earth_big:
	./../bin/pycli earth_big -v -m serial
	./../bin/pycli earth_big -v -m accel

omp: omp_test.cc
	g++ omp_test.cc -std=c++11 -fopenmp -g -o ../bin/omp_test
	./../bin/omp_test

clean:
	rm -rf *.o ../bin/*.o ../bin/pycli ../bin/omp_test

.PHONY: all clean
