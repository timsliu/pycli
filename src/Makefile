# makefile for pycli
#

##### Variables #####

OBJS = planet.o model.o parser.o utils.o
TEST_OBJS = test/unit_test.o test/conv_test.o test/omp_test.o test/util_test.o utils.o
CXX = g++
CXXFLAGS = -std=c++11 -fopenmp -g -Wall -Werror -O3

##### Dependencies #####

all: pycli

model.o: model.h model.cc utils.cc constant.h conv.h

planet.o: planet.h planet.cc utils.cc constant.h

parser.o: parser.cc planet.h utils.cc model.h

utils.o: utils.cc utils.h

test/unit_test.o: test/unit_test.cc test/conv_test.cc test/omp_test.cc test/util_test.cc utils.cc

test/conv_test.o: test/conv_test.cc

test/util_test.o: utils.cc test/util_test.cc

test/omp_test.o: test/omp_test.cc


##### Build Rules #####

# build pycli - does not run model
pycli: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	mv *.o ../bin
	mv $@ ../bin

# build and run all unit tests
unit_test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	mv test/*.o ../bin
	mv $@ ../bin
	./../bin/unit_test

# run certain models
test_big:
	./../bin/pycli large_random -v -m serial
	./../bin/pycli large_random -v -m accel

earth:
	./../bin/pycli earth -v -m serial
	#./../bin/pycli earth -v -m accel

earth_big:
	./../bin/pycli earth_big -v -m serial
	./../bin/pycli earth_big -v -m accel

# open MP test - will be deprecated
omp: omp_test.cc
	g++ omp_test.cc -std=c++11 -fopenmp -g -o ../bin/omp_test
	./../bin/omp_test

clean:
	rm -rf *.o
	cd ../bin
	rm -f !"README.md"
	cd -

.PHONY: all clean
