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
 * the xDimension
 */

template <typename T>
vector<T> makeLinearKernel(int xDim, int yDim, float width);

/*
 * ============ Function implementations ==============
 */

template <typename T>
void serialConvolve(vector<vector<T>>& inputMatrix, vector<T>& kernel) {
    
    int kernelSize = kernel.size();
    int kernelMid = (kernelSize - 1) /2;

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
                int offset = k - kernelMid;
                int neighbor = (j + offset) % xDim;
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
                int neighbor = i + offset;

                // clamp at the edges
                if (neighbor < 0) {
                    neighbor = 0;
                }
                if (neighbor > yDim - 1) {
                    neighbor = yDim - 1;
                }

                sum += kernel[k] * interMatrix[neighbor][j]; 
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
vector<T> makeLinearKernel(int xDim, int yDim, float width) {

    float kernelWidth = round((xDim * width - 1)/2) * 2 + 1;
    vector<T> kernel(kernelWidth, sqrt(1/(kernelWidth * kernelWidth)));
    return kernel;
}

#endif /* CONV_H */
