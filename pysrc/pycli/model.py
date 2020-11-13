from pycli.surface import Surface
from pycli.atmosphere import Atmosphere
import random

class Model:
    def __init__(self, default = True, preset_surface = "",
                 num_lat_gridlines = None, num_lon_gridlines = None, 
                 init_o2 = None, init_co2 = None, init_n2 = None):

        self.current_time = 0
        self.preset_surface = ""

        if default:
            self.surface = Surface(100, 100)
            self.atmosphere = Atmosphere(0, 0, 0)
        elif preset_surface != "":
            self.preset_surface = preset_surface
            self.surface = Surface(0, 0)
            self.atmosphere = Atmosphere(0, 0, 0)
        else:
            if num_lat_gridlines is None or num_lon_gridlines is None or init_o2 is None or init_co2 is None or init_n2 is None:
                raise ValueError("Need to specify starting configuration")
            self.surface = Surface(num_lat_gridlines, num_lon_gridlines)
            self.atmosphere = Atmosphere(init_o2, init_co2, init_n2)

    def gen_random_surface(self):
        for i in range(self.surface.num_lat_grid):
            for j in range(self.surface.num_lon_grid):
                if i <= self.surface.num_lat_grid * 0.1 or i >= self.surface.num_lat_grid * 0.9:
                    self.surface.set_grid_cell_type(i, j, 2)
                else:
                    self.surface.set_grid_cell_type(i, j, random.randint(0,2))

    def set_atmosphere(self, element, value, time = None):
        if time == None:
            time = self.current_time

        if element == "CO2":
            self.atmosphere.set_co2(value, time)
        elif element == "O2":
            self.atmosphere.set_o2(value, time)
        elif element == "N2":
            self.atmosphere.set_n2(value, time)
        else:
            raise ValueError("Element not supported")

    def get_atmosphere(self, element, time = None):
        if time == None:
            time = self.current_time

        if element == "CO2":
            return self.atmosphere.get_co2(time)
        elif element == "O2":
            return self.atmosphere.get_o2(time)
        elif element == "N2":
            return self.atmosphere.get_n2(time)
        else:
            raise ValueError("Element not supported")

    def model_step(self):
        self.atmosphere.update_atmosphere(self.current_time)
        self.current_time = self.current_time + 1
    
    def write_surface(self):
        if self.preset_surface == "":
            self.surface.write_to_file()
        else:
            self.surface.copy_preset(self.preset_surface)
        
    def write_atmosphere(self):
        self.atmosphere.write_to_file()
