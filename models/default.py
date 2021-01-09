# default.py
#
# Example model using the default planet and a randomly generated
# surface

import pycli

# generate a planet and preference object
earth, prefs = pycli.new_model()

# optional - modify preferences
prefs.set_pref({"verbose": False, "colors": "jet"})

# optional - setup starting concentration of CO2

for i in range(10):
    # increment model step
    earth.model_step()

    # get current CO2 level and increase by 2% each step
    CO2_level = earth.get_atmosphere()["CO2"]
    CO2_level *= 1.02
    
    earth.set_atmosphere("CO2", CO2_level)

# write out the configuration for planet
earth.write_config()
prefs.write_preferences()
