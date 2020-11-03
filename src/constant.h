/* This file contains various physical constants.
 *
 */



#ifndef CONSTANT_H
#define CONSTANT_H

#define LONG_RANGE 360         /* range of longitude in degrees */
#define LAT_RANGE 180          /* range of latitude in degrees */
//#define EARTH_RADIUS 6380000   /* radius of earth in meters */
#define EARTH_RADIUS 1         /* radius of earth in meters */
#define PI 3.14159265358979 
#define W_SUN 1366             /* solar flux at top of atmosphere in W/m^2 */
// types of surfaces
enum SurfaceType {
    land,
    sea,
    ice
};

#endif /* CONSTANT_H */
