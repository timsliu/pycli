/*
 *  Header file for planet.cc. The planet class represents a planet including
 *  the surface types, level of discretization, temperature, and atmospheric
 *  makeup
 */

#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <map>
#include <fstream>

#include "constant.h"
#include "utils.h"

class Planet {

private:

    size_t _longCells;                // number of cells 360 degrees of longitude are broken into
    size_t _latCells;                 // number of cells 180 degrees latitude are broken into

    std::vector<std::vector<SurfaceType>> _surface; // type of surface in each cell
    std::map<std::string, double> _atmosphere;   // mapping between gases and atmosphere concentration
    
    double _cellLongDegrees;
    double _cellLatDegrees;            // dimension of each cells in latitude and long

    std::vector<std::vector<double>> _temperature;   // temperature of surface in each cell
    std::vector<double> _radIn;        // incoming radiation for each latitude cell

    double _planetRadius{EARTH_RADIUS};
   
    // private helper methods
    double calcFluxAntideri(double x);

public:

    // constructor
    Planet(std::vector<std::vector<SurfaceType>> &surface,
           std::map<std::string, double> &atmosphere);

  
   // return reference to the surface
   std::vector<std::vector<SurfaceType>>&  getSurface() { return _surface; }

   // return reference to the temperature
   std::vector<std::vector<double>>& getTemperature() { return _temperature; }

   size_t getLongCells() { return _longCells; }

   size_t getLatCells() { return _latCells; }

   void setAtmosphere(std::map<std::string, double> atmo) {
       _atmosphere = atmo;
   }
   
   std::map<std::string, double>& getAtmosphere() { return _atmosphere; }

   std::vector<double>& getRadIn() { return _radIn; }

   void calcRadIn();


   void printPlanet(size_t step, std::ofstream& outFile);
};

#endif /* PLANET_H */
