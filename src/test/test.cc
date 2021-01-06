/* 
 * Helper functions for tests
 */


#include "test.h"

using namespace std;

bool close(float a, float b) {
    return abs(a - b)/a < 0.0001;
}
