/*
 * model.cc
 * backend for running the python climate modeling DSL 
 *
 */



Model::Model(steps, Planet planetStart) {

}


void Model::simClimate() {

    for (int i = 0; i < steps; i++ ) {
        calcTemps();

        // add current planet to the list of computed planets
        computedPlanets.push_back(currentPlanet);

        // make a copy of last planet as start for next iteration
    }

    // write out results to a file
    outputResults();

}


// calculate fill in the temperatures of the planet
void Model::calcTemps() {

}
