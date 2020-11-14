import pycli

earth = pycli.new_model("small")
earth.gen_random_surface()
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

earth.write_surface("surface.txt")
earth.write_atmosphere("atmos.txt")