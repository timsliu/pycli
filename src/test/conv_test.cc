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


/***** Unit test functions *****/

/* convolve a uniform grid - every element should be the same in the result */

int conv_uniform() {

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


