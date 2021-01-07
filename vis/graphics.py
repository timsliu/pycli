# vis.py
# 
# functions for generating visualizations of temperature map
#
# plot_map - create heat map of final temperature
# get_coast - helper function for plotting lines between surface and ocean


import numpy as np
import matplotlib
matplotlib.use('Agg')       # needed to run in headless mode (no display) 
import matplotlib.pyplot as plt
import os
import sys
import json
import argparse

from mpl_toolkits.axes_grid1.inset_locator import inset_axes


PYCLI_ROOT = os.path.join(os.getcwd(), "..")
LAT_MAX = 90
LON_MAX = 180


def plot_map(temps, color_map, model_name, coastlines, verbose = False):
    '''plot the temperature for each grid point using matplotlib'''
 
    if verbose:
        print("Starting to plot heat map...")

    # get temperature range
    minimum = np.amin(temps)
    maximum = np.amax(temps)
    
    fig, ax = plt.subplots(1, 1)
    plt.axis('off')                     # disable axis
    plt.imshow(temps, cmap=color_map)   # plot heatmap
    plt.title('{} Global Temperature'.format(model_name.capitalize())) # add title

    # plot the coastline

    for i, line in enumerate(coastlines):
        # unpack coordinates of each line
        x1 = line[0][0]
        x2 = line[0][1]
        y1 = line[1][0]
        y2 = line[1][1]
        # plot the lines
        plt.plot([x1, x2], [y1, y2], color='black', linewidth=1)
        if verbose and i % int(len(coastlines)/10) == 0:
            print("Plotted {:.1f}% of coastline".format(100 * i/len(coastlines)))

 
    # position colorbar label on the right side and size it
    axins = inset_axes(ax, 
                       height="100%", 
                       width="5%",
                       loc='lower left',
                       bbox_to_anchor=(1.05, 0., 1, 1),
                       bbox_transform=ax.transAxes,
                       borderpad=0)
    
    # add colorbar label 
    plt.colorbar(label='Average temperature (°F)', cax=axins)

    plt.clim(minimum, maximum)
    
    if verbose:
        print("Saving temperature map at pycli/models/{}/{}.png ...".format(model_name, model_name))
    # save the figure at 800 dpi resolution and ensure all features are saved
    plt.savefig(os.path.join(PYCLI_ROOT, "models/{}/{}.png".format(model_name, model_name)), 
                dpi=800,
                bbox_inches="tight")
    
    return

def get_coast(surface_array, verbose=False):
    '''returns a list of lines representing the boundary between water and land
    inputs: surface_array - numpy 2D array encoded with surface type for each square
    output: coast - set of lines; lines represented as ((x1, x2), (y1, y2))'''

    if verbose:
        print("Calculating location of coastlines...")
    lines = set()   # set for holding all lines

    dims = surface_array.shape
    yDim = dims[0]      # get shape and dimensions of the array
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
                if candidate[0] < 0 or candidate[0] > yDim - 1\
                    or candidate[1] < 0 or candidate[1] > xDim - 1:
                    continue
                
                # check if adjacent tile is ocean
                if surface_array[candidate[0], candidate[1]] == 0:
                    x1, x2, y1, y2 = None, None, None, None 
                    # on the same row 
                    if candidate[0] == center[0]:
                        y1 = center[0] - 0.5
                        y2 = center[0] + 0.5
                        x1 = (center[1] + candidate[1])/2
                        x2 = x1
                    # on the same col 
                    else:
                        y1 = (center[0] + candidate[0])/2
                        y2 = y1
                        x1 = center[1] - 0.5
                        x2 = center[1] + 0.5

                    lines.add(((x1, x2), (y1, y2)))

    return lines


if __name__ == "__main__":

    
    print("Starting PyCli visualization suite...")
   
    # create parser
    parser = argparse.ArgumentParser(description="Generate visualizations for PyCli")
    parser.add_argument("model_name", type=str, help='name of the model')
    parser.add_argument("-v", type=str, default="silent", help="run in verbose mode")

    # parse arguments
    args = parser.parse_args()
    model_name = args.model_name
    verbose = args.v == "verbose"

    # build paths to different files and parse them
    if verbose:
        print("Parsing temp, surface, and preference files...")
    
    prefs_file = os.path.join(PYCLI_ROOT, "models/{}/prefs.json".format(model_name))
    temp_file = os.path.join(PYCLI_ROOT, "models/{}/out/temp_f.txt".format(model_name))
    surface_file = os.path.join(PYCLI_ROOT, "models/{}/surface.txt".format(model_name))

    # parse the temperature, surface, and preference files
    temps_array = np.loadtxt(temp_file)
    surface_array = np.loadtxt(surface_file)
   
    prefs = None
    with open(prefs_file) as json_file:
        prefs = json.load(json_file)

   
    # call helper function to get lines representing coast
    coastlines = get_coast(surface_array, verbose=verbose)
    
    # plot the temperature heatmap
    plot_map(temps_array, prefs["colors"], model_name, coastlines, verbose) 

    # plot graph of temperatures over time
    #plot_avg_temps(avg_temps, verbose)

