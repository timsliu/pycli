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
#include "utils.h"

class Planet {

private:

    size_t _longCells;                // number of cells 360 degrees of longitude are broken into
    size_t _latCells;                 // number of cells 180 degrees latitude are broken into

    std::vector<std::vector<SurfaceType>> _surface; // type of surface in each cell
    std::map<std::string, float> _atmosphere;   // mapping between gases and atmosphere concentration
    
    float _cellLongDegrees;
    float _cellLatDegrees;            // dimension of each cells in latitude and long

    std::vector<std::vector<float>> _temperature;   // temperature of surface in each cell
    std::vector<float> _radIn;        // incoming radiation for each latitude cell

    float _planetRadius{EARTH_RADIUS};
   
    // private helper methods
    float calcFluxAntideri(float x);

public:

    // constructor
    Planet(std::vector<std::vector<SurfaceType>> &surface,
           std::map<std::string, float> &atmosphere);

  
   // return reference to the surface
   std::vector<std::vector<SurfaceType>>&  getSurface() { return _surface; }

   // return reference to the temperature
   std::vector<std::vector<float>>& getTemperature() { return _temperature; }

   size_t getLongCells() { return _longCells; }

   size_t getLatCells() { return _latCells; }

   void setAtmosphere(std::map<std::string, float> atmo) {
       _atmosphere = atmo;
   }
   
   std::map<std::string, float>& getAtmosphere() { return _atmosphere; }

   std::vector<float>& getRadIn() { return _radIn; }

   void calcRadIn();


   void printPlanet(size_t step);
};

#endif /* PLANET_H */
