/*
 * Functions for testing convolution.h functions
 */

#include "test.h"


using namespace std;

/* convolve a uniform grid - every element should be the same in the result */

void conv_uniform() {

}



int main(int argc, char *argv[]) {

    vector<testType> allTests = {struct testType a{"conv_uniform", "convolve a uniform grid", &conv_uniform}};
    /* loop through test vector list */ 


    return 0;
}
