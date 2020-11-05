#include <iostream>
#include <fstream>
#include <sstream>

#include "model.h"
#include "planet.h"
#include "utils.h"
#include "constant.h"

using namespace std;

int main() {
    cout << "Welcome to PyCli!" << endl;

    cout << "Creating new planet" << endl;
    
    vector<vector<SurfaceType>> inputSurface;
    vector<map<string, float>> atmosList;

    size_t latCells;
    size_t longCells;

    /* parse the surface from a file */
    ifstream myfile("surface.txt");
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

    printSurface(inputSurface);
   
    /* parse atmosphere at each step from a file */
    ifstream atmofile("atmos.txt");

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
    latCells = inputSurface.size();
    longCells = inputSurface[0].size();

    cout << latCells << endl;
    cout << longCells << endl;

    printAtmosList(atmosList);

    /* instantiate the planet and model and run the climate */ 
    Planet samplePlanet(inputSurface, atmosList[0]);
    SerialModel sampleModel(atmosList.size(), samplePlanet, atmosList);
    sampleModel.simClimate();

    cout << "Simulation complete!" << endl;

}
