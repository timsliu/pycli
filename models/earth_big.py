import pycli

# size of model
earth = pycli.new_model("earth_big")

# setup starting atmosphere
earth.set_atmosphere("O2", 22)

co2_emiss = 0.0001
earth.set_atmosphere("CO2", co2_emiss)

n2_emiss = 77.99
earth.set_atmosphere("N2", n2_emiss)

# schedule 5 model steps
for i in range(5):
    earth.model_step()

    co2_emiss += 0.0001
    n2_emiss -= 0.01
   
    # change CO2 concentration at each step
    earth.set_atmosphere("CO2", co2_emiss)
    earth.set_atmosphere("N2", n2_emiss)

# save surface, atmosphere, and configuration files
earth.write_surface()
earth.write_atmosphere()
pycli.write_preferences()
