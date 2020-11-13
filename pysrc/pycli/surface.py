import sys
import os
import shutil

# this assumes script is being run from run-cli.py in models directory
PYCLI_ROOT = os.path.join(os.getcwd(), "..")


class Surface:
    def __init__(self, num_lat_gridlines, num_lon_gridlines):
        self.num_lat_grid = num_lat_gridlines
        self.num_lon_grid = num_lon_gridlines

        self.surface = [ [0] * num_lon_gridlines for _ in range(num_lat_gridlines)]
        
    def set_grid_cell_type(self, lat, lon, surface_type):
        self.surface[lat][lon] = surface_type

    def write_to_file(self):
        # get name of the model
        model_name = sys.argv[0][0:sys.argv[0].find(".")]
        with open(os.path.join(model_name, "surface.txt"), "w") as write_file:
            for i in range(len(self.surface)):
                for j in range(len(self.surface[i])):
                    write_file.write(str(self.surface[i][j]))
                    # only write a space after not the last element
                    if j != len(self.surface[i]) - 1:
                        write_file.write(" ")
                write_file.write("\n")

    def copy_preset(self, preset):
        '''copy a pre generated default surface to the appropriate directory'''
        model_name = sys.argv[0][0:sys.argv[0].find(".")]
        src = os.path.join(PYCLI_ROOT, "pysrc/pycli/preset_surfaces/{}.txt".format(preset))
        dst = os.path.join(PYCLI_ROOT, "models/{}/surface.txt".format(model_name))
        shutil.copyfile(src, dst)
