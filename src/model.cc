/*
 * model.cc
 * backend for running the python climate modeling DSL 
 *
 */

#include "model.h"
#include <iostream>
#include <cmath>

using namespace std;

Model::Model(size_t steps, Planet planetStart, vector<map<string, float>> atmos): 
    steps(steps), 
    currentPlanet(planetStart),
    allAtmos(atmos){
}

SerialModel::SerialModel(size_t steps, Planet planetStart, vector<map<string, float>> atmos): 
    Model(steps, planetStart, atmos) {
}


void SerialModel::simClimate() {

    cout << "Starting climate sim" << endl;
    for (size_t i = 0; i < steps; i++ ) {
        // set the atmosphere of the planet and calculate temperatures
        currentPlanet.setAtmosphere(allAtmos[i]);
        calcTemps();

        // add copy of current planet to the list of computed planets
        Planet lastPlanet = Planet(currentPlanet);
        computedPlanets.push_back(lastPlanet);
        currentStep++;
    }
    // write out results to a file
    outputResults();
}


// calculate fill in the temperatures of the planet
void SerialModel::calcTemps() {

    vector<vector<float>>& temps = currentPlanet.getTemperature();
    vector<float> EinArray = currentPlanet.getRadIn();
    for (size_t i = 0; i < currentPlanet.getLatCells(); i++ ) {
        for (size_t j = 0; j < currentPlanet.getLongCells(); j++) {
            float Ein = EinArray[i]; 
            temps[i][j] = pow(Ein/SIGMA, 0.25);
        }
    }
}

void SerialModel::outputResults() {

    cout << "Outputting results" << endl;
    // print all of the planets
    for (size_t i = 0; i < computedPlanets.size(); i++) {
        computedPlanets[i].printPlanet(i);
    }
}

