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
               map<string, double> &atmosphere):
   _longCells(surface[0].size()),
   _latCells(surface.size()),
   _surface(surface),
   _atmosphere(atmosphere), 
   _cellLongDegrees(LONG_RANGE/static_cast<double>(_longCells)),
   _cellLatDegrees(LAT_RANGE/static_cast<double>(_latCells)),
   _radIn(_latCells){

   // create empty vector for temperatures
   for (size_t i = 0; i < _latCells; i ++ ) {
       vector<double> latTemps(_longCells); 
       _temperature.push_back(latTemps);
   }

    // call function to fill in the incoming radiation vector
   calcRadIn();
}


// calculate the radiation at each cell
void Planet::calcRadIn() {
    
    for (size_t i = 0; i < _latCells/2; i++ ) {
       double topBorderRad = (90 - i * _cellLatDegrees) * PI/180; 
       double botBorderRad = (90 - (i + 1) * _cellLatDegrees) * PI/180;
       double rSq = _planetRadius * _planetRadius;
       
       double topBorderM = _planetRadius * sin(topBorderRad);
       double botBorderM = _planetRadius * sin(botBorderRad);
       
       double interceptedArea = calcFluxAntideri(topBorderM) - calcFluxAntideri(botBorderM);

       double surfaceArea = 2 * PI * rSq * (sin(topBorderRad) - sin(botBorderRad));
       double _radInLat = W_SUN * interceptedArea/surfaceArea;

       _radIn[i] = _radInLat;
    }

    // radiation in is mirrored above and below the equator
    size_t j = 0;
    for (size_t i = _latCells/2; i < _latCells; i++) {
        _radIn[i] = _radIn[_latCells/2 - 1 - j];
        j++;
    }
   
}

double Planet::calcFluxAntideri(double x) {
    double xSq = x * x;
    double rSq = _planetRadius * _planetRadius;

    if (abs((x - _planetRadius)/x) < 0.00001 ) {
        return rSq * PI/2;
    }

    double termOne = x * sqrt(rSq - xSq);
    double termTwo = rSq * atan(termOne/(xSq - rSq));

    return termOne - termTwo;
}

void Planet::printPlanet(ofstream& outFile) {

    for (size_t i = 0; i < _latCells; i++) {
        for (size_t j = 0; j < _longCells; j++) {
            outFile << " " << setprecision(3) <<  _temperature[i][j] << " ";
        }
        outFile << endl;
    }
}

void Planet::setAverageTemp(float temp) {
    _averageTemp = temp;
}
