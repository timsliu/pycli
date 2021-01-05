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
            raise ValueError("Atmosphere classe expects dictionary in initializer")

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
                value (float) - amount of gas added to atmosphere
                step (int) - model timestep '''

        # if gas isn't specified for all timesteps, fill in the intermediate
        # timesteps with the most recent concentration
        self.fill_steps(gas, step)

        # TODO convert gas value to concentration
        concentration = value
        # update new concentration 
        self.gases[gas].append(concentration)
        return 

    def fill_steps(self, gas, step):
        '''fill in the concentrations of a gas that isn't specified for all time
        with the last value so that the gas concentration is the right length. 
        Ex: A step value of 4 (0 indexed, the fifth step after initialization)
            will make the gas have a length of 5'''

        while len(self.gases[gas]) - 1 < step:
            self.gases[gas].append(self.gases[gas][-1])

        return

    def write_to_file(self):
        # find longest gas list
        max_len = max([len(self.gases[gas]) for gas in self.gases.keys()]) 
        
        for gas in self.gases.keys():
            self.fill_steps(gas, max_len - 1)

        # find model name 
        model_name = sys.argv[0][0:sys.argv[0].find(".")]

        # create the atmosphere file and write out concentration at each step
        with open(os.path.join(model_name, "atmosphere.txt"), "w") as f:
            for i in range(max_len):
                for gas in self.gases.keys():
                    f.write(gas + str(self.gases[gas][i])
                f.write("\n")
