import pycli
import os

def test_create_model():
    earth = pycli.new_model("default")

def test_set_atmosphere():
    earth = pycli.new_model("default")
    earth.set_init_atmosphere("CO2", 0.04)
    earth.set_init_atmosphere("O2", 22)

def test_write_surface():
    if not os.path.exists('tests/build'):
        os.makedirs('tests/build')

    earth = pycli.new_model("small")
    earth.write_surface("tests/build/small_surface.txt")
    assert os.path.exists("tests/build/small_surface.txt")