from pycli.surface import Surface
from pycli.atmosphere import Atmosphere


class Model:
    def __init__(self, default = True):

        if default:
            self.surface = Surface(100, 100)
            self.atmosphere = Atmosphere()
        else:
            raise NotImplementedError("Only default model supported right now")


    def set_atmosphere(self, element, value):
        if element == "CO2":
            self.atmosphere.set_co2(value)
        elif element == "O2":
            self.atmosphere.set_o2(value)
        elif element == "N2":
            self.atmosphere.set_n2(value)
        else:
            raise ValueError(f"Element {element} not supported")