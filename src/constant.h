/* This file contains various physical constants.
 *
 */

#ifndef CONSTANT_H
#define CONSTANT_H

#define LONG_RANGE 360         /* range of longitude in degrees */
#define LAT_RANGE 180          /* range of latitude in degrees */
#define EARTH_RADIUS 6380000   /* radius of earth in meters */
#define PI 3.14159265358979 
#define W_SUN 1366             /* solar flux at top of atmosphere in W/m^2 */
#define SIGMA 5.67e-8          /* stefan boltzmann constant */

/* 1990 CO2 level was 355 ppm with radiative heating of 2.2 watts/m^2 */

#define CO2_HEATING 6285       /* CO2 radiative heating coefficient watts/m^2 */
                               /* multiply by CO2 concentration to get heating */

#define H2O_POWER 3            /* estimated adding heating from water vapor in 
                                  watts/m^2 */

#define CO2_EMIT2CONC 1.28e-7 /* conversion from CO2 emissions in gigatons to
                                  concentration change in mole fraction */
#define CO2_ATMOS 0.44         /* fraction of emitted CO2 absorbed by atmosphere */

#define MODEL_IN "./../models/"
#define MODEL_OUT "./../models/"

// types of surfaces
enum SurfaceType {
    land,
    sea,
    ice
};


#endif /* CONSTANT_H */
