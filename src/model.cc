/*
 * model.cc
 * backend for running the python climate modeling DSL 
 *
 */

#include "model.h"
#include <iostream>

using namespace std;

Model::Model(size_t steps, Planet planetStart): 
    steps(steps), 
    currentPlanet(planetStart) {
}


void Model::simClimate() {

    cout << "Starting climate sim" << endl;
    for (size_t i = 0; i < steps; i++ ) {
        cout << "Model step: " << i << endl; 
        calcTemps();
        cout << "Temperatures calculated" << endl;

        // add copy of current planet to the list of computed planets
        Planet lastPlanet = Planet(currentPlanet);
        computedPlanets.push_back(lastPlanet);
        currentStep++;
    }

    // write out results to a file
    outputResults();

}


// calculate fill in the temperatures of the planet
void Model::calcTemps() {

    cout << "Calculating temperatures" << endl;
    vector<vector<float>>& temps = currentPlanet.getTemperature();
    cout << "Current step" << endl;

    for (size_t i = 0; i < currentPlanet.getLatCells(); i++ ) {
        for (size_t j = 0; j < currentPlanet.getLongCells(); j++) {
            temps[i][j] = (float) currentStep + 0.01 * (float) i + 0.001 * (float) j;
        }
    }
}

void Model::outputResults() {

    cout << "Outputting results" << endl;
    // print all of the planets
    for (size_t i = 0; i < computedPlanets.size(); i++) {
        computedPlanets[i].printPlanet(i);
    }
}
