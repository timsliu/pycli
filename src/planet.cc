/*
 * Implementation of planet class. The planet class describes the
 * surface of the planet, the planet discretization, and the temperature.
 *
 */


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

    // call function to fill in the incoming radiation vector
   calcRadIn();
}


// calculate the radiation at each cell
void Planet::calcRadIn() {
    
    for (size_t i = 0; i < latCells/2; i++ ) {
       //float topBorderDeg = 90 - i * cellLatDegrees; 
       //float botBorderDeg = 90 - (i + 1) * cellLatDegrees;

       //float topBorderKm = EARTH_RADIUS * sin(topBorderDeg);
       //float botBorderKm = EARTH_RADIUS * sin(botBorderDeg);

       //// area from integrating latitudinal slice 
       //float area = topBorderDeg 
    }

}




