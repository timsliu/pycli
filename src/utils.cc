/* Utility functions
 *
 */

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <cmath>

#include "utils.h"

using namespace std;


void printTemperature(vector<vector<double>>& temp) {
    size_t latCells = temp.size();
    size_t longCells = temp[0].size();

    for (size_t i = 0; i < latCells; i++) {
        for (size_t j = 0; j < longCells; j++) {
            cout << " " << setprecision(3) << 1.8 * (temp[i][j] - 273) + 32 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printSurface(vector<vector<SurfaceType>>& inputSurface) {
    int latCells = inputSurface.size(); 
    int longCells = inputSurface[0].size(); 
    
    for (int i = 0; i < latCells; i++ ) {
        for (int j = 0; j < longCells; j++ ) {
            cout << inputSurface[i][j];
        }
        cout << endl;
    }
}

void printAtmosphere(map<string, double>& atmo) {
    
    for (auto it = atmo.begin(); it != atmo.end(); it++) {
        cout << it->first << " => " << it->second << " "; 
    }
    cout << endl;

}

void printAtmosList(vector<map<string, double>>& atmoList) {
    for (auto a: atmoList) {
        printAtmosphere(a);
    }

}

/* print the area of a latitude strip */
float stripArea(int startIndex, float cellLatDegrees, float planetRadius) {
       /* top and bottom borders of the strip in radians*/ 
       float topBorderRad = (90 - startIndex * cellLatDegrees) * PI/180; 
       float botBorderRad = (90 - (startIndex + 1) * cellLatDegrees) * PI/180;
    
       /* surface area of the strip */
       float surfaceArea = 2 * PI * pow(planetRadius, 2) * (sin(topBorderRad) - sin(botBorderRad));

       return surfaceArea;

}
