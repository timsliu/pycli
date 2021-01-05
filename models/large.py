# large.py
#
# Example model using the large, randomly generated surface

import pycli

# generate a planet and preference object
earth, prefs = pycli.new_model("large")

# optional - modify preferences
prefs.set_pref({"verbose": True, "colors": "jet"})

# optional - setup starting concentration of CO2
earth.set_atmosphere("CO2", 0.0004)

# variable used in loop
panic = False
for i in range(20):
    # increment model step
    earth.model_step()

    # get current CO2 level
    CO2_level = earth.get_atmosphere()["CO2"]
   
    # CO2 level reaches some threshold, changing behavior
    if CO2_level > 0.0006:
        panic = True

    if panic: 
        CO2_level *= 0.9  # quick, cut emissions!!
    else:
        CO2_level *= 1.04 # business as usual :)
    
    earth.set_atmosphere("CO2", CO2_level)

# write out the configuration for planet
earth.write_config()
prefs.write_preferences()
