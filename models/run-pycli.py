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
   
    if model_name.find(".py") != -1:
        print("Argument to run-pycli.py should be model name without .py extension")
        exit()

    model_out = os.path.join(PYCLI_ROOT, "models/{}/out".format(model_name))
    model_in = os.path.join(PYCLI_ROOT, "models/{}".format(model_name))
  
    # 1) make sure there is the needed in and out files
    for path in [model_in, model_out]:
        if os.path.exists(path):
            shutil.rmtree(path)
        os.mkdir(path)


    os.chdir(os.path.join(PYCLI_ROOT, "models"))
    # 2) compile the model and generate surface and atmosphere files
    try:
        subprocess.run([
            "python3",
            model_name + ".py",
        ], check=True)

    except subprocess.CalledProcessError:
        print("\nPyCli execution halted due to invalid argument/configuration") 
        exit()

    
    # 3) update src
    os.chdir(os.path.join(PYCLI_ROOT, "src"))
    subprocess.run([
        "make",
        "-j4"
    ])
    
    # 4) run the C++ climate model
    os.chdir(os.path.join(PYCLI_ROOT, "src"))
    subprocess.run([
        "./../bin/pycli", 
        model_name, 
        "-v",
        "-m",
        "serial"
    ])
    
    os.chdir(os.path.join(PYCLI_ROOT, "vis"))
    # 5) run visualization
    subprocess.run([
        "python3",
        os.path.join(PYCLI_ROOT, "vis/graphics.py"),
        model_name,
        PYCLI_ROOT
    ])
