import pycli
import os

def test_create_model():
    earth = pycli.new_model("default")

def test_set_atmosphere():
    earth = pycli.new_model("default")
    earth.set_atmosphere("CO2", 0.04)
    earth.set_atmosphere("O2", 22)
    assert(earth.get_atmosphere("CO2") == 0.04)
    assert(earth.get_atmosphere("O2") == 22)

def test_write_surface():
    if not os.path.exists('tests/build'):
        os.makedirs('tests/build')

    earth = pycli.new_model("small")
    earth.gen_random_surface()
    earth.write_surface("tests/build/small_surface.txt")
    assert os.path.exists("tests/build/small_surface.txt")

def test_write_atmosphere():
    if not os.path.exists('tests/build'):
        os.makedirs('tests/build')

    earth = pycli.new_model("small")
    earth.gen_random_surface()
    earth.set_atmosphere("CO2", 0.04)
    earth.set_atmosphere("O2", 22)
    earth.set_atmosphere("N2", 5.1)
    earth.write_atmosphere("tests/build/small_atmosphere.txt")
    assert os.path.exists("tests/build/small_atmosphere.txt")

def test_complex():
    if not os.path.exists('tests/build'):
        os.makedirs('tests/build')

    earth = pycli.new_model("small")
    earth.gen_random_surface()
    earth.set_atmosphere("O2", 22)
    earth.set_atmosphere("N2", 5.1)

    co2_emiss = 0.04
    earth.set_atmosphere("CO2", co2_emiss)
    for i in range(10):
        earth.model_step()

        if earth.get_atmosphere("CO2") < 5:
            # CO2 emissions decaying function
            co2_emiss += 1
       
        earth.set_atmosphere("CO2", co2_emiss)


    earth.write_atmosphere("tests/build/small_atmosphere.txt")
    assert os.path.exists("tests/build/small_atmosphere.txt")
