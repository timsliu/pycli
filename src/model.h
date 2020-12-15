/*
 * Header file for model.cc. The model class has an instance of the
 * planet class as an attribute and simulates the temperature over
 * the surface of the planet.
 *
 */


#ifndef MODEL_H
#define MODEL_H

#include "planet.h"
#include "utils.h"
#include "conv.h"

class Model {

protected:
    size_t _steps;
    size_t _currentStep{0};
    Planet _currentPlanet;
    std::vector<Planet> _computedPlanets;
    std::vector<std::map<std::string, double>> _allAtmos;
    bool _verbose{false};
    std::string _outputDir;

public:
    // constructor for the planet specifying the number of model steps and the planet
    Model(size_t steps, Planet planetStart, std::vector<std::map<std::string, double>> atmos, 
          bool verbose, std::string outputDir);

    // run the model
    void simClimate();

    // write out model results to a file
    void outputResults();
    
    // fill in the temperatures
    virtual void calcTemps() = 0;


    std::map<SurfaceType, double> albedoMap = {{land, 0.2}, {sea, 0.06}, {ice, 0.6}};

};

class SerialModel : public Model {

public:
    SerialModel(size_t steps, Planet planetStart, std::vector<std::map<std::string, double>> atmos, 
                bool verbose, std::string outputDir);
    
    // fill in the temperatures at one step
    void calcTemps() override;

};

class AccelModel : public Model {

public:
    AccelModel(size_t steps, Planet planetStart, std::vector<std::map<std::string, double>> atmos, 
               bool verbose, std::string outputDir);
    
    // fill in the temperatures at one step
    void calcTemps() override;

};

#endif /* MODEL_H */
