# This script is used to invoke the full PyCli stack, from
# generating a model written in the DSL to visualization
#
# To invoke this script, use the command:
# python3 run-pycli.py <model_name>
# 
# where <model_name>.py is the name of the PyCli model holding
# the climate model

import json
import subprocess
import os
import sys
import shutil

PYCLI_ROOT = os.path.join(os.getcwd(), "..")

if __name__ == "__main__":

    model_name = sys.argv[1]    # parse the model name

    if model_name.find(".py") != -1:
        print("Argument to run-pycli.py should be model name without .py extension")
        exit()

    # model input and output paths
    model_out = os.path.join(PYCLI_ROOT, "models/{}/out".format(model_name))
    model_in = os.path.join(PYCLI_ROOT, "models/{}".format(model_name))
  
    # 1) make sure there is the needed in and out files
    print("\n**** Cleaning output path ****\n")

    for path in [model_in, model_out]:
        if os.path.exists(path):
            shutil.rmtree(path)
        os.mkdir(path)

    # 2) compile the model and generate surface and atmosphere files
    print("\n**** Generating model description ****\n")
    os.chdir(os.path.join(PYCLI_ROOT, "models"))
    try:
        subprocess.run([
            "python3",
            model_name + ".py",
        ], check=True)

    except subprocess.CalledProcessError:
        print("\nPyCli execution halted due to invalid argument/configuration") 
        exit()

    # open preference file
    prefs = None
    with open(os.path.join(PYCLI_ROOT, "models/{}/prefs.json".format(model_name))) as f:
        prefs = json.load(f)
    
    verbose_mode = ""
    if prefs["verbose"]:
        verbose_mode = "verbose"
    else:
        verbose_mode = "silent"
    
    # 3) update src
    print("\n**** Compiling PyCli backend source ****\n")
    os.chdir(os.path.join(PYCLI_ROOT, "src"))
    subprocess.run([
        "make",
        "-j4"
    ])
    
    # 4) run the C++ climate model
    print("\n**** Starting backend climate model ****\n")
    os.chdir(os.path.join(PYCLI_ROOT, "src"))
   
    # map verbose preference to flag
    if prefs["verbose"]: 
        verbose_str = "-v" 
    else:
        verbose_str = ""
   
    # map atmos type preference to flag
    if prefs["atmos_type"] == "emission":
        atmos_str = "-e"
    else:
        atmos_str = ""

    subprocess.run([
        "./../bin/pycli", 
        model_name,
        verbose_str,
        atmos_str,
        "-m",
        prefs["backend_model"]
    ])
    
    # 5) run visualization
    os.chdir(os.path.join(PYCLI_ROOT, "vis"))
    print("\n**** Running visualization suite ****\n")
    
    subprocess.run([
        "python3",
        os.path.join(PYCLI_ROOT, "vis/graphics.py"),
        "-v",                      # verbose mode
        verbose_mode,
        "-t",                      # temperature unit
        prefs["temp_unit"],
        model_name,
    ])

    print("\n**** PyCli finished - exiting...  ****\n")

