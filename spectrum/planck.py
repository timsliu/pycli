import numpy as np
import matplotlib.pyplot as plt

from constants import *

LU_MAX = 0.1        # lowest wavelength considered (100 nm)
LU_MIN = 40         # longest wavelength considered (40 um)

SPECIES = ["O2", "H20", "O3"]

def planck(temp, plot=False):
    '''plot planck's distribution at a given temperature. Returns two numpy
    arrays with the b (spectral radiance) and l (wavelength) values
    '''
    lu_start = LU_MIN
    lu_stop  = LU_MAX
    lu_step  = 0.1


    lu = np.arange(lu_start, lu_stop, lu_step)   # wavelength in micrometers
    l = lu/1e6                                   # wavelength in meters (MKS)
    b = 2 * h * c ** 2 / l ** 5 * 1/(np.exp(h*c/(l * Kb * temp)) - 1)

    # normalize so total adds to 1
    total_flux = sum(b) * lu_step                # approx integral of flux
    b_norm = b/total_flux
    
    if plot:
        plt.plot(lu, b_norm)
        plt.show()

    return b_norm, lu


def get_transmittance(specie, lu):
    '''returns the transmittance of a gas specie at a certain wavelength
    (in microns um). Only certain gas specie can be passed. The function
    loads in the specie file "<specie>_points.txt" and linearly interpolates
    between available transmittance values to calculate the transmittance of
    the passed value.
    inputs: specie (str) - name of gas specie
            lu (array)   - list of wavelengths to get transmittance at; 
                           must be between LU_MIN and LU_MAX'''

    if specie not in SPECIES:
        print("Specie {} not recognized".format(specie))
        return []

    with open("{}_points.txt".format(specie), "r") as f:
        trans_data_raw = f.readlines()   # get strings with "wavelength, trans"

    trans_v_wave = []                    # build list of transmittance v lambda
    for point in trans_data_raw:
        comma = point.find(",")
        wavelength = float(point[:comma])
        transmittance = float(point[comma+2:-1])
        trans_v_wave.append([wavelength, transmittance])

    trans_v_wave.sort(key=lambda x:x[0]) # sort by wavelength
    print(trans_v_wave)

    return


if __name__ == "__main__":
    get_transmittance("O2", [])
