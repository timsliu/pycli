/*  Header file for convolution unit tests
 *
 */

#include "./../conv.h"

std::vector<std::vector<float>> make_grid(int size, float val);

float kernelSum(std::vector<float> kernel);

int convUniform();

int linearKernel();
