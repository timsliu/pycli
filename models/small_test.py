import pycli

# size of model
earth = pycli.new_model("small")
# how to fill in the surface
earth.gen_random_surface()
# should be way to specify preset models
earth.set_atmosphere("O2", 22)

co2_emiss = 0.0001
earth.set_atmosphere("CO2", co2_emiss)

n2_emiss = 77.99
earth.set_atmosphere("N2", n2_emiss)

for i in range(5):
    earth.model_step()

    co2_emiss += 0.0001
    n2_emiss -= 0.01
    
    earth.set_atmosphere("CO2", co2_emiss)
    earth.set_atmosphere("N2", n2_emiss)

# change this to put in a directory with the model name
earth.write_surface()
earth.write_atmosphere()
