/*
 * Implementation of planet class. The planet class describes the
 * surface of the planet, the planet discretization, and the temperature.
 *
 */

using namespace std;

#include "planet.h"

Planet::Planet(size_t longCells, size_t latCells, vector<vector<SurfaceType>> &surface) {
    this->longCells = longCells;
    this->latCells = latCells;
}



