# PyCli front end
# 
# This file contains functions for creating an instance of the Model and
# Preference class which specify the planet being simulated and simulation
# settings, respectively.


from pycli.model import Model
from pycli.prefs import Preferences 
import json
import os
import sys

# list of names for models
ALLOWED_NAMES = ["default", "small", "large", "earth_big", "earth"] 

def new_model(name):
    '''this function should be called at the top of a new PyCli model config file. Function
    creates a model instance and a preference instance based on the passed name.
    The passed name MUST be in the list allowed_names

    inputs: name - name of new model; must be in ALLOWED_NAMES list
    output: model - new instance of model class
            prefs - instance of preferences class '''
 
    # list for holding the newly instantiated model
    model = []
   
    # default setting
    if name == "default":
        model.append(Model(default = True))
    # small random world 
    elif name == "small":
        model.append(Model(default = False, num_lat_gridlines = 16, num_lon_gridlines = 4, 
                     init_o2 = 0, init_co2 = 0, init_n2 = 0))
    # large random world 
    elif name == "large":
        model.append(Model(default = False, num_lat_gridlines = 1000, 
                     num_lon_gridlines = 1000, init_o2 = 10, init_co2 = 10, init_n2 = 10))
    # large earth - predefined map 
    elif name == "earth_big":
        model.append(Model(default = False, preset_surface = "earth_big"))
    
    # small earth - predefined map 
    elif name == "earth":
        model.append(Model(default = False, preset_surface = "earth"))
    else:
        print("Model name not in allowed list: ", ALLOWED_NAMES)
        raise NotImplementedError

    # return the model and the model and a preference instance
    return model[0], Preferences()

