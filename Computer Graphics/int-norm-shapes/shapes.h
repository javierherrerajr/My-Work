#ifndef __shapes_H__
#define __shapes_H__

#include "object.h"

class PotatoChip:public Object
{
public:
    double a,b,c; // You may assume a,b,c > 0

    virtual double Value(const vec3& location) const override
    {
        double x=location[0],y=location[1],z=location[2];
        return a*x*x+b*y*y-c*z;
    }
    virtual Hit Intersection(const Ray& ray) const override;
    virtual vec3 Normal(const vec3& location) const override;
    virtual void Print() const override
    {
        std::cout<<"(PotatoChip "<<a<<" "<<b<<" "<<c<<")\n";
    }
};

class Cylinder:public Object
{
public:
    // You may assume that axis is normalized and r>0.
    vec3 point,axis;
    double r;

    virtual double Value(const vec3& location) const override
    {
        vec3 v=location-point;
        vec3 w=v-dot(v,axis)*axis;
        return w.magnitude_squared()-r*r;
    }
    virtual Hit Intersection(const Ray& ray) const override;
    virtual vec3 Normal(const vec3& location) const override;
    virtual void Print() const override
    {
        std::cout<<"(Cylinder "<<point<<" "<<axis<<" "<<r<<")\n";
    }
};

#endif
