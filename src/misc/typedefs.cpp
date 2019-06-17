#ifdef DEBUG

#include <stdio.h>

#include "misc/typedefs.h"



void sfSpace::testSizes()
{
    if (sizeof(sfSpace::PRECISE) == sizeof(double))
    {
        printf("[Warning] PRECISE not long!\n");
    }
}

#endif // DEBUG
