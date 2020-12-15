/*
 * File for testing openMP installation. Running this should
 * print out numbers 1-100 out of order and possibly with
 * mixed lines
 */

#include <iostream>

using namespace std;
int main() {

    #pragma omp parallel for
    for (int i = 0; i < 20; i ++) {
        cout << "Hello from: " << i << endl;
    }

    return 0;

}
