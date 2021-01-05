import pycli

# generate an planet and preference object
earth, prefs = pycli.new_model("earth")

# optional - modify preferences

# setup starting concentration of CO2 in ppm
earth.set_atmosphere("CO2", 280)

# schedule 5 model steps
for i in range(5):
    # indicate a new step 
    earth.model_step()
  
    # annual CO2 emissions in gigatons
    earth += {"CO2": 20}

# write out the configuration for the planet and the configurations
earth.write_config()
prefs.write_preferences()
