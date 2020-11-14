# PyCli

PyCli is a domain specific language (DSL) embedded in Python for climate
modeling. PyCli uses a Python interface to specify a climate model, which
is then run in C++. The output is parallelized using OpenMP.

## Environment

PyCli has the following environment requirements:

```
python >= 3.5
C++11
OpenMP
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

``pip`` is not installed on the myth machines by default.

```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py --user
```

Install several packages used by PyCli:

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
cd pysrc/pycli
pip3 install -e .
```

You should now have PyCli installed on your myth account.

## Quickstart

First, make sure you've completed all the steps in the Installation section.
Climate models written in PyCli should be saved in the `<models>` subdirectory.
The PyCli repo includes several climate models already specified. The 
`<earth_big.py>` model simulates the Earth's climate across five timesteps
with varying levels of CO2. Details on how to write your own models are in the
README.md file under the `<pycli>` repository.

To run a model, use the following command while in the `<models>` directory:

```
python3 run-pycli.py <model_name>
```

For the `<earth_big>` prewritten model, the command would be:

```
python3 run-pycli.py earth_big
```

Note that the model name should not have `<.py>` at the end - only include
The name of the model. The `<run-pycli.py>` script will run the PyCli
model interpreter, the climate simulation backend, and the visualization
suite. ahe output should look like:


![Alt text](images/run-pycli_out.png?raw=true "Output from running run-pycli.py")


The script will create a directory with the name of the model in
the `<models>` folder and place a `<surface.txt>` and `<atmosphere.txt>`
file in the directory. These files describe the surface of the planet and
the atmosphere at each simulation step. After the simulation is run, a map
of the final temperatures will be placed in models folder.

![Alt text](images/earth_big.png?raw=true "Earth Big temperature map")

## Directory Organization

#### src
This directory contains C++ source files for running the model and invoking compilation of models. 
The C++ source files form the backend for running the climate model.

#### models
This directory contains PyCli models.

#### bin
The `bin` directory contains compiled binary files.

#### pysrc
This directory contains source code written in Python and contains the PyCli library.

#### tex

#### pyvisual

## Climate Model

#### Input solar energy
The solar energy falling on each model square is calculated by considering the sunlight falling
on a latitude band and dividing by the number of squares. The total sunlight falling on the earth
is:

![formula](https://render.githubusercontent.com/render/math?math=e^{i \pi} = -1)
src="https://render.githubusercontent.com/render/math?math=e^{i \pi} = -1">
