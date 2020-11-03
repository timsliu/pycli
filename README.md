# PyCli

PyCli is a domain specific language (DSL) embedded in Python for climate
modeling. PyCli uses a Python interface to specify a climate model, which
is then run in C++. The output is parallelized using OpenMP and ISPC.

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

## Quick Start

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

## Climate Model

#### Input solar energy
The solar energy falling on each model square is calculated by considering the sunlight falling
on a latitude band and dividing by the number of squares. The total sunlight falling on the earth
is:

![formula](https://render.githubusercontent.com/render/math?math=e^{i \pi} = -1)

