# This script is used to invoke the full PyCli stack, from
# generating a model written in the DSL to visualization
#
# To invoke this script, use the command:
# python3 run-pycli.py <model_name>
# 
# where <model_name>.py is the name of the PyCli model holding
# the climate model

PYCLI_ROOT = "./.."

import subprocess
import os
import sys
import shutil

if __name__ == "__main__":

    model_name = sys.argv[0]
    model_out = os.path.join(PYCLI_ROOT, "src/out/{}".format(model_name))

    # 1) compile the model and generate surface and text
    subprocess.run([
        "python3",
        model_name + ".py",
    ])

    # make sure there's an out file for the model
    if os.path.exists(model_out):
        shutil.rmtree(model_out)
    os.mkdir(model_out)

    # 2) run the C++ climate model
    subprocess.run([
        os.path.join(PYCLI_ROOT, "bin/pycli"), 
        model_name, 
        "-v",
        "accel"
    ])

    # 3) run visualization
    subprocess.run([
        "python3",
        os.path.join(PYCLI_ROOT, "pyvisual/visualization.bm.py"),
        model_name
    ])
