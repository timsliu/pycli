/*
 * functions for generic convolution
 *
 */

#ifndef CONV_H
#define CONV_H

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

/*
 * ========= Function prototypes ============
 */


/* Performs an in place 2D convolution treating the input matrix as a cylinder:
 * the x-dimension wraps but the y-dimensions does not. The top and bottom edges
 * are handled by repeating the edge values. The convolution kernel MUST be
 * separable and is passed as the vector kernel
 */

template <typename T>
void serialConvolve(vector<vector<T>>& inputMatrix, vector<T>& kernel);


/* creates a gaussian, separable filter given the size of the
 * matrix to convolve and the size of the filter as a fraction of
 * the xDimension
 */

template <typename T>
vector<T> makeGaussianKernel(int xDim, int yDim, float width);

/* creates a linear, separable filter given the size of the
 * matrix to convolve and the size of the filter as a fraction of
 * the xDimension. Filter size is rounded to the nearest odd number.
 * For example, if xDim = 100 and width = 0.1 then the
 * filter will be 11 units large
 */

template <typename T>
vector<T> makeLinearKernel(int xDim, int yDim, T width);

/*
 * ============ Function implementations ==============
 */

template <typename T>
void serialConvolve(vector<vector<T>>& inputMatrix, vector<T>& kernel) {
    
    int kernelSize = kernel.size();       /* size of the kernel */
    int kernelMid = (kernelSize - 1) /2;  /* elements on either side of kernel center */

    if (kernelSize % 2 != 1) {
        cout << "kernel size: " << kernelSize << endl;
        cout << "serialConvolve error: kernel must have odd no. of elements" << endl;
        return;
    }

    int xDim = inputMatrix[0].size();
    int yDim = inputMatrix.size();

    // create vector to hold intermediate matrix (result of row conv)
    vector<vector<T>> interMatrix;

    for (int i = 0; i < yDim; i++) {
        vector<T> xRow(xDim);
        interMatrix.push_back(xRow);
    }


    // perform row convolution
    for (int i = 0; i < yDim; i++) {
        for (int j = 0; j < xDim; j++) {
            T sum = 0;
            for (int k = 0; k < kernelSize; k++) {
                int offset = k - kernelMid;                 /* offset of element to multiply */
                int neighbor = (j + offset + xDim) % xDim;  /* wrap to get index of neighbor */
                sum += kernel[k] * inputMatrix[i][neighbor]; 
            }
            interMatrix[i][j] = sum;
        }
    }

    // perform col convolution
    for (int j = 0; j < xDim; j++) {
        for (int i = 0; i < yDim; i++) {
            T sum = 0;
            for (int k = 0; k < kernelSize; k++) {
                int offset = k - kernelMid;
                int neighborRow = i + offset;
                int neighborCol = j;

                /* reflect off edges and use x value on opposite side of cylinder */
                /* represents going over the poles */
                if (neighborRow < 0) {
                    neighborRow = neighborRow * -1 - 1;
                    neighborCol = (neighborCol + xDim/2) % xDim;
                }
                if (neighborRow > yDim - 1) {
                    neighborRow = yDim - (neighborRow - yDim + 1);
                    neighborCol = (neighborCol + xDim/2) % xDim;
                }

                sum += kernel[k] * interMatrix[neighborRow][neighborCol]; 
            }
            inputMatrix[i][j] = sum;
        }
    }
}


template <typename T>
vector<T> makeGaussianKernel(int xDim, int yDim, float width) {

    int kernelWidth = xDim * width;
    vector<T> kernel(kernelWidth);
    return kernel;
}

template <typename T>
vector<T> makeLinearKernel(int xDim, int yDim, T width) {

    T kernelWidth = round((xDim * width - 1)/2) * 2 + 1;
    vector<T> kernel(kernelWidth, sqrt(1/(kernelWidth * kernelWidth)));
    return kernel;
}

#endif /* CONV_H */
