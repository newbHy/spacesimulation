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

class Vector2D
{
    public:
        Vector2D();
        Vector2D(sfSpace::PRECISE x, sfSpace::PRECISE y);
        Vector2D(const Vector& copyvector);
        virtual ~Vector2D();

        Vector2D& operator+=(const Vector2D& rhs);
        Vector2D& operator-=(const Vector2D& rhs);
        Vector2D& operator*=(const sfSpace::PRECISE& rhs);

        sfSpace::PRECISE x, y;
};


#endif // VECTOR_H
