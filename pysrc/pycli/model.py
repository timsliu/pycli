from pycli.surface import Surface
from pycli.atmosphere import Atmosphere


class Model:
    def __init__(self, default = True, num_lat_gridlines = None, num_lon_gridlines = None, init_o2 = None, init_co2 = None, init_n2 = None):

        self.current_time = 0

        if default:
            self.surface = Surface(100, 100)
            self.atmosphere = Atmosphere(0, 0, 0)
        else:
            if num_lat_gridlines is None or num_lon_gridlines is None or init_o2 is None or init_co2 is None or init_n2 is None:
                raise ValueError("Need to specify starting configuration")
            self.surface = Surface(num_lat_gridlines, num_lon_gridlines)
            self.atmosphere = Atmosphere(init_o2, init_co2, init_n2)

    def set_init_atmosphere(self, element, value):
        if element == "CO2":
            self.atmosphere.set_co2(value, 0)
        elif element == "O2":
            self.atmosphere.set_o2(value, 0)
        elif element == "N2":
            self.atmosphere.set_n2(value, 0)
        else:
            raise ValueError("Element not supported")

    def write_surface(self, filename):
        self.surface.write_to_file(filename)
        
    def write_atmosphere(self, filename):
        raise NotImplementedError