import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import os
import sys
import json


PYCLI_ROOT = os.path.join(os.getcwd(), "..")
LAT_MAX = 90
LON_MAX = 180


def load_prefs(prefs_file):
    with open(prefs_file) as json_file:
        return json.load(json_file)


def plot_map(temps, color_map, model_name, coastlines):
    '''plot the temperature for each grid point using matplotlib'''
    
    print("Generating temperature map at models/{}/{}.png".format(model_name, model_name))
    minimum = np.amin(temps)
    maximum = np.amax(temps)
    
    plt.imshow(temps, cmap=color_map)
    plt.title('{} Global Temperature'.format(model_name))
    plt.colorbar(label='temperature anomaly (°F)')

    for line in coastlines: 
        x1 = line[0][0]
        x2 = line[0][1]
        y1 = line[1][0]
        y2 = line[1][1]
        plt.plot([x1, x2], [y1, y2], color='black', linewidth=1)
    plt.clim(minimum, maximum)
    plt.savefig(os.path.join(PYCLI_ROOT, "models/{}/{}.png".format(model_name, model_name)))
        
    return

def get_coast(surface_array):
    '''returns a list of lines representing the boundary between water and land
    inputs: surface_array - numpy 2D array encoded with surface type for each square
    output: coast - set of lines; lines represented as ((x1, x2), (y1, y2))'''

    lines = set()   # set for holding all lines

    dims = surface_array.shape
    yDim = dims[0]
    xDim = dims[1]

    # sides corresponding to four adjacnet cells
    sides = np.array([[0, 1], [1, 0], [-1, 0], [0, -1]])

    # iterate through all cells
    for i in range(yDim):
        for j in range(xDim):
            # skip ocean tiles - only look for land touching ocean
            if surface_array[i, j] == 0:
                continue
            center = np.array([i, j])

            # iterate through 4 surrounding tiles
            for side in sides:
                candidate = center + side     # coordinates of candidate tile

                # point is off the edge - skip
                if candidate[0] < 0 or candidate[0] >= yDim - 1\
                    or candidate[1] < 0 or candidate[1] >= xDim - 1:
                    continue
                
                # check if adjacent tile is ocean
                if surface_array[candidate[0], candidate[1]] == 0:
                    x1, x2, y1, y2 = None, None, None, None 
                    # on the same row 
                    if candidate[0] == center[0]:
                        y1 = center[0]
                        y2 = center[0] + 1
                        x1 = (center[1] + candidate[1])/2
                        x2 = x1
                    # on the same col 
                    else:
                        y1 = (center[0] + candidate[0])/2
                        y2 = y1
                        x1 = center[1]
                        x2 = center[1] + 1

                    lines.add(((x1, x2), (y1, y2)))
    print("Number of lines: ", len(lines))

    return lines


if __name__ == "__main__":
   
    model_name = sys.argv[1]
    prefs_file = os.path.join(PYCLI_ROOT, "models/{}/prefs.json".format(model_name))
    temp_file = os.path.join(PYCLI_ROOT, "models/{}/out/temp_f.txt".format(model_name))
    surface_file = os.path.join(PYCLI_ROOT, "models/{}/surface.txt".format(model_name))
    temps_array = np.loadtxt(temp_file)
    surface_array = np.loadtxt(surface_file)
    coastlines = get_coast(surface_array)

    prefs = load_prefs(prefs_file)

    plot_map(temps_array, prefs["colors"], model_name, coastlines) 

