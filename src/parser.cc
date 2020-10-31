#include <iostream>

using namespace std;

#include "model.h"
#include "planet.h"

int main() {
    cout << "Welcome to PyCli!" << endl;

    cout << "Creating new planet" << endl;

    vector<SurfaceType> strip1 = {ice, ice, ice, ice};
    vector<SurfaceType> strip2 = {sea, sea, land, sea};
    vector<SurfaceType> strip3 = {ice, sea, land, land};
    vector<SurfaceType> strip4 = {ice, ice, ice, ice};

    vector<vector<SurfaceType>> sampleSurface = {strip1, strip2, strip3, strip4};
    map<string, float> sampleAtmos = {{"co2", 0.01}, {"o2", 22}, {"n2", 77.99}};

    Planet samplePlanet(4, 4, sampleSurface, sampleAtmos);

    Model sampleModel(10, samplePlanet);

    sampleModel.simClimate();

    cout << "Simulation complete!" << endl;

}
