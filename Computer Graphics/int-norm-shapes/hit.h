#ifndef __HIT_H__
#define __HIT_H__

#include "vec.h"

// Records information about an intersection, which may be needed later for a
// subsequent call to Normal.
struct Hit
{
    // Distance along the ray at which this occurred; if there was no
    // intersection, set this to a negative value.
    double dist = -1;

    bool Valid() const {return dist>=0;}
};

#endif
