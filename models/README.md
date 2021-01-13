# Writing Models in PyCli

A **model** in PyCli refers to two separate topics. A PyCli model is the 
description of a climate simulation written in Python, using the
PyCli Python library (examples of which are in this directory). 
The PyCli library is a domain specific language (DSL) embedded in Python, designed 
to make it easy for users to specify a climate. Most users will only use the
PyCli model Python interface. The **backend climate model** refers to the C++ implemented 
in the `src` directory that simulates the globe's climate and calculates temperatures. 
change model. The Python model is specifies inputs to the backend climate model.

This document describes how to create a PyCli climate model in
Python. To understand how the backend climate model computes temperatures at
each point, please refer to `tex/pycli.pdf` which describes the science and
math used to calculate temperatures.

There are three main steps to building a PyCli model:
1. Initialization and preferences
2. Model loop
3. Output config files

### Initialization and preferences
The start of a PyCli model requires a call to `pycli.new_model`

```
earth, prefs = pycli.new_model("earth")
```

Allowed arguments to `new_model`:
* Empty - creates a default 100x100 randomly made planet
* "small" - randomly generated 16x4 planet
* "large" - randomly generated 1000x1000 planet
* "earth" - 90x180 planet shaped like Earth with no ice
* "earth_big" - 900x1800 planet shaped like Earth
* "custom" - custom model; requires num_lat_gridlines and num_lon_gridlines to
             be specified

This method returns two objects. The first return is a planet object. Method
calls to the planet object will be used to specify the atmosphere. The
prefs object holds the model and visualization preferences.

Preferences can be modified by passing a dictionary to the `prefs.set_pref()`
method:

```
prefs.set_pref({"temp_unit": "C", "verbose": False})
```

The `set_pref()` method can be called multiple times, or once with a single
large dictionary. The keys in the dictionary are the names of preferences
and the values are the desired setting. The list of allowed settings are listed
in `pycli/pysrc/pycli/prefs.py`. If not specified, preference values will
be set to the default.

* backend_model: C++ backend climate model to use
* verbse: print details of climate model and visualization
* atmos_type: whether the atmosphere is specified by the concentration of
gas or by annual emissions
* temp_unit: unit for temperature in output
* colors: color scale

### Modeling loop
The second part of a PyCli model is a loop where the atmosphere at each step
is specified by the loop body. The top of the loop must have a call to
`earth.model_step()` which indicates that a new timestep has begun.

Currently one function is used to specify the climate. `earth.set_atmosphere`
takes two arguments. The first is a string describing what gas is being set.
PyCli only supports CO2. The second argument is the quantity, which can either
be the annual emission (in gigatons) or the concentration (in ppm). By default
values passed are interpreted as concentration. The `atmos_type` preference
can be set so that it is interpreted as an annual emission.

The `earth.get_atmosphere()` method can also be used to get the value of a
certain gas at the last timeste.

### Output config files
A PyCli model must conclude with two method calls (order does not matter). The
methods `earth.write_config()` and `prefs.write_preferences()` write out the 
settings to configuration files read by the backend climate model.


