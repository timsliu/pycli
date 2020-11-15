from pycli.model import Model
import json
import os
import sys

def new_model(name):
    if name == "default":
        return Model(default = True)
    elif name == "small":
        return Model(default = False, num_lat_gridlines = 16, num_lon_gridlines = 4, 
                     init_o2 = 0, init_co2 = 0, init_n2 = 0)
    elif name == "large":
        return Model(default = False, num_lat_gridlines = 1000, 
                     num_lon_gridlines = 1000, init_o2 = 10, init_co2 = 10, init_n2 = 10)
    elif name == "earth_big":
        return Model(default = False, preset_surface = "earth_big")
    else:
        raise NotImplementedError

color_map_pref = "RdBu_r"

def set_color_map(color_map):
    colors = {'Greys', 'Purples', 'Blues', 'Greens', 'Oranges', 'Reds',
            'YlOrBr', 'YlOrRd', 'OrRd', 'PuRd', 'RdPu', 'BuPu',
            'GnBu', 'PuBu', 'YlGnBu', 'PuBuGn', 'BuGn', 'YlGn',
            'binary', 'gist_yarg', 'gist_gray', 'gray', 'bone', 'pink',
            'spring', 'summer', 'autumn', 'winter', 'cool', 'Wistia',
            'hot', 'afmhot', 'gist_heat', 'copper',
            'PiYG', 'PRGn', 'BrBG', 'PuOr', 'RdGy', 'RdBu',
            'RdYlBu', 'RdYlGn', 'Spectral', 'coolwarm', 'bwr', 'seismic',
            'twilight', 'twilight_shifted', 'hsv',
            'Pastel1', 'Pastel2', 'Paired', 'Accent',
            'Dark2', 'Set1', 'Set2', 'Set3',
            'tab10', 'tab20', 'tab20b', 'tab20c',
            'flag', 'prism', 'ocean', 'gist_earth', 'terrain', 'gist_stern',
            'gnuplot', 'gnuplot2', 'CMRmap', 'cubehelix', 'brg',
            'gist_rainbow', 'rainbow', 'jet', 'turbo', 'nipy_spectral',
            'gist_ncar'}

    colors_r = {c + "_r" for c in colors}

    if color_map not in colors and color_map not in colors_r:
        raise ValueError("Color map not supported in matplotlib")

    
    color_map_pref = color_map

def write_preferences():
    prefs = {}
    prefs["color_map"] = color_map_pref

    model_name = sys.argv[0][0:sys.argv[0].find(".")]
    with open(os.path.join(model_name, "vis_prefs.json"), "w") as outfile:
        json.dump(prefs, outfile)