/*
 *  Header file for planet.cc. The planet class represents a planet including
 *  the surface types, level of discretization, temperature, and atmospheric
 *  makeup
 */

#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <map>
#include "constant.h"

// types of surfaces
enum SurfaceType {
    land,
    sea,
    ice
};

class Planet {

private:

    size_t longCells;                // number of cells 360 degrees of longitude are broken into
    size_t latCells;                 // number of cells 180 degrees latitude are broken into

    std::vector<std::vector<SurfaceType>> surface; // type of surface in each cell
    std::map<std::string, float> atmosphere;   // mapping between gases and atmosphere concentration
    
    float cellLongDegrees;
    float cellLatDegrees;            // dimension of each cells in latitude and long

    std::vector<std::vector<float>> temperature;   // temperature of surface in each cell
    std::vector<float> radIn;        // incoming radiation for each latitude cell

public:

    // constructor
    Planet(size_t longCells, 
           size_t latCells, 
           std::vector<std::vector<SurfaceType>> &surface,
           std::map<std::string, float> &atmosphere);

  
   // return reference to the surface
   std::vector<std::vector<SurfaceType>>&  getSurface() { return surface; }

   // return reference to the temperature
   std::vector<std::vector<float>>& getTemperature() { return temperature; }

   size_t getLongCells() { return longCells; }

   size_t getLatCells() { return latCells; }

   void setAtmosphere(std::map<std::string, float> atmo) {
       atmosphere = atmo;
   }

   std::vector<float>& getRadIn() { return radIn; }

   void calcRadIn();

   void printPlanet(size_t step);
};

#endif /* PLANET_H */
