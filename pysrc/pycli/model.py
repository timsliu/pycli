from pycli.surface import Surface
from pycli.atmosphere import Atmosphere
import random


class Model:
    '''The model class defines the starting surface of the climate
    being simulated and the atmosphere at each model step'''
    def __init__(self, preset_surface = None,
                 num_lat_gridlines = 100, num_lon_gridlines = 100, 
                 init_atmos = {"CO2": 0.00028}):

        self.surface = None                  # model surface
        self.atmosphere = None               # model atmosphere
        self.current_step = 0                # model timestep
        self.preset_surface = None           # name of preset surface (if used)

        # use named preset surface
        if preset_surface is not None:
            self.preset_surface = preset_surface
            # set a blank surface and atmosphere - these will be filled later 
            self.surface = Surface(0, 0)
            self.atmosphere = Atmosphere(init_atmos)
        
        # used passed/default values
        else:
            if num_lat_gridlines is None or num_lon_gridlines is None:
                raise ValueError("Need to specify starting configuration")
            
            # fill in surface and atmosphere
            self.surface = Surface(num_lat_gridlines, num_lon_gridlines)
            self.surface.gen_random_surface()
            self.atmosphere = Atmosphere(init_atmos)

    def set_atmosphere(self, gas, value):
        '''set the concentration of the gas for the current timestep'''
        # update the atmosphere for the current timestep
        self.atmosphere.update_atmosphere(gas, value, self.current_step)

    def get_atmosphere(self, element, step = None):
        '''return the atmosphere - not implemented''' 
        # TODO

    def model_step(self):
        '''increment counter tracking the step index'''
        self.current_step += 1
    
    def get_current_step(self):
        '''return current model step (0 indexed)'''
        return self.current_step

    def write_config(self):
        '''write the configuration files surface.txt and atmosphere.txt out''' 
        # write the defined surface or use a preset surface 
        if self.preset_surface == "":
            self.surface.write_to_file()
        else:
            self.surface.copy_preset(self.preset_surface)
        
        # write the atmosphere file
        self.atmosphere.write_to_file(self.current_step)
        
