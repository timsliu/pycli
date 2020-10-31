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

protected:
    size_t steps;
    size_t currentStep{0};
    Planet currentPlanet;
    std::vector<Planet> computedPlanets;
    std::vector<std::map<std::string, float>> allAtmos;

public:
    // constructor for the planet specifying the number of model steps and the planet
    Model(size_t steps, Planet planetStart, std::vector<std::map<std::string, float>> atmos);

    // run the model
    virtual void simClimate() = 0;

    // fill in the temperatures
    virtual void calcTemps() = 0;

    // write out model results to a file
    virtual void outputResults() = 0;

};

class SerialModel : public Model {

public:
    SerialModel(size_t steps, Planet planetStart, std::vector<std::map<std::string, float>> atmos);
    
    // run the model
    void simClimate() override;

    // fill in the temperatures
    void calcTemps() override;

    // write out model results to a file
    void outputResults() override;

};

#endif /* MODEL_H */
