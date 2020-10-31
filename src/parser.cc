#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "model.h"
#include "planet.h"

int main() {
    cout << "Welcome to PyCli!" << endl;

    cout << "Creating new planet" << endl;


    /* declare a sample surface explicitly */
    vector<SurfaceType> strip1 = {ice, ice, ice, ice};
    vector<SurfaceType> strip2 = {sea, sea, land, sea};
    vector<SurfaceType> strip3 = {ice, sea, land, land};
    vector<SurfaceType> strip4 = {ice, ice, ice, ice};

    vector<vector<SurfaceType>> sampleSurface = {strip1, strip2, strip3, strip4};

    /* parse the surface from a file */
    ifstream myfile("surface.txt");
    vector<vector<SurfaceType>> inputSurface;

    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            istringstream iss(line);
            vector<SurfaceType> latSurface;
            while (!iss.eof()) {
                int value;
                iss >> value;
                latSurface.push_back(static_cast<SurfaceType>(value));
            }
            inputSurface.push_back(latSurface);
        }
    }

    /* print out the parsed surface to ensure it looks correct */
    int latCells = inputSurface.size(); 
    int longCells = inputSurface[0].size(); 
    
    for (int i = 0; i < latCells; i++ ) {
        for (int j = 0; j < longCells; j++ ) {
            cout << inputSurface[i][j];
        }
        cout << endl;
    }
   
    /* explicitly define an atmosphere */
    map<string, float> sampleAtmos = {{"co2", 0.01}, {"o2", 22}, {"n2", 77.99}};

    
    Planet samplePlanet(latCells, longCells, inputSurface, sampleAtmos);

    SerialModel sampleModel(10, samplePlanet);

    sampleModel.simClimate();

    cout << "Simulation complete!" << endl;

}
