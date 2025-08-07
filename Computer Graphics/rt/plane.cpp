#include "plane.h"
#include "hit.h"
#include "ray.h"
#include <cfloat>
#include <limits>

Plane::Plane(const Parse* parse,std::istream& in)
{
    in>>name>>x>>normal;
    normal=normal.normalized();
}

// Intersect with the plane.  The plane's normal points outside.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    Hit hit = Hit();
    double t = -dot((ray.endpoint - this->x), this->normal)/(dot(ray.direction, this->normal));

    if (t > small_t) 
    {
        hit.dist=t;
        Pixel_Print("Intersect test with ", this->name, "; hit: ", hit);
    }
    else Pixel_Print("No intersect with ", this->name);

    return hit;
}

vec3 Plane::Normal(const Ray& ray, const Hit& hit) const
{
    return normal;
}

std::pair<Box,bool> Plane::Bounding_Box(int part) const
{
    Box b;
    b.Make_Full();
    return {b,true};
}
