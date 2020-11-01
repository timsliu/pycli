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

    /* parse atmosphere at each step from a file */
    ifstream atmofile("atmos.txt");
    vector<map<string, float>> atmosList;

    if (atmofile.is_open()) {
        string line;
        while (getline(atmofile, line)) {
            istringstream iss(line);
            map<string, float> atmoStep;
            int parseIndex = 0;
            string gas;
            float concentration;

            while (!iss.eof()) {
                if (parseIndex % 2 == 0) {
                    iss >> gas;
                } else {
                    iss >> concentration;
                    atmoStep.insert(pair<string, float>(gas, concentration));
                }
                parseIndex++;
            }
            atmosList.push_back(atmoStep);
        }
    }

    for (size_t i = 0; i < atmosList.size(); i++ ) {
        for (auto it = atmosList[i].begin(); it != atmosList[i].end(); it++) {
            cout << it->first << " => " << it->second << " "; 
        }
        cout << endl;
    }

    /* instantiate the planet and model and run the climate */ 
    Planet samplePlanet(latCells, longCells, inputSurface, sampleAtmos);

    SerialModel sampleModel(atmosList.size(), samplePlanet, atmosList);

    sampleModel.simClimate();

    cout << "Simulation complete!" << endl;

}
