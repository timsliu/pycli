/*
 * File for testing openMP installation. Running this should
 * print out numbers 1-20 out of order and possibly with
 * mixed lines
 */

#include <iostream>
#include "omp_test.h"

using namespace std;
int omp_test_1() {

    #pragma omp parallel for
    for (int i = 0; i < 20; i ++) {
        cout << "Hello from: " << i << endl;
    }

    return 0;
}
