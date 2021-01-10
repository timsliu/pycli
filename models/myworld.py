# myworld.py
# 
# example using the custom sized map of the world

import pycli

# generate a planet and preference object
earth, prefs = pycli.new_model("custom", 
                               num_lat_gridlines=80, 
                               num_lon_gridlines=80, 
                               init_atmos = {"CO2": 0.0001})

# optional - modify preferences
prefs.set_pref({"colors": "jet",            # color spectrum
                "atmos_type": "emission"    # specify CO2 emissions 
               })


# optional - setup starting concentration of CO2 in ppm

# schedule 5 model steps
for i in range(5):
    # increment model step 
    earth.model_step()

    # CO2 emissions in gigatons 
    CO2_emit = 20

    # annual CO2 emissions in gigatons
    earth.set_atmosphere("CO2", CO2_emit)

# write out the configuration for the planet and the configurations
earth.write_config()
prefs.write_preferences()
