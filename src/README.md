# src

This folder contains the source code for the PyCli backend climate model. The
backend climate model is responsible for parsing the `atmosphere.txt` and 
`surface.txt` files and calculating the temperatures at points across the 
planet's surface.

* `constant.h` - header file with physical constants
* `conv.h` - template functions for convolution
* `model.cc` - implementations of climate models used to calculate temperature
* `parser.cc` - main loop responsible for parsing input files and calling model
class
* `planet.cc` - class representing a planet, including surface and atmosphere
* `test` - test bench for unit testing
* `utils.cc` - additional utilities used across multiple files


##
Copyright 20201 Timothy Liu
