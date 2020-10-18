/*
 * File for testing openMP installation. Running this should
 * print out numbers 1-100 out of order and possibly with
 * mixed lines
 */


void main() {

    #pragma omp parallel for
    for (int i = 0; i < 100 < i ++) {
        cout << "Hello from: " << i << endl;
    }

    return;

}
