import pycli

# generate a planet and preference object
earth, prefs = pycli.new_model("earth")

# optional - modify preferences

# optional - setup starting concentration of CO2 in ppm
# if not defined in initialization
earth.set_atmosphere("CO2", 0.00028)

# schedule 5 model steps
for i in range(5):
    # increment model step 
    earth.model_step()
  
    # annual CO2 emissions in gigatons
    earth.set_atmosphere("CO2", 0.0003)

# write out the configuration for the planet and the configurations
earth.write_config()
prefs.write_preferences()
