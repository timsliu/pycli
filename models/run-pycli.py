# This script is used to invoke the full PyCli stack, from
# generating a model written in the DSL to visualization
#
# To invoke this script, use the command:
# python3 run-pycli.py <model_name>
# 
# where <model_name>.py is the name of the PyCli model holding
# the climate model


import subprocess
import os
import sys
import shutil

PYCLI_ROOT = os.path.join(os.getcwd(), "..")

if __name__ == "__main__":

    model_name = sys.argv[1]
    model_out = os.path.join(PYCLI_ROOT, "src/out/{}".format(model_name))
    model_in = os.path.join(PYCLI_ROOT, "models/{}".format(model_name))
  
    # make sure there is the needed in and out files
    for path in [model_in, model_out]:
        if os.path.exists(path):
            shutil.rmtree(path)
        os.mkdir(path)

    # update src
    os.chdir(os.path.join(PYCLI_ROOT, "src"))
    subprocess.run([
        "make",
        "-j4"
    ])

    os.chdir(os.path.join(PYCLI_ROOT, "models"))
    # 1) compile the model and generate surface and text
    subprocess.run([
        "python3",
        model_name + ".py",
    ])


    # 2) run the C++ climate model
    os.chdir(os.path.join(PYCLI_ROOT, "src"))
    subprocess.run([
        "./../bin/pycli", 
        model_name, 
        "-v",
        "-m",
        "serial"
    ])
    os.chdir(PYCLI_ROOT)

    # 3) run visualization
    subprocess.run([
        "python3",
        os.path.join(PYCLI_ROOT, "pyvisual/visualization_bm.py"),
        model_name,
        PYCLI_ROOT
    ])
