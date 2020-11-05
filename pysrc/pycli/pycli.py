from pycli.model import Model

def new_model(name):
    if name == "default":
        return Model(default = True)
    elif name == "small":
        return Model(default = False, num_lat_gridlines = 16, num_lon_gridlines = 4, init_o2 = 0, init_co2 = 0, init_n2 = 0)
    else:
        raise NotImplementedError