# PyCli

PyCli is a domain specific language (DSL) embedded in Python for climate
modeling. PyCli uses a Python interface to specify a climate model, which
is then run in through a C++ backend parallelized with OpenMP. The final
output of the simulation is saved as a temperature map using the `pyvisual`
visualization suite.

PyCli is designed to be an educational tool for understanding climate modeling.
PyCli lets users tweak the rate of greenhouse gas emissions and see how the
climate reacts. PyCli uses a very simplified model of the climate to do 
calculations and ignores factors such as particulate matter, cloud cover,
and ocean currents. This project is not meant to compete with the climate
models designed by national institutes. Rather, it is purely an educational
tool designed for people interested in climate change and scientific computing.

## Supported Modeling Features
PyCli uses a discretized grid to represent the earth and to simulate
temperatures. Currently, the model allows users to specify:

1. The surface of the planet (land, sea, or ice)
2. The model resolution, defined by the size of the grid
3. The composition of the atmosphere at each simulation step. The CO2 level is
currently the main driver of temperature changes between steps.

Additional PyCli user features are currently under development. Some of the
planned features for users include:

- Simulating different planets at different distances from the Sun
- Modifying concentrations of other greenhouse gases such as methane
- Exploring the effect of geoengineering the planet by adding sulfur
dioxide to the planet and reflecting away sunlight

## Environment

PyCli has been tested with the following specifications:

```
python >= 3.5
C++11
OpenMP
matplotlib >= 3.03
numpy >= 1.18.5

```

