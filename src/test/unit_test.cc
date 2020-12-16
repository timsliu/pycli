/*
 * Functions for testing convolution.h functions
 */

#include "test.h"
#include "conv_test.h"
#include "omp_test.h"

using namespace std;


int main(int argc, char *argv[]) {

    /* assemble structs with all tests */
    struct testType test1 = {"conv_uniform", "convolve a uniform grid", &conv_uniform};

    /* assemble testType structs into single vector */
    vector<testType> allTests = {test1};
    
    int success = allTests.size();       // counter for number of successful tests
    cout << endl;
    
    /* loop through test vector list */
    for (size_t i = 0; i < allTests.size(); i++) {
        cout << "Test " << i << ": " << allTests[i].testName << endl;
        cout << allTests[i].testDescription << endl;

        int result = allTests[i].testFunc();

        if (result != 0) {
            cout << "Test " << i << " failed" << endl;
            success--;
        }
        cout << endl;
    }

    cout << "******************* Test Results *******************" << endl;
    cout << "Total Tests: " << allTests.size() << "    " << "Successful Tests: " << success << endl;
    cout << "****************************************************" << endl;

    return 0;
}
