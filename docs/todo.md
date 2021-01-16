## Planned features

### Python Frontend

* Improved random surface generation using random "islands" that grow in 
each direction based on some probability (v 0.2)
* Use Python operator overloading to allow setting atmospheric gas
concentrations without calling methods (v 0.2)
* Conditional statements based on temperature (v 0.3)

### Backend climate model
* Add accelerated convolution and average temp calculation so accelerated
model can be used (v 0.2)
* Add tilt to the planet (v 0.4)
* Make temperature at each timestep influenced by previous timestep - currently
each timestep is independent (v 0.2)
* Change surfaces so that ice can melt and water can freeze depending on temperature (v 0.3)
* Spawn additional threads to output temperature files in parallel with calculations (v 0.2)
* Optionally output intermediate temperature files (v 0.2)

### Visualization suite
* Stitch temperature files into a gif (v 0.3)


### Miscellaneous
* Fork release main and dev-main branches


##
Copyright 2021 Timothy Liu
