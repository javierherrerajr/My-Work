#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "hit.h"
#include "vec.h"
#include "ray.h"

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    // This function implicitly defines the object.  If the input location is on
    // the surface, this function will return zero.  If the input location is
    // inside the surface, it will return a negative number.  If the input
    // location is outside the object, the return value will be positive.  You
    // can think of this as a definition of what the object is.  For each object
    // of interest, it will be given to you.
    virtual double Value(const vec3& location) const=0;

    // These two routines have the same meanings as they did in the ray tracer.
    // You must implement these for each type of object.
    virtual Hit Intersection(const Ray& ray) const=0;
    virtual vec3 Normal(const vec3& location) const=0;
    virtual void Print() const=0;
};

#endif
