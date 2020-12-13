/* Utility functions
 *
 */

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

#include "utils.h"

using namespace std;

void printTemperature(vector<vector<double>>& temp) {
    size_t latCells = temp.size();
    size_t longCells = temp[0].size();

    for (size_t i = 0; i < latCells; i++) {
        for (size_t j = 0; j < longCells; j++) {
            cout << " " << setprecision(3) << 1.8 * (temp[i][j] - 273) + 32 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printSurface(vector<vector<SurfaceType>>& inputSurface) {
    int latCells = inputSurface.size(); 
    int longCells = inputSurface[0].size(); 
    
    for (int i = 0; i < latCells; i++ ) {
        for (int j = 0; j < longCells; j++ ) {
            cout << inputSurface[i][j];
        }
        cout << endl;
    }
}

void printAtmosphere(map<string, double>& atmo) {
    
    for (auto it = atmo.begin(); it != atmo.end(); it++) {
        cout << it->first << " => " << it->second << " "; 
    }
    cout << endl;

}

void printAtmosList(vector<map<string, double>>& atmoList) {
    for (auto a: atmoList) {
        printAtmosphere(a);
    }

}

/* Performs an in place 2D convolution treating the input matrix as a cylinder:
 * the x-dimension wraps but the y-dimensions does not. The top and bottom edges
 * are handled by repeating the edge values. The convolution kernel MUST be
 * separable and is passed as the vector kernel
 */


template <class T>
void serialConvolve(vector<vector<T>>& inputMatrix, vector<T>& kernel) {

    size_t kernelSize = kernel.size();
    size_t kernelMid = (kernelSize - 1) /2;

    if (kernelSize % 2 != 0) {
        cout << "serialConvolve error: kernel must have odd no. of elements" << endl;
        return;
    }

    size_t xDim = inputMatrix[0].size();
    size_t yDim = inputMatrix.size();

    // create vector to hold intermediate matrix (result of row conv)
    vector<vector<T>> interMatrix;

    for (size_t i = 0; i < yDim; i++) {
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

// creates a gaussian, separable filter given the size of the
// matrix to convolve and the size of the filter as a fraction of
// the xDimension

template <class T>
vector<T> makeKernel(int xDim, int yDim, float width) {

    int kernelWidth = xDim * width;
    vector<T> kernel(kernelWidth);

}
