/*
 * Functions for testing convolution.h functions
 */

#include "conv_test.h"
#include "test.h"


using namespace std;

/***** Helper functions *****/

/* create a SMALL_GRID x SMALL_GRID  2D vector with the same value */
vector<vector<float>> make_grid(int size, float val) {
    vector<vector<float>> input(size, vector<float>(size, val));
    return input;
}

/* compute the sum of a separable kernel. Compute the dot product of a 
 * vector representing a kernel with its transpose
 * 
 */
float kernelSum(vector<float> kernel) {

    float sum = 0.0;

    for (size_t i = 0; i < kernel.size(); i++) {
        for (size_t j = 0; j < kernel.size(); j++) {
            sum += kernel[i] * kernel[j];
        }
    }
    return sum;
}


/***** Unit test functions *****/

/* convolve a uniform grid - every element should be the same in the result */
int convUniform() {

    vector<vector<float>> input = make_grid(SMALL_GRID, 1.0);
    vector<float> kernel (1.0, 3);
    serialConvolve<float>(input, kernel);

    int rows = input.size();
    int cols = input[0].size();
    int errors = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++ ) {
            if (input[i][j] != 9.0) {
                if (errors < 10) {
                    cout << "Error! At " << i << ", " << j;
                    cout << " got: " << input[i][j] << " expected: 9.0" << endl;
                }
                errors++;
            }
        }
    }

    /* return 1 if more than 0 errors, otherwise return 0 */
    return errors > 0 ? 1 : 0;
}

/*
 * call makeLinearKernel with different arguments and check the kernel's size and
 * that the values add to one
 */

int linearKernel() {

    int error = 0;

    vector<float> kernel1 = makeLinearKernel<float>(100, 100, 0.1);
    float kernel1Sum = kernelSum(kernel1);

    if (kernel1.size() != 11) {
        cout << "Error! Expected kernel size 11 got kernel size: " << kernel1.size() << endl;
        error = 1;
    }

    if (abs(kernel1Sum - 1.0) > 0.001) {
        cout << "Error! Kernel sum is: " << kernel1Sum << endl; 
        error = 1;
    }
    
    vector<float> kernel2 = makeLinearKernel<float>(10, 10, 0.25);
    float kernel2Sum = kernelSum(kernel2);

    if (kernel2.size() != 3) {
        cout << "Error! Expected kernel size 3 got kernel size: " << kernel2.size() << endl;
        error = 1;
    }

    if (abs(kernel2Sum - 1.0) > 0.001) {
        cout << "Error! Kernel sum is: " << kernel2Sum << endl; 
        error = 1;
    }

    return error;
}


