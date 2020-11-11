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

Model::Model(size_t steps, Planet planetStart, vector<map<string, float>> atmos, bool verbose, string outputDir): 
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
        //Planet lastPlanet = Planet(_currentPlanet);
        //_computedPlanets.push_back(lastPlanet);
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
        cout << "Outputting results" << endl;
    }


    // print all of the planets
    for (size_t i = 0; i < _computedPlanets.size(); i++) {
        ofstream tempFile(_outputDir + "/temp_" + to_string(i) + ".txt");
        _computedPlanets[i].printPlanet(i, tempFile);
        tempFile.close();
    }

    if (_verbose) {
        cout << "Creating long/lat files" << endl;
    }
  
    cout << _outputDir << endl;
    ofstream latFile(_outputDir + "/lat.txt");
    ofstream longFile(_outputDir + "/long.txt");

    int latCells = _currentPlanet.getLatCells();
    int longCells = _currentPlanet.getLongCells();
    
    for (int i = 0; i < latCells; i++) {
        for (int j = 0; j < longCells; j++) {
            latFile << setprecision(4) <<  i * LAT_RANGE/(latCells+ 1) - LAT_RANGE/2 << " ";
            longFile << setprecision(4) << j * LONG_RANGE/(longCells + 1) - LONG_RANGE/2 << " ";
        }
        latFile << endl;
        longFile << endl;
    }
    longFile.close();
    latFile.close();
}

/*
 * Serial model computation steps
 *
 */

SerialModel::SerialModel(size_t steps, Planet planetStart, vector<map<string, float>> atmos, bool verbose, string outputDir): 
    Model(steps, planetStart, atmos, verbose, outputDir) {
    cout << "Creating Serial Model" << endl;
}


// calculate fill in the temperatures of the planet
void SerialModel::calcTemps() {

    vector<vector<float>>& temps = _currentPlanet.getTemperature();
    vector<vector<SurfaceType>>& surface = _currentPlanet.getSurface();
    float co2Level = _currentPlanet.getAtmosphere()["co2"];

    vector<float> EinArray = _currentPlanet.getRadIn();
    
    for (size_t i = 0; i < _currentPlanet.getLatCells(); i++ ) {
        float Ein = EinArray[i];
        for (size_t j = 0; j < _currentPlanet.getLongCells(); j++) {
            float albedo = albedoMap[surface[i][j]];
            float radForc = CO2_HEATING * co2Level + H2O_POWER;  /* radiative forcing from ghg */
            float rhs = (((1 - albedo) * Ein) + radForc) /SIGMA;
            temps[i][j] = pow(rhs, 0.25);
        }
    }
}


/*
 * Parallel model computation steps
 *
 */


AccelModel::AccelModel(size_t steps, Planet planetStart, vector<map<string, float>> atmos, bool verbose, string outputDir): 
    Model(steps, planetStart, atmos, verbose, outputDir) {
    cout << "Creating Accel Model" << endl;
}


// calculate fill in the temperatures of the planet
void AccelModel::calcTemps() {

    vector<vector<float>>& temps = _currentPlanet.getTemperature();
    vector<vector<SurfaceType>>& surface = _currentPlanet.getSurface();
    float co2Level = _currentPlanet.getAtmosphere()["co2"];

    vector<float> EinArray = _currentPlanet.getRadIn();
    float radForc = CO2_HEATING * co2Level + H2O_POWER;

    size_t latCells = _currentPlanet.getLatCells();
    size_t longCells = _currentPlanet.getLongCells();
 
    #pragma omp parallel for 
    for (size_t i = 0; i < latCells; i++ ) {
        float Ein = EinArray[i];
        for (size_t j = 0; j < longCells; j++) {
            float albedo = albedoMap[surface[i][j]];
            /* greenhouse gas effect */
            float rhs = (((1 - albedo) * Ein) + radForc) /SIGMA;
            temps[i][j] = pow(rhs, 0.25);
        }
    }
}


