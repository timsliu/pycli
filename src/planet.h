/*
 *  Header file for planet.cc. The planet class represents a planet including
 *  the surface types, level of discretization, temperature, and atmospheric
 *  makeup
 */

#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <map>

// types of surfaces
enum SurfaceType {
    land,
    sea,
    ice
};

class Planet {

private:

    map<string, float> atmosphere;   // mapping between gases and atmosphere concentration
    size_t longCells;                // number of cells 360 degrees of longitude are broken into
    size_t latCells;                 // number of cells 180 degrees latitude are broken into
    float cellLatDegrees;            // dimension of each cells in latitude and long
    float cellLongDegrees;

    vector<vector<SurfaceType>> surface; // type of surface in each cell
    vector<vector<float>> temperature;   // temperature of surface in each cell

public:

    // constructor
    Planet(size_t longCells, size_t latCells, vector<vector<SurfaceType>> &surface);


};

#endif /* PLANET_H */
