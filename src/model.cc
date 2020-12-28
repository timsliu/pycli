/*
 * model.cc
 * backend for running the python climate modeling DSL 
 *
 */

#include "model.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <omp.h>

using namespace std;

inline double radForceTemp(double Ein, double albedo, double co2Level) {
    double radForc = CO2_HEATING * co2Level + H2O_POWER;  /* radiative forcing from ghg */
    double rhs = (((1 - albedo) * Ein) + radForc) /SIGMA;
    return pow(rhs, 0.25);
}

inline double singleLayerTemp(double Ein, double albedo, double co2Level) {
    double ECo2 = CO2_CONST * log(co2Level/CO2_DENOM);
    double term1 = (1-albedo) * Ein + ECo2/2;
    double term2 = 1/SIGMA/(1-F/2);
    return pow(term1 * term2, 0.25);
}

Model::Model(size_t steps, Planet planetStart, vector<map<string, double>> atmos, bool verbose, string outputDir): 
    _steps(steps), 
    _currentPlanet(planetStart),
    _allAtmos(atmos),
    _verbose(verbose),
    _outputDir(outputDir){

    cout << "Starting new model!" << endl;
    cout << "latCells: " << _currentPlanet.getLatCells() << " ";
    cout << "longCells: " << _currentPlanet.getLongCells() << endl;
}

void Model::simClimate() {

    if (_verbose) {
        cout << "Starting climate sim" << endl;
    }
    
    auto start = chrono::system_clock::now();
    for (size_t i = 0; i < _steps; i++ ) {
        // set the atmosphere of the planet and calculate temperatures
        _currentPlanet.setAtmosphere(_allAtmos[i]);
        calcTemps();

        // add copy of current planet to the list of computed planets
        Planet lastPlanet = Planet(_currentPlanet);
        _computedPlanets.push_back(lastPlanet);
        _currentStep++;
    }
    auto end = chrono::system_clock::now();
    
    chrono::duration<double> diff = end - start;
    
    if (_verbose) {
        cout << "Model completed! Computed " << _steps << " steps ";
        cout << _currentPlanet.getLatCells() * _currentPlanet.getLongCells() << " cells ";
        cout << "in " << diff.count() << " s" << endl;
    }
    // write out results to a file
    outputResults();
}

void Model::outputResults() {

    if (_verbose) {
        cout << "Outputting results..." << endl;
    }

    // print all of the planets
    for (size_t i = 0; i < _computedPlanets.size(); i++) {
        
        string id;
        if (i == _computedPlanets.size() - 1) {
            id = "f"; 
        }
        else {
            id = to_string(i);
        }

        cout << _outputDir << endl;
        ofstream tempFile(_outputDir + "/temp_" + id + ".txt");
        _computedPlanets[i].printPlanet(i, tempFile);
        tempFile.close();
    }
}

/*
 * Serial model methods
 *
 */

SerialModel::SerialModel(size_t steps, Planet planetStart, vector<map<string, double>> atmos, bool verbose, string outputDir): 
    Model(steps, planetStart, atmos, verbose, outputDir) {
    cout << "Creating Serial Model" << endl;
}


// calculate fill in the temperatures of the planet
void SerialModel::calcTemps() {

    vector<vector<double>>& temps = _currentPlanet.getTemperature();
    vector<vector<SurfaceType>>& surface = _currentPlanet.getSurface();
    double co2Level = _currentPlanet.getAtmosphere()["co2"];

    vector<double> EinArray = _currentPlanet.getRadIn();
    
    for (size_t i = 0; i < _currentPlanet.getLatCells(); i++ ) {
        double Ein = EinArray[i];
        for (size_t j = 0; j < _currentPlanet.getLongCells(); j++) {
            double albedo = albedoMap[surface[i][j]];
            temps[i][j] = singleLayerTemp(Ein, albedo, co2Level);
        }
    }

    // kernel for convolution - update to be dynamic
    vector<double> kernel = makeLinearKernel<double>(_currentPlanet.getLongCells(), _currentPlanet.getLatCells(), 0.1);
    serialConvolve<double>(temps, kernel);

}


/*
 * Parallel model methods
 *
 */


AccelModel::AccelModel(size_t steps, Planet planetStart, vector<map<string, double>> atmos, bool verbose, string outputDir): 
    Model(steps, planetStart, atmos, verbose, outputDir) {
    cout << "Creating Accel Model" << endl;
}


// calculate fill in the temperatures of the planet
void AccelModel::calcTemps() {

    vector<vector<double>>& temps = _currentPlanet.getTemperature();
    vector<vector<SurfaceType>>& surface = _currentPlanet.getSurface();
    double co2Level = _currentPlanet.getAtmosphere()["co2"];

    vector<double> EinArray = _currentPlanet.getRadIn();

    size_t latCells = _currentPlanet.getLatCells();
    size_t longCells = _currentPlanet.getLongCells();
 
    #pragma omp parallel for 
    for (size_t i = 0; i < latCells; i++ ) {
        double Ein = EinArray[i];
        for (size_t j = 0; j < longCells; j++) {
            double albedo = albedoMap[surface[i][j]];
            temps[i][j] = singleLayerTemp(Ein, albedo, co2Level);
        }
    }
    // TODO perform fast convolution
}


