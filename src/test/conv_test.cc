/*
 * Functions for testing convolution.h functions
 */

#include <iomanip>
#include <algorithm>

#include "conv_test.h"
#include "test.h"


using namespace std;

/***** Helper functions *****/

/* create a SMALL_GRID x SMALL_GRID  2D vector with the same value */
vector<vector<float>> makeGrid(int size, float val) {
    vector<vector<float>> input(size, vector<float>(size, val));
    return input;
}

/* compute the sum of a separable kernel
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

/*
 * print out a 2D grid
 */

void printGrid(vector<vector<float>> grid) {
   int xDim = grid[0].size();
   int yDim = grid.size();

    for (int i = 0; i < yDim; i++) {
        for (int j = 0; j < xDim; j++) {
            cout << setprecision(3) << grid[i][j] << " ";
        }
        cout << endl;
    }

}

/*
 * Check if a grid has the expected values. Assumes that the values are either zero
 * or a specified nonzero value. Grid must be a square 
 *
 * inputs: testGrid - 2D grid being tested
 *         nonZero - vector of points on grid that are nonzero in row*rowSize + col form
 *         value - expected nonzero value
 */

int checkGrid(vector<vector<float>>& testGrid, vector<int> nonZero, float value) {

    int error = 0;                      /* total number of incorrect values */
    int gridSize = testGrid.size();     /* size of the grid - must be square */
   
    /* iterate through grid */
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            /* check if point is in expected nonzero list */
            auto it = find(nonZero.begin(), nonZero.end(), gridSize * i + j);
            if (it != nonZero.end()) {
                /* check if correct value */
                if (!close(testGrid[i][j], value)) {
                    cout << "convVerticalEdge error! ";
                    cout << "Expected " << value << " at position: " << i << " " << j;
                    cout << " Got: " << testGrid[i][j] << endl;
                    error += 1;
                }
            }

            else {
                /* value should be 0 */
                if (testGrid[i][j] != 0) {
                    cout << "convVerticalEdge error! ";
                    cout << "Expected 0 at position: " << i << " " << j;
                    cout << " Got: " << testGrid[i][j] << endl;
                    error += 1; 
                }
            }
        }
    }

    return error;

}



/***** Unit test functions *****/

/* convolve a uniform grid - every element should be the same in the result */
int convUniform() {

    vector<vector<float>> input = makeGrid(SMALL_GRID, 1.0);
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

    /* create a linear kernel that is 0.1 * 100 wide*/
    vector<float> kernel1 = makeLinearKernel<float>(100, 100, 0.1);
    float kernel1Sum = kernelSum(kernel1);

    /* check size of kernel is expected */
    if (kernel1.size() != 11) {
        cout << "Error! Expected kernel size 11 got kernel size: " << kernel1.size() << endl;
        error = 1;
    }

    /* check the sum of the kernel */
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


/*
 * Perform a convolution on a matrix with all zeros and one value on the 
 * rightmost edge - check that the values are correct given the left and
 * right edge should be treated as contiguous
 */

int convVerticalEdge() {
    int gridSize = 10;
    int error = 0;

    /* get an empty grid */
    vector<vector<float>> inputRight = makeGrid(gridSize, 0.0);
    vector<vector<float>> inputLeft = makeGrid(gridSize, 0.0);

    /* set value on the far right edge to 9.0 */
    inputRight[5][9] = 9.0;
    /* set value on the far left edge to 9.0 */
    inputLeft[5][0] = 9.0;
    
    /* create 3x3 linear kernel and convolve the grid */
    vector<float> kernel = makeLinearKernel<float>(gridSize, gridSize, 0.3333);
    serialConvolve<float>(inputRight, kernel); 
    serialConvolve<float>(inputLeft, kernel); 

    /* indices of points expected to be nonzero in the form gridSize * i + j */
    vector<int> rightExpected = {40, 48, 49, 50, 58, 59, 60, 68, 69};
    vector<int> leftExpected = {40, 41, 49, 50, 51, 59, 60, 61, 69};

    /* check the values in the grids */
    error += checkGrid(inputRight, rightExpected, 1);
    error += checkGrid(inputLeft, leftExpected, 1);
    
    /* return 1 if more than 0 errors, otherwise return 0 */
    return error > 0 ? 1 : 0;

}

/*
 * Perform a convolution over the north and south poles (the upper and lower
 * edges)
 */

int convOverPoles() {
    int gridSize = 10;
    int error = 0;

    /* get an empty grid */
    vector<vector<float>> inputNorth = makeGrid(gridSize, 0.0);
    vector<vector<float>> inputSouth = makeGrid(gridSize, 0.0);

    /* set value on the upper edge to 9.0 */
    inputNorth[0][3] = 9.0;
    /* set value on the lower edge to 9.0 */
    inputSouth[9][9] = 9.0;
    
    /* create 3x3 linear kernel and convolve the grid */
    vector<float> kernel = makeLinearKernel<float>(gridSize, gridSize, 0.3333);
    serialConvolve<float>(inputNorth, kernel); 
    serialConvolve<float>(inputSouth, kernel);

    /* indices of points expected to be nonzero in the form gridSize * i + j */
    vector<int> northExpected = {2, 3, 4, 7, 8, 9, 12, 13, 14};
    vector<int> southExpected = {80, 88, 89, 90, 93, 94, 95, 98, 99};

    /* check the values in the grids */
    error += checkGrid(inputNorth, northExpected, 1);
    error += checkGrid(inputSouth, southExpected, 1);

    return error > 0 ? 1 : 0;

}
