# Release Notes

## Description
This page describes the different changes and updates in each version of PyCli.
The naming scheme for each release is `x.y.z` where:

* `x` is incremented on major rewrites
* `y` is incremented for signficant new features
* `z` is incremented for minor feature changes, bug fixes, or modifications

## Releases

#### v0.1.0 - 01/18/21

First public release of PyCli. 

* Users can use either preset surfaces or generate a random surface with a specified size. 
* Temperatures are calculated using a 
one layer atmosphere model, and users can only modify the concentration of CO2
to influence the climate. 
* The surface of the planet does not change between
model steps, and the planet is not tilted. 
* A map of the final temperatures and
a plot of the average temperature at each step is saved.
* Makefile updated to detect OS; compatible with macOS and Ubuntu
