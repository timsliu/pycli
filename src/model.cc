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
    cout << "Starting new model!" << endl;
    cout << "latCells: " << currentPlanet.getLatCells() << " ";
    cout << "longCells: " << currentPlanet.getLongCells() << endl;
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
    vector<vector<SurfaceType>>& surface = currentPlanet.getSurface();
    float co2Level = currentPlanet.getAtmosphere()["co2"];

    vector<float> EinArray = currentPlanet.getRadIn();
    for (size_t i = 0; i < currentPlanet.getLatCells(); i++ ) {
        float Ein = EinArray[i];
        for (size_t j = 0; j < currentPlanet.getLongCells(); j++) {
            float albedo = albedoMap[surface[i][j]];
            float radForc = CO2_HEATING * co2Level + H2O_POWER;  /* radiative forcing from ghg */
            float rhs = (((1 - albedo) * Ein) + radForc) /SIGMA;
            temps[i][j] = pow(rhs, 0.25);
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

