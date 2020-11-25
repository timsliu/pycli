import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.basemap import Basemap
import os
import sys
import json
"""
## Map Projections

The first thing to decide when using maps is what projection to use.
You're probably familiar with the fact that it is impossible to project a spherical map, such as that of the Earth, onto a flat surface without somehow distorting it or breaking its continuity.
These projections have been developed over the course of human history, and there are a lot of choices!
Depending on the intended use of the map projection, there are certain map features (e.g., direction, area, distance, shape, or other considerations) that are useful to maintain.

The Basemap package implements several dozen such projections, all referenced by a short format code.
Here we'll briefly demonstrate some of the more common ones.

We'll start by defining a convenience routine to draw our world map along with the longitude and latitude lines:
"""

from itertools import chain

def draw_map(m, scale=0.2):
    # draw a shaded-relief image
    m.shadedrelief(scale=scale)
    
    # lats and longs are returned as a dictionary
    lats = m.drawparallels(np.linspace(-90, 90, 13))
    lons = m.drawmeridians(np.linspace(-180, 180, 13))

    # keys contain the plt.Line2D instances
    lat_lines = chain(*(tup[1][0] for tup in lats.items()))
    lon_lines = chain(*(tup[1][0] for tup in lons.items()))
    all_lines = chain(lat_lines, lon_lines)
    
    # cycle through these lines and set the desired style
    for line in all_lines:
        line.set(linestyle='-', alpha=0.3, color='w')

"""### Cylindrical projections

The simplest of map projections are cylindrical projections, in which lines of constant latitude and longitude are mapped to horizontal and vertical lines, respectively.
This type of mapping represents equatorial regions quite well, but results in extreme distortions near the poles.
The spacing of latitude lines varies between different cylindrical projections, leading to different conservation properties, and different distortion near the poles.
In the following figure we show an example of the *equidistant cylindrical projection*, which chooses a latitude scaling that preserves distances along meridians.
Other cylindrical projections are the Mercator (``projection='merc'``) and the cylindrical equal area (``projection='cea'``) projections.
"""


"""
Temperature overlay
"""
"""
from netCDF4 import Dataset
data = Dataset('gistemp250.nc')
"""
"""The file contains many global temperature readings on a variety of dates; we need to select the index of the date we're interested in—in this case, January 15, 2014:"""
"""
from netCDF4 import date2index
from datetime import datetime
timeindex = date2index(datetime(2014, 1, 15),
                       data.variables['time'])
"""
"""Now we can load the latitude and longitude data, as well as the temperature anomaly for this index:"""
"""
lat = data.variables['lat'][:]
lon = data.variables['lon'][:]
lon, lat = np.meshgrid(lon, lat)
temp_anomaly = data.variables['tempanomaly'][timeindex]
"""
"""Finally, we'll use the ``pcolormesh()`` method to draw a color mesh of the data.
We'll look at North America, and use a shaded relief map in the background.
Note that for this data we specifically chose a divergent colormap, which has a neutral color at zero and two contrasting colors at negative and positive values.
We'll also lightly draw the coastlines over the colors for reference:
"""


PYCLI_ROOT = os.path.join(os.getcwd(), "..")
LAT_MAX = 90
LON_MAX = 180


def gen_lat_lon(res_x, res_y):
   
    # generate latitude grid
    lat = np.ones((1, int(2 * LON_MAX * res_x)))
    lat = lat * LAT_MAX
    
    for i in range(int(2 * LAT_MAX * res_y - 1)):
        lat_next = lat[-1] - 1/res_y
        lat = np.vstack((lat, lat_next))
    
    # gnerate longitude grid
    lon = np.arange(int(2 * LON_MAX * res_x))
    lon = lon / res_x - LON_MAX
    next_lon = lon
    
    for i in range(int(2 * LAT_MAX * res_y-1)):
        lon = np.vstack((lon, next_lon))
    
    return lat, lon


def plot_temp(lat, lon, res_y, res_x, temps_array, model_name, c_map):
    
    minimum = np.amin(temps_array)
    maximum = np.amax(temps_array)
    
    fig = plt.figure(figsize=(20, 16))
    m = Basemap(projection='cyl', resolution='c',
                llcrnrlat=-LAT_MAX, urcrnrlat=LAT_MAX,
                llcrnrlon=-LON_MAX, urcrnrlon=LON_MAX, )
    m.shadedrelief(scale=0.5)
    m.pcolormesh(lon, lat, temps_array,
                 latlon=True, cmap=c_map)
    plt.clim(minimum, maximum)
    m.drawcoastlines(color='black')
    
    plt.title('{} Global Temperature'.format(model_name))
    plt.colorbar(label='temperature anomaly (°F)');
    print("Generating temperature map at models/{}/{}.png".format(model_name, model_name))
    plt.savefig(os.path.join(PYCLI_ROOT, "models/{}/{}.png".format(model_name, model_name)))

def load_prefs(prefs_file):
    with open(prefs_file) as json_file:
        return json.load(json_file)
        

if __name__ == "__main__":
   
    model_name = sys.argv[1]
    PYCLI_ROOT = sys.argv[2]
    prefs_file = os.path.join(PYCLI_ROOT, "models/{}/vis_prefs.json".format(model_name))
    temp_file = os.path.join(PYCLI_ROOT, "src/out/{}/temp_f.txt".format(model_name))
    temps_array = np.loadtxt(temp_file)

    prefs = load_prefs(prefs_file)

    lat_points, lon_points = temps_array.shape
    res_y = lat_points/(2 * LAT_MAX)
    res_x = lon_points/(2 * LON_MAX)

    lat, lon = gen_lat_lon(res_x, res_y)
    plot_temp(lat, lon, res_y, res_x, temps_array, model_name, prefs["color_map"])

