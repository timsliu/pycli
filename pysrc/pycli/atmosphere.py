# atmosphere.py
#
# Class that describes the composition of the atmosphere at each state
# only gases whos concentrations are input into the model are considered


import os
import sys

# list of gases that can be modified
ALLOWED_GASES = ["CO2"]

class Atmosphere:
    def __init__(self, start_atmos):
        self.gases = {}

        # check that passed argument is a dictionary
        if !isinstance(start_atmos, dict):
            print("Atmosphere class must be initialized with a dictionary")

        # check that gas is in the allowed list
        for gas in start_atmos.keys():
            if gas not in ALLOWED_GASES:
                print("Gas: {} not in list of allowed gases: {}".format(gas, ALLOWED_GASES))
            # permitted gas - add to the dictionary 
            else:
                self.gases[gas] = start_atmos[gas]


    def update_atmosphere(self, gas, value, step):
        '''update the atmosphere with the given gas with with the specified amount
        and timestep
        inputs: gas (str) - name of gas
                value (float) - mass of gas
                step (int) - model timestep '''

        # if gas isn't specified for all timesteps, fill in the intermediate
        # timesteps with the most recent concentration
        self.fill_steps(gas, step)
        while len(self.gases[gas]) - 1 < step:
            self.gases[gas].append(self.gases[gas][-1])

        # TODO convert gas value to concentration
        concentration = value
        # update new concentration 
        self.gases[gas].append(concentration)
        return 

    def fill_steps(self, gas, step):
        '''fill in the concentrations of a gas that isn't specified for all time
        with the last value so that the gas concentration is the right length'''

        while len(self.gases[gas]) - 1 < step:
            self.gases[gas].append(self.gases[gas][-1])

    def write_to_file(self):
        # find longest gas list
        last_step = max([len(self.gases[gas]) for gas in self.gases.keys()]) 
        
        for gas in self.gases.keys():
            self.fill_steps(gas, last_step + 1)

        model_name = sys.argv[0][0:sys.argv[0].find(".")]
        with open(os.path.join(model_name, "atmosphere.txt"), "w") as write_file:
            for i in range(len(self.co2)):
                write_file.write("co2 " + str(self.co2[i]))
                write_file.write(" o2 " + str(self.o2[i]))
                write_file.write(" n2 " + str(self.n2[i]))
                write_file.write("\n")
