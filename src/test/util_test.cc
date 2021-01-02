/*
 * Functions for testing convolution.h functions
 */

#include "test.h"
#include "util_test.h"


using namespace std;


/* returns if two values are "close" to each other */
bool close(float a, float b) {
    return abs(a - b)/a < 0.00001;
}


/***** Unit test functions *****/

/* check that the area of strips above and below the equator are the same */
int areaStripSymmetry() {
    int error = 0;
    
    if (!close(stripArea(0, 10, TEST_RADIUS), stripArea(17, 10, TEST_RADIUS))) {
        error = 1; 
        cout << "Error! Strips at index 0 and 17 should have equal size" << endl;
    }
    
    if (!close(stripArea(24, 3.6, TEST_RADIUS), stripArea(25, 3.6, TEST_RADIUS))) {
        error = 1; 
        cout << "Error! Strips at index 24 and 25 should have equal size" << endl;
    }
    /* return 1 if more than 0 errors, otherwise return 0 */
    return error;
}

/*
 * check that the area of the sum of the strips is equal to the surface area of a sphere
 */

int areaStripSumEqual() {

    int error = 0;
    float stripTotalArea = 0;
    int numStrips = 20;

    /* calculate area by summing the strips */
    for (int i = 0; i < numStrips; i++) {
        stripTotalArea += stripArea(i, LAT_RANGE/numStrips, TEST_RADIUS); 
    }

    /* calculate area of the sphere */
    float sphereArea = 4.0 * PI * pow(TEST_RADIUS, 2);

    /* call error if the areas are not the same*/
    if (!close(sphereArea, stripTotalArea)) {
        error = 1;
        cout << "Error! Area of sphere: " << sphereArea;
        cout << "  does not much sum of strips: " << stripTotalArea << endl;
    }

    return error;
}


