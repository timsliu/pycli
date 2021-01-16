import pycli

# generate a planet and preference object
earth, prefs = pycli.new_model("earth")

# optional - modify preferences
prefs.set_pref({"colors": "jet"})         # color for charts

# optional - setup starting concentration of CO2 in ppm
# if not defined in initialization
CO2_level = 0.00036
earth.set_atmosphere("CO2", CO2_level)

# schedule 5 model steps
for i in range(5):
    # increment model step 
    earth.model_step()
 
    CO2_level += 0.00001
    # set CO2 level in ppm
    earth.set_atmosphere("CO2", CO2_level)

# write out the configuration for the planet and the configurations
earth.write_config()
prefs.write_preferences()