For instructions on installing OpenMP, please see [this page](https://www.geeksforgeeks.org/openmp-introduction-with-installation-guide/). More information on
OpenMP can also be found on [their website](https://www.openmp.org/). Once you've
installed OpenMP, you can test your installation by running `make omp` in the
`src` directory. You should see the numbers 1-20 printed out of order.

## Installation

PyCli has currently ony been tested on the Myth cluster (myth.stanford.edu).
The myth cluster machines run Ubuntu14 on a 4.2 GHz Intel Core i7 processor
with 2 hyperthreads per core. More details about the myth machines can be
found [here](https://ark.intel.com/products/97129/Intel-Core-i7-7700K-Processor-8M-Cache-up-to-4-50-GHz://ark.intel.com/products/97129/Intel-Core-i7-7700K-Processor-8M-Cache-up-to-4-50-GHz-).

Future versions of PyCli will be supported on other Unix distributions and 
macOS. There are no plans to support PyCli on Windows.

To install PyCli and get your first model running, first clone the repository:

```
git clone https://github.com/timsliu/pycli.git
```
 
``pip`` is not installed on the myth machines by default. To install, use the
following commands:

```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py --user
```

Next, install several packages used by PyCli:

```
pip3 install numpy
pip3 install matplotlib
```

The visualization uses the ``basemap`` library. To install the basemap
library:

```
cd pyvisual
wget https://github.com/matplotlib/basemap/archive/v1.2.2rel.tar.gz
tar -zxvf v1.2.2rel.tar.gz
cd basemap-1.2.2rel
cd geos-3.3.3
export DEOS_DIR=~
./configure --prefix=$GEOS_DIR
make
make_install
cd ..
pip3 install -e .
```

If these steps fail, comment out your entire `<~/.bashrc>` and try again. 


Finally, install the pycli python library:

```
cd ../pysrc
pip3 install -e .
```

You should now have PyCli installed on your myth account.

## Quickstart

First, make sure you've completed all the steps in the Installation section.
Climate models written in PyCli should be saved in the `<models>` subdirectory.
The PyCli repo includes several climate models already specified. The 
`earth_big.py` model simulates the Earth's climate across five timesteps
with varying levels of CO2. Details on how to write your own models are in the
README.md file under the `pycli` repository.

To run a model, use the following command while in the `<models>` directory:

```
python3 run-pycli.py <model_name>
```

For the `earth_big` prewritten model, the command is:

```
python3 run-pycli.py earth_big
```

Note that the model name should not have `.py` at the end - only include
The name of the model. The `run-pycli.py` script will run the PyCli
model interpreter, the climate simulation backend, and the visualization
suite. The output should look like:


![Alt text](images/run-pycli_out.png?raw=true "Output from running run-pycli.py")


The script will create a directory with the name of the model in
the `<models>` folder and place a `surface.txt` and `atmosphere.txt`
file in the directory. These files describe the surface of the planet and
the atmosphere at each simulation step. After the simulation is run, a map
of the final temperatures will be placed in models folder.

![Alt text](images/earth_big.png?raw=true "Earth Big temperature map")

## Folder Organization
This section briefly describes the contents of each of the subfolders in the
PyCli repo. Each section has a `README.md` with more details about the subfolders
function.

### src
The `src` directory contains the C++ backend for running the climate model.
This folder also contains the `Makefile` for compiling the model. Users wishing
to modify the climate model should make changes in this directory.

### models
This directory contains PyCli models. All PyCli models should be written and
saved in this directory. Each time a PyCli model is run, a new subfolder will
be generated holding the atmosphere and surface configuration files. The final
temperature map will also be dumped into this directory.

This directory also holds the `run-pycli.py` script. This script is run to
invoke the entire PyCli stack. The script will run the PyCli front end to
generated configuration files, launch the C++ backend, and finally use the
visualization suite to create graphs and maps.

### bin
The `bin` directory contains compiled binary files.

### pysrc
This directory contains the PyCli library for the PyCli front end. The front
end is implemented as a series of method calls for users to create a new
model, set the surface, and specify the atmosphere at each step. The Python
front end is also responsible for generating the model configuration files used
by the C++ climate model.

Users wishing to learn more about writing models in PyCli should read the
`README` in this folder.

### tex
This directory contains typeset documents describing how the C++ climate
model backend works. Users interested in the science and mathematics behind
the model should read this document.


### pyvisual
This directory contains the installation of the `basemap` library used for
generating temperature maps. This folder also has the visualization suite
responsible for parsing temperature files and generating temperature maps.

## Planned features and TODO

### Python Frontend

* Improved random surface generation using random "islands" that grow in 
each direction based on some probability (v 0.2)
* Use Python operator overloading to allow setting atmospheric gas
concentrations without calling methods (v 0.2)
* Allow input to be either CO2 levels or annual net emissions (v 0.1)
* Conditional statements based on temperature (v 0.3)
* Make output temperatures a preference (v 0.1) **Done**

### Backend climate model
* Fix convolution wrapping around vertical edge of map (v 0.1) **Done**
* Update convolution so that grid cells over the poles are adjacent (v 0.1) **Done** 
* Add accelerated convolution and average temp calculation so accelerated
model can be used (v 0.2)
* Add tilt to the planet (v 0.4)
* Make temperature at each timestep influenced by previous timestep - currently
each timestep is independent (v 0.2)
* Change surfaces so that ice can melt and water can freeze depending on temperature (v 0.3)
* Spawn additional threads to output temperature files in parallel with calculations (v 0.2)
* Optionally output intermediate temperature files (v 0.2)

### Visualization suite
* Remove basemap and build TKinter/matplotlib drawing mechanism (v 0.1) **Done**
* Line chart of average temperature (v 0.1) **Done**
* Stitch temperature files into a gif (v 0.3)


### Additional features
* OSX compatibility (there are no plans to make PyCli Windows compatible) (v 0.1) **Done**

## Contributors and Contact
PyCli is an open source project created by Kalhan Koul, Timothy Liu, and
Jack Melchert at Stanford. This project originated from a [CS343D: Domain Specific
Programming Models and Compilers](https://cs343d.github.io/)  course assignment
and is currently maintained and updated by Timothy Liu.
