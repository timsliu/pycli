/*
 * Implementation of planet class. The planet class describes the
 * surface of the planet, the planet discretization, and the temperature.
 *
 */

#include <iostream>
#include <cmath>

#include "planet.h"

using namespace std;

// constructor for a new planet
Planet::Planet(size_t longCells, 
               size_t latCells, 
               vector<vector<SurfaceType>> &surface,
               map<string, float> &atmosphere):
   longCells(longCells),
   latCells(latCells),
   surface(surface),
   atmosphere(atmosphere), 
   cellLongDegrees(LONG_RANGE/longCells),
   cellLatDegrees(LAT_RANGE/latCells),
   radIn(latCells){

   // create empty vector for temperatures
   for (size_t i = 0; i < longCells; i ++ ) {
       vector<float> latTemps(longCells); 
       temperature.push_back(latTemps);
   }

    // call function to fill in the incoming radiation vector
   calcRadIn();
}


// calculate the radiation at each cell
void Planet::calcRadIn() {
    
    for (size_t i = 0; i < latCells/2; i++ ) {
       float topBorderRad = (90 - i * cellLatDegrees) * PI/180; 
       float botBorderRad = (90 - (i + 1) * cellLatDegrees) * PI/180;
       float rSq = planetRadius * planetRadius;

       float topBorderM = planetRadius * sin(topBorderRad);
       float botBorderM = planetRadius * sin(botBorderRad);

       cout << "\nTop border: " << topBorderM << endl;
       cout << "Bot border: " << botBorderM << endl;
       cout << "Top border rad: " << topBorderRad << endl;
       cout << "Bot border rad: " << botBorderRad << endl;

       float interceptedArea = calcFluxAntideri(topBorderM) - calcFluxAntideri(botBorderM);
       float surfaceArea = 2 * PI * rSq * (sin(topBorderRad) - sin(botBorderRad));

       cout << "Surface Area: " << surfaceArea << endl;
       cout << "Intercepted Area: " << interceptedArea << endl;

       float radInLat = W_SUN * interceptedArea/surfaceArea;

       radIn[i] = radInLat;
    }

    // radiation in is mirrored above and below the equator
    size_t j = 0;
    for (size_t i = latCells/2; i < latCells; i++) {
        radIn[i] = radIn[latCells/2 - 1 - j];
        j++;
    }
   
    for (size_t i = 0; i < latCells; i++) {
        cout << "Radiation at index: " << i << " " << radIn[i] << endl;
    }

}

float Planet::calcFluxAntideri(float x) {
    float xSq = x * x;
    float rSq = planetRadius * planetRadius;

    if (abs((x - planetRadius)/x) < 0.00001 ) {
        return rSq * PI/2;
    }

    float termOne = x * sqrt(rSq - xSq);
    float termTwo = rSq * atan(termOne/(xSq - rSq));

    return termOne - termTwo;
}

void Planet::printPlanet(size_t step) {
    cout << "Temperatures at timestep: " << step << endl;
    printTemperature(temperature);
}


