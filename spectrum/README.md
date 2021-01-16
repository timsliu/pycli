# Spectrum

This folder contains files used to calculate physical constants for the
PyCli backend climate model. A key atmospheric parameter is its infrared
absorption - this is the fraction of IR energy emitted by the surface that is
absorbed by the atmosphere. A higher IR absorption corresponds to a stronger
greenhouse gas effect and higher temperatures.

The IR absorption was calculated by modeling the Earth's IR emission as 
blackbody radiation and integrating the emission against the known absorption
of several greenhouse gases.

The `images` directory contains images of the absorption spectrum for several
greenhouse gases. These raw values of the curves were extracted from the
images using the online WebPlotDigitizer tool. The `.txt` files in this
directory are the raw data points extractecd from the graphs.
