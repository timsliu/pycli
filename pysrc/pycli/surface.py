import sys
import os

class Surface:
    def __init__(self, num_lat_gridlines, num_lon_gridlines):
        self.num_lat_grid = num_lat_gridlines
        self.num_lon_grid = num_lon_gridlines

        self.surface = [ [0] * num_lon_gridlines for _ in range(num_lat_gridlines)]
        
    def set_grid_cell_type(self, lat, lon, surface_type):
        self.surface[lat][lon] = surface_type

    def write_to_file(self):
        model_name = sys.argv[0][0:sys.argv[0].find(".")]
        with open(os.path.join(model_name, "surface.txt"), "w") as write_file:
            for i in range(len(self.surface)):
                for j in range(len(self.surface[i])):
                    write_file.write(str(self.surface[i][j]) + " ")
                write_file.write("\n")
