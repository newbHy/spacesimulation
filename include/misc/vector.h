#ifndef VECTOR_H
#define VECTOR_H

#include "typedefs.h"



class Vector
{
    public:
        Vector();
        Vector(sfSpace::PRECISE x, sfSpace::PRECISE y, sfSpace::PRECISE z);
        virtual ~Vector();

        sfSpace::PRECISE x, y, z;
};

#endif // VECTOR_H
