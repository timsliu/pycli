/*
 * model.cc
 * backend for running the python climate modeling DSL 
 *
 */

#include "model.h"

using namespace std;

Model::Model(size_t steps, Planet planetStart): 
    steps(steps), 
    currentPlanet(planetStart) {
}


void Model::simClimate() {

    for (size_t i = 0; i < steps; i++ ) {
        calcTemps();

        // add copy of current planet to the list of computed planets
        Planet lastPlanet = Planet(currentPlanet);
        computedPlanets.push_back(lastPlanet);
    }

    // write out results to a file
    outputResults();

}


// calculate fill in the temperatures of the planet
void Model::calcTemps() {
    vector<vector<float>> temps = currentPlanet.getTemperature();

    for (size_t i = 0; i < currentPlanet.getLatCells(); i++ ) {
        for (size_t j = 0; j < currentPlanet.getLongCells(); j++) {
            temps[i][j] = currentStep;
        }
    }
}

void Model::outputResults() {

}
