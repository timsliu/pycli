#include <iostream>
#include <fstream>
#include <sstream>

#include "model.h"
#include "planet.h"
#include "utils.h"
#include "constant.h"

using namespace std;

void printHelp() {
    cout << "\nExpecting arguments: " << endl;
    cout << "<model_dir> path relative to MODEL_IN with atmosphere and surface files" << endl;
    cout << "            this arg will be appended to MODEL_OUT and filled with output files" << endl;
    cout << "-v (optional) verbose flag; default false" << endl;
    cout << "-e (optional) atmosphere is emissions; default atmos is concentration" << endl;
    cout << "-m <model_name>(optional) flag specifying model; serial (default), accel" << endl;
}

int main(int argc, char *argv[]) {
    cout << "Welcome to PyCli!" << endl;

    bool verbose = false;
    bool emission = false;
    string modelType = "serial";

    string inputDir;
    string outputDir;

    string surfaceFile;
    string atmosFile;

    vector<string> allArgs(argv, argv + argc);
    try {
        verbose = false;                /* default verbose value */
        emission = false;    /* default atmosphere specification */
        modelType = "serial";           /* default model */

        inputDir = MODEL_IN + allArgs[1];
        outputDir = MODEL_OUT + allArgs[1] + "/out";
        surfaceFile = inputDir + "/surface.txt";
        atmosFile = inputDir + "/atmosphere.txt";

        for (int i = 0; i < argc; i++ ) {
            if (allArgs[i] == "-v") {
                verbose = true;
            }
            if (allArgs[i] == "-m") {
                modelType = allArgs[i + 1];
            }
            if (allArgs[i] == "-e") {
                emission = true;
            }
        }
    } 
    catch (const exception &e) {
        cout << "Error while parsing arguments: " << e.what() << endl;
        printHelp();
        return 1;
    }

    if (verbose) {
        cout << "Parsing surface file: " << surfaceFile << endl;
    }

    vector<vector<SurfaceType>> inputSurface;   // starting surface
    vector<map<string, double>> atmosList;       // atmosphere at each step

    /* parse the surface from a file */
    ifstream myfile(surfaceFile);
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
   
    if (verbose) {
        cout << "Parsing temperature file: " << atmosFile << endl;
    }
    
    /* parse atmosphere at each step from a file */
    ifstream atmofile(atmosFile);

    if (atmofile.is_open()) {
        string line;
        while (getline(atmofile, line)) {
            istringstream iss(line);
            map<string, double> atmoStep;
            int parseIndex = 0;
            string gas;
            double quantity;

            while (!iss.eof()) {
                if (parseIndex % 2 == 0) {
                    iss >> gas;
                } else {
                    iss >> quantity;
                    /* convert from emission level to concentration */
                    double concentration = quantity;
                    if (atmosList.size() > 0 and emission) {
                        /* conversion for CO2 */ 
                        if (gas.compare("CO2") == 0) {
                            concentration = quantity * CO2_EMIT2CONC * CO2_ATMOS + atmosList.back()[gas];
                        }
                    }
                    /* insert gas and concentration */
                    cout << concentration;
                    atmoStep.insert(pair<string, double>(gas, concentration));
                }
                parseIndex++;
            }
            atmosList.push_back(atmoStep);
        }
    }
   

    /* instantiate the planet and model and run the climate */ 
    Planet samplePlanet(inputSurface, atmosList[0]);

    if (modelType == "serial") {
        SerialModel climateModel(atmosList.size(), samplePlanet, atmosList, verbose, outputDir);
        climateModel.simClimate(); 
    }
    else if (modelType == "accel") {
        AccelModel climateModel(atmosList.size(), samplePlanet, atmosList, verbose, outputDir);
        climateModel.simClimate(); 
    }
    else {
        cout << "Model type " << modelType << " not recognized" << endl;
        printHelp();
        return 1;
    }

    if (verbose) {
        cout << "Simulation complete!" << endl;
    }

    return 0;

}
