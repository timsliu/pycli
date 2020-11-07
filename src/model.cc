/*
 * model.cc
 * backend for running the python climate modeling DSL 
 *
 */

#include "model.h"
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

Model::Model(size_t steps, Planet planetStart, vector<map<string, float>> atmos): 
    _steps(steps), 
    _currentPlanet(planetStart),
    _allAtmos(atmos){
    cout << "Starting new model!" << endl;
    cout << "latCells: " << _currentPlanet.getLatCells() << " ";
    cout << "longCells: " << _currentPlanet.getLongCells() << endl;
}

void Model::simClimate() {

    cout << "Starting climate sim" << endl;
    auto start = chrono::system_clock::now();
    for (size_t i = 0; i < _steps; i++ ) {
        // set the atmosphere of the planet and calculate temperatures
        _currentPlanet.setAtmosphere(_allAtmos[i]);
        calcTemps();

        // add copy of current planet to the list of computed planets
        Planet lastPlanet = Planet(_currentPlanet);
        _computedPlanets.push_back(lastPlanet);
        _currentStep++;
    }
    auto end = chrono::system_clock::now();
    
    chrono::duration<double> diff = end - start;
    cout << "Model completed! Computed " << _steps << " steps ";
    cout << _currentPlanet.getLatCells() * _currentPlanet.getLongCells() << " cells ";
    cout << "in " << diff.count() << " s" << endl;
    // write out results to a file
    outputResults();
}

void Model::outputResults() {

    cout << "Outputting results" << endl;
    // print all of the planets
    for (size_t i = 0; i < _computedPlanets.size(); i++) {
        _computedPlanets[i].printPlanet(i);
    }
}

/*
 * Serial model computation steps
 *
 */

SerialModel::SerialModel(size_t steps, Planet planetStart, vector<map<string, float>> atmos): 
    Model(steps, planetStart, atmos) {
    cout << "Creating Serial Model" << endl;
}


// calculate fill in the temperatures of the planet
void SerialModel::calcTemps() {

    vector<vector<float>>& temps = _currentPlanet.getTemperature();
    vector<vector<SurfaceType>>& surface = _currentPlanet.getSurface();
    float co2Level = _currentPlanet.getAtmosphere()["co2"];

    vector<float> EinArray = _currentPlanet.getRadIn();
    for (size_t i = 0; i < _currentPlanet.getLatCells(); i++ ) {
        float Ein = EinArray[i];
        for (size_t j = 0; j < _currentPlanet.getLongCells(); j++) {
            float albedo = albedoMap[surface[i][j]];
            float radForc = CO2_HEATING * co2Level + H2O_POWER;  /* radiative forcing from ghg */
            float rhs = (((1 - albedo) * Ein) + radForc) /SIGMA;
            temps[i][j] = pow(rhs, 0.25);
        }
    }
}


/*
 * Parallel model computation steps
 *
 */


AccelModel::AccelModel(size_t steps, Planet planetStart, vector<map<string, float>> atmos): 
    Model(steps, planetStart, atmos) {
    cout << "Creating Accel Model" << endl;
}


// calculate fill in the temperatures of the planet
void AccelModel::calcTemps() {

    vector<vector<float>>& temps = _currentPlanet.getTemperature();
    vector<vector<SurfaceType>>& surface = _currentPlanet.getSurface();
    float co2Level = _currentPlanet.getAtmosphere()["co2"];

    vector<float> EinArray = _currentPlanet.getRadIn();
    float radForc = CO2_HEATING * co2Level + H2O_POWER;
        
    #pragma omp parallel for 
    for (size_t i = 0; i < _currentPlanet.getLatCells(); i++ ) {
        float Ein = EinArray[i];
        for (size_t j = 0; j < _currentPlanet.getLongCells(); j++) {
            float albedo = albedoMap[surface[i][j]];

            /* greenhouse gas effect */
            float rhs = (((1 - albedo) * Ein) + radForc) /SIGMA;
            temps[i][j] = pow(rhs, 0.25);
        }
    }
}


