#include <iostream>
#include <fstream>
#include <sstream>

#include "model.h"
#include "planet.h"
#include "utils.h"
#include "constant.h"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Welcome to PyCli!" << endl;

    if (argc != 3) {
        cout << "Expecting 2 arguments ";
        cout << "- surface text file and atmosphere text file" << endl;
    }

    cout << "Parsing surface file: " << argv[1] << endl;

    vector<vector<SurfaceType>> inputSurface;   // starting surface
    vector<map<string, float>> atmosList;       // atmosphere at each step

    size_t latCells;       // number of latitude cells (rows)
    size_t longCells;      // number of longitude cells (cols)

    /* parse the surface from a file */
    ifstream myfile(argv[1]);
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
    
    cout << "Parsing temperature file: " << argv[2] << endl;
    /* parse atmosphere at each step from a file */
    ifstream atmofile(argv[2]);

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
   
    // get dimensions of the grid
    latCells = inputSurface.size();
    longCells = inputSurface[0].size();

    cout << "Number of latCells: " << latCells << endl;
    cout << "Number of longCells: " << longCells << endl;
    cout << "Starting simulation..." << endl;

    /* instantiate the planet and model and run the climate */ 
    Planet samplePlanet(inputSurface, atmosList[0]);
    AccelModel sampleModel(atmosList.size(), samplePlanet, atmosList);
    sampleModel.simClimate();

    cout << "Simulation complete!" << endl;

    return 0;

}
