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
ALLOWED_NAMES = ["small", "large", "earth_big", "earth"] 

def new_model(name = None, num_lat_gridlines = None, num_lon_gridlines = None, init_atmos = None):
    '''this function should be called at the top of a new PyCli model config file. Function
    creates a model instance and a preference instance based on the passed name.
    The passed name MUST be in the list allowed_names

    inputs: name - name of new model; must be in ALLOWED_NAMES list
    output: model - new instance of model class
            prefs - instance of preferences class '''
 
    # list for holding the newly instantiated model
    model = None
   
    # default setting
    if name is None:
        model = Model()
    
    # small random world 
    elif name == "small":
        model = Model(num_lat_gridlines = 16, num_lon_gridlines = 4)
    
    # large random world 
    elif name == "large":
        model = Model(num_lat_gridlines = 1000, num_lon_gridlines = 1000)
    
    # small earth - predefined map 
    elif name == "earth":
        model = Model(preset_surface = "earth")
    
    # large earth - predefined map 
    elif name == "earth_big":
        model = Model(preset_surface = "earth_big")

    # custom user defined map and atmosphere
    elif name == "custom":
        
        # not enough arguments are specified
        if num_lat_gridlines is None or num_lon_gridlines is None:
            raise ValueError("Dimenstions must be specified to use custom model init")
       
        # sufficient args
        else:
            # no specified atmosphere - use model default 
            if init_atmos is None:
                model = Model(num_lat_gridlines=num_lat_gridlines,
                              num_lon_gridlines=num_lon_gridlines)
            # atmosphere specified - pass it 
            else:
                model = Model(num_lat_gridlines=num_lat_gridlines,
                              num_lon_gridlines=num_lon_gridlines, init_atmos=init_atmos)
    else:
        raise ValueError("Model name not in allowed list: {}".format(str(ALLOWED_NAMES)))

    # return the model and the model and a preference instance
    return model, Preferences()

