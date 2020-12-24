import numpy as np
import matplotlib.pyplot as plt

from constants import *

LU_MIN = 0.1        # lowest wavelength considered (100 nm)
LU_MAX = 40         # longest wavelength considered (40 um)
LU_STEP = 0.1       # increment between wavelengths
DEFAULT_TEMP = 300  # temperature in Kelvin

#SPECIES = ["O2", "H2O", "O3"]
SPECIES = ["H2O"]

def planck(temp, lu, plot=False):
    '''plot planck's distribution at a given temperature. 
    inputs: temperature (float)
            lu (array) list of wavelengths (in um) to calculate
    output: b_norm(array) - normalized spectral radiance at each lu value
    '''

    lu_step = lu[1] - lu[0]
    l = lu/1e6                                   # wavelength in meters (MKS)
    b = 2 * h * c ** 2 / l ** 5 * 1/(np.exp(h*c/(l * Kb * temp)) - 1)


    # normalize so total adds to 1
    total_flux = sum(b) * lu_step                # approx integral of flux
    b_norm = b/total_flux
    
    if plot:
        plt.plot(lu, b_norm)
        plt.show()

    return b_norm


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

    # return array of transmittance values
    
    return np.array([get_trans_value(x, trans_v_wave) for x in lu])

def get_trans_value(wavelength, trans_v_wave):
    '''returns the transmittance of a certain wavelength given the
    wavelength (single float) and a sorted array with the [lu, transmittance]
    values'''

    # iterate through transmittance array, looking for the two wavelengths
    # around the passed value
    for i in range(len(trans_v_wave)):
        # exact match
        if wavelength == trans_v_wave[i][0]:
            return trans_v_wave[i][1]
        # reached end of array - use last value
        if i == len(trans_v_wave) - 1:
            return trans_v_wave[-1][1]
        # found two elements around passed wavelength 
        if wavelength > trans_v_wave[i][0] and wavelength < trans_v_wave[i+1][0]:
            # interpolate
            x1 = trans_v_wave[i][0]
            x2 = trans_v_wave[i+1][0]
            y1 = trans_v_wave[i][1]
            y2 = trans_v_wave[i+1][1]
            m = (y2 - y1)/(x2 - x1)     # slope between two array points

            # interpolate transmittance at wavelength and return
            return m * (wavelength - x1) + y1

def total_absorbance(lu):
    '''calculates the total absorbance of a collection of gas species
    inputs: lu (array) - wavelengths to calculate absorbance at in um
    outputs: total_absorbance (array) absorbance at each wavelength'''

    total_absorbance = [0 for x in range(len(lu))]  # total abs. of all specie
    for specie in SPECIES:
        transmittance = get_transmittance(specie, lu)
        # convert transmittance to absorbance
        absorbance = [1 - x for x in transmittance]
        # sum absorbances and put ceiling at 1
        for i in range(len(total_absorbance)):
            total_absorbance[i] += absorbance[i]
        total_absorbance = [min(x, 1) for x in total_absorbance]

    return total_absorbance



if __name__ == "__main__":
    lu = np.arange(LU_MIN, LU_MAX, LU_STEP)   # wavelength in micrometers
    total_abs = total_absorbance(lu)
    b_norm = planck(DEFAULT_TEMP, lu)
    avg_absorb = 0

    for i in range(len(total_abs)):
        avg_absorb += LU_STEP * total_abs[i] * b_norm[i]

    print("Average absorbance: {}".format(avg_absorb))

