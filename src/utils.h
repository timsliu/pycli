/* helper functions and utilities shared across all files */

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <map>


void printTemperature(std::vector<std::vector<float>>& temp);

void printAtmosphere(std::map<std::string, float>& atmo);

void printAtmosList(std::vector<std::map<std::string, float>>& atmoList);

#endif /* UTILS_H */
