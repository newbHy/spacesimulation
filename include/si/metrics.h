#ifndef METRICS_H_INCLUDED
#define METRICS_H_INCLUDED

#include "misc/typedefs.h"



namespace sfSpace
{
    namespace SI
    {
        const sfSpace::PRECISE M    = 1.;
        const sfSpace::PRECISE KM   = M * 1000;
        const sfSpace::PRECISE LD   = M * 384402000;
        const sfSpace::PRECISE AU   = M * 149597870700;
        const sfSpace::PRECISE pc   = M * 3.0857e16;
        const sfSpace::PRECISE ly   = M * 9.4607e15;
    }

    const PRECISE Pi = 3.14159265358979323846;
    const PRECISE G  = 6.67408e-11;
}

#endif // METRICS_H_INCLUDED
