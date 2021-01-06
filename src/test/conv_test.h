/*  Header file for convolution unit tests
 *
 */

#ifndef CONV_TEST_H
#define CONV_TEST_H


#define SMALL_GRID 8
#define LARGE_GRID 16

#include "./../conv.h"

std::vector<std::vector<float>> make_grid(int size, float val);

float kernelSum(std::vector<float> kernel);

int convUniform();

int linearKernel();

int convVerticalEdge();

#endif /* CONV_TEST_H */
