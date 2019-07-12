#ifdef DEBUG

#include <stdio.h>
#include "typedefs.h"



void sfSpace::testSizes()
{
    if (sizeof(sfSpace::PRECISE) == sizeof(double))
    {
        printf("[Warning] PRECISE not long!\n");
    }
}

#endif // DEBUG
