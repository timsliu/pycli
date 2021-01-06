/* Header file for unit_tests.cc
 *
 * All unit tests MUST meet the following requirements:
 *
 * 1) Prototype must return an int and take no arguments
 * 2) If the test passes, return 0; otherwise return 1
 * 3) Test should be silent (output nothing) if the test passed
 * 4) Test must print an appropriate error message if the test failed  
 *
 */

#ifndef TEST_H
#define TEST_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include "./../constant.h"

#define MAX_ERRORS 10

/* returns if two values are "close" to each other */
bool close(float a, float b);

struct testType {
    std::string testName;
    std::string testDescription;
    int(*testFunc)();
};


#endif /* TEST_H */
