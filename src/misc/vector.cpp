#include "vector.h"



///////////////////////////////////////////////////////////////////////////////
Vector::Vector() : x(0.0), y(0.0), z(0.0)
{
    //ctor
}


///////////////////////////////////////////////////////////////////////////////
Vector::Vector(sfSpace::PRECISE px, sfSpace::PRECISE py, sfSpace::PRECISE pz) : x(px),
    y(py),
    z(pz)
{

}


///////////////////////////////////////////////////////////////////////////////
Vector::~Vector()
{
    //dtor
}