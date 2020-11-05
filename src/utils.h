/* helper functions and utilities shared across all files */

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <map>

#include "constant.h"

void printTemperature(std::vector<std::vector<float>>& temp);

void printSurface(std::vector<std::vector<SurfaceType>>& inputSurface);

void printAtmosphere(std::map<std::string, float>& atmo);

void printAtmosList(std::vector<std::map<std::string, float>>& atmoList);

#endif /* UTILS_H */
