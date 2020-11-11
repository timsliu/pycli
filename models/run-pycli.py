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
    model_in = os.path.join(PYCLI_ROOT, "models/{}".format(model_name))
  
    # make sure there is the needed in and out files
    for path in [model_in, model_out]:
        if os.path.exists(path):
            shutil.rmtree(path)
        os.mkdir(path)
    
    # 1) compile the model and generate surface and text
    subprocess.run([
        "python3",
        model_name + ".py",
    ])


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
