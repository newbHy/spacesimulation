#ifndef ORBITALELEMENTS_H
#define ORBITALELEMENTS_H

#include "misc/typedefs.h"



struct OrbitalElementsMajorPlanet
{
    // a : semi major axis in meters
    // e : eccentricity
    // i : inclination in degrees
    // L : mean longitude in degrees
    // w1: longitude of the periapsis
    // N : longitude of the ascending node
    sfSpace::PRECISE a;
    sfSpace::PRECISE e;
    sfSpace::PRECISE i;
    sfSpace::PRECISE N;
    sfSpace::PRECISE w1;
    sfSpace::PRECISE L;
};


struct OrbitalElementsSimple
{
    // a : semi major axis in meters
    // e : eccentricity
    // i : inclination in degrees
    // N : longitude of the ascending node
    // w : argument of periapsis
    // M : mean anomaly
    sfSpace::PRECISE a;
    sfSpace::PRECISE e;
    sfSpace::PRECISE i;
    sfSpace::PRECISE N;
    sfSpace::PRECISE w;
    sfSpace::PRECISE M;
};


// Used to store rate of change in rate/s
struct OrbitalElementsAll
{
    sfSpace::PRECISE a;
    sfSpace::PRECISE e;
    sfSpace::PRECISE i;
    sfSpace::PRECISE N;
    sfSpace::PRECISE w1;
    sfSpace::PRECISE w;
};

#endif // ORBITALELEMENTS_H
