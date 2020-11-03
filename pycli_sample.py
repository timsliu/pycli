import pycli

earth = pycli.new_model("default")

earth.set_atmosphere("CO2", 0.04)
earth.set_atmosphere("02", 22)

for i in range(MODEL_STEPS):
    earth.model_step()
    earth.output_temps()

    if earth.get_atmosphere("C02") > THRESHOLD:
        # CO2 emissions decaying function
        co2_emiss = CO2_CONST * np.e ^ -i/ALPHA
    else:
        # CO2 emissions linearly growing
        co2_emiss = CO2_CONST * i * BETA

    # simulate greenhouse gas emissions 
    earth.emit_gas("C02", co2_emiss)





