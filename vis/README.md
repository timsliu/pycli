# PyCli Visualization Suite

The PyCli visualization suite has several functions for generating plots.
Currently, two plots are made by default: a plot of the final temperatures 
across the planet and the average temperatures at each timestep.

The visualization suite uses the final temperatures to plot a colored map. The
coastlines are drawn in by detecting boundaries between land squares and
ocean squares. Each line is then separately plotted on the temperature map.
Since each coastline edge is plotted by a separate call to `plt.plot`, the
coastline plotter is prohibitively slow for large maps with many coasts.


##
Copyright 20201 Timothy Liu
