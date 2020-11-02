
class Surface:
    def __init__(self, num_lat_gridlines, num_lon_gridlines):
        self.surface = [[0]*num_lat_gridlines]*num_lon_gridlines
        

    def set_grid_cell_type(self, lat, lon, surface_type):
        self.surface[lat][lon] = surface_type
