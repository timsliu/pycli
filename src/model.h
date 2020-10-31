/*
 * Header file for model.cc. The model class has an instance of the
 * planet class as an attribute and simulates the temperature over
 * the surface of the planet.
 *
 */


#ifndef MODEL_H
#define MODEL_H

#include "planet.h"

class Model {

private:
    size_t steps;
    Planet currentPlanet;
    std::vector<Planet> computedPlanets;

public:
    // constructor for the planet specifying the number of model steps and the planet
    Model(size_t steps, Planet planetStart);

    // run the model
    void simClimate();

    // fill in the temperatures
    void calcTemps();

    // write out model results to a file
    void outputResults();

};



#endif /* MODEL_H */
