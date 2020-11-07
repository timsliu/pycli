/*
 * Implementation of planet class. The planet class describes the
 * surface of the planet, the planet discretization, and the temperature.
 *
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

#include "planet.h"

using namespace std;

// constructor for a new planet
Planet::Planet(vector<vector<SurfaceType>> &surface,
               map<string, float> &atmosphere):
   _longCells(surface[0].size()),
   _latCells(surface.size()),
   _surface(surface),
   _atmosphere(atmosphere), 
   _cellLongDegrees(LONG_RANGE/_longCells),
   _cellLatDegrees(LAT_RANGE/_latCells),
   _radIn(_latCells){

   // create empty vector for temperatures
   for (size_t i = 0; i < _latCells; i ++ ) {
       vector<float> latTemps(_longCells); 
       _temperature.push_back(latTemps);
   }

    // call function to fill in the incoming radiation vector
   calcRadIn();
}


// calculate the radiation at each cell
void Planet::calcRadIn() {
    
    for (size_t i = 0; i < _latCells/2; i++ ) {
       float topBorderRad = (90 - i * _cellLatDegrees) * PI/180; 
       float botBorderRad = (90 - (i + 1) * _cellLatDegrees) * PI/180;
       float rSq = _planetRadius * _planetRadius;

       float topBorderM = _planetRadius * sin(topBorderRad);
       float botBorderM = _planetRadius * sin(botBorderRad);

       float interceptedArea = calcFluxAntideri(topBorderM) - calcFluxAntideri(botBorderM);
       float surfaceArea = 2 * PI * rSq * (sin(topBorderRad) - sin(botBorderRad));
       float _radInLat = W_SUN * interceptedArea/surfaceArea;

       _radIn[i] = _radInLat;
    }

    // radiation in is mirrored above and below the equator
    size_t j = 0;
    for (size_t i = _latCells/2; i < _latCells; i++) {
        _radIn[i] = _radIn[_latCells/2 - 1 - j];
        j++;
    }
   
    //for (size_t i = 0; i < _latCells; i++) {
    //    cout << "Radiation at index: " << i << " " << _radIn[i] << endl;
    //}

}

float Planet::calcFluxAntideri(float x) {
    float xSq = x * x;
    float rSq = _planetRadius * _planetRadius;

    if (abs((x - _planetRadius)/x) < 0.00001 ) {
        return rSq * PI/2;
    }

    float termOne = x * sqrt(rSq - xSq);
    float termTwo = rSq * atan(termOne/(xSq - rSq));

    return termOne - termTwo;
}

void Planet::printPlanet(size_t step) {
    cout << "Temperatures at timestep: " << step << endl;

    // TODO update to make a file
    ofstream outFile ("out/temp_" + to_string(step) + ".txt");

    for (size_t i = 0; i < _latCells; i++) {
        for (size_t j = 0; j < _longCells; j++) {
            outFile << " " << setprecision(3) << 1.8 * (_temperature[i][j] - 273) + 32 << " ";
        }
        outFile << endl;
    }

    outFile.close();

    // printTemperature(_temperature);
}


