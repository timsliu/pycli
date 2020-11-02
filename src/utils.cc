/* Utility functions
 *
 */

using namespace std;

#include "utils.h"
#include <iostream>
#include <vector>
#include <map>

void printTemperature(vector<vector<float>>& temp) {
    size_t latCells = temp.size();
    size_t longCells = temp[0].size();

    for (size_t i = 0; i < latCells; i++) {
        for (size_t j = 0; j < longCells; j++) {
            cout << " " << temp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void printAtmosphere(map<string, float>& atmo) {
    
    for (auto it = atmo.begin(); it != atmo.end(); it++) {
        cout << it->first << " => " << it->second << " "; 
    }
    cout << endl;

}

void printAtmosList(vector<map<string, float>>& atmoList) {
    for (auto a: atmoList) {
        printAtmosphere(a);
    }

}
