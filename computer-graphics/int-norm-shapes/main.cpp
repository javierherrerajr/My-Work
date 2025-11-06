#include <cassert>
#include <random>
#include <iostream>
#include <iomanip>
#include "shapes.h"

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_real_distribution<> dist(0, 1);

// These helpers are defined at the bottom of this file.
double rand_num(double a,double b);
vec3 rand_vec(double a,double b);
vec3 rand_dir();
Object* rand_object(int obj_type);
Ray rand_ray();
bool is_intersection(Object* obj, const Ray& ray, double dist);
bool is_first_intersection(Object* obj, const Ray& ray, double dist);
bool has_intersection(Object* obj, const Ray& ray);
bool test_normal(Object* obj, const vec3& loc, const vec3& norm);

int main(int argc, char* argv[])
{
    bool intersect_ok[2]={true,true};
    bool normal_ok[2]={true,true};

    std::cout<<std::setprecision(16);
    for(int obj_type=0;obj_type<2;obj_type++)
    {
        // Run a bunch of tests to see if the routines are likely correct.
        for(int i=0;i<1000;i++)
        {
            // Construct a random object.
            Object* obj=rand_object(obj_type);

            // Construct a random ray.
            Ray ray=rand_ray();

            // Get intersection location
            Hit hit=obj->Intersection(ray);
            if(hit.dist>=0)
            {
                // Intersection routine says this is an intersection; see if it
                // actually is.
                if(!is_intersection(obj,ray,hit.dist))
                {
                    intersect_ok[obj_type]=false;
                    break;
                }

                // Next, check to see if it is the first one.
                if(!is_first_intersection(obj,ray,hit.dist))
                {
                    intersect_ok[obj_type]=false;
                    break;
                }

                // Intersection seems to be okay; check the normal.
                if(normal_ok[obj_type])
                {
                    vec3 loc=ray.Point(hit.dist);
                    vec3 norm=obj->Normal(loc);
                    if(!test_normal(obj,loc,norm))
                    {
                        normal_ok[obj_type]=false;
                        break;
                    }
                }
            }
            else
            {
                // Intersection routine says there is no intersection; check for
                // one.
                if(has_intersection(obj,ray))
                {
                    intersect_ok[obj_type]=false;
                    break;
                }
            }
            delete obj;
        }
    }    

    const char* pf[2]={"FAIL","PASS"};
    for(int obj_type=0;obj_type<2;obj_type++)
    {
        std::cout<<pf[intersect_ok[obj_type]]<<" int "<<obj_type<<std::endl;
        if(intersect_ok[obj_type])
            std::cout<<pf[normal_ok[obj_type]]<<" normal "<<obj_type<<std::endl;
    }

    // Detect early termination.
    if(argv[1]) std::cout<<"TOKEN "<<argv[1]<<std::endl;
    return 0;
}

double rand_num(double a,double b)
{
    return dist(mt)*(b-a)+a;
}

vec3 rand_vec(double a,double b)
{
    vec3 u;
    for(auto&i:u.x) i=rand_num(a,b);
    return u;
}
vec3 rand_dir()
{
    vec3 u;
    do u=rand_vec(-1,1);
    while(u.magnitude_squared()>1);
    return u.normalized();
}

// Construct a random object.
Object* rand_object(int obj_type)
{
    if(obj_type)
    {
        auto o=new PotatoChip;
        o->a=rand_num(1,2);
        o->b=rand_num(1,2);
        o->c=rand_num(1,2);
        return o;
    }
    else
    {
        auto o=new Cylinder;
        o->point=rand_vec(-2,2);
        o->axis=rand_dir();
        o->r=rand_num(0.5,1.5);
        return o;
    }
}

// Construct a random ray.
Ray rand_ray()
{    
    Ray ray;
    ray.endpoint=rand_vec(-2,2);
    ray.direction=rand_dir();
    return ray;
}

bool is_intersection(Object* obj, const Ray& ray, double dist)
{
    // Get intersection point.
    vec3 loc=ray.Point(dist);

    // Intersection routine says there is an intersection.  We can
    // verify that there is an intersection here by checking to see if
    // Value is zero at that location.
    double value=obj->Value(loc);
    if(fabs(value)<1e-6) return true;

    std::cout<<"Intersect failed"<<std::endl;
    obj->Print();
    std::cout<<"Value "<<value<<std::endl;
    std::cout<<"Location "<<loc<<std::endl;
    std::cout<<"Distance "<<dist<<std::endl;
    return false;
}

bool is_first_intersection(Object* obj, const Ray& ray, double dist)
{
    // Next, lets see if it is the first one.  If so, Value should
    // have the same sign at the beginning of the ray and just
    // before the intersection location.
    double v0=obj->Value(ray.Point(0));
    double v1=obj->Value(ray.Point(dist-1e-4));
    bool in_start=v0<0;
    bool in_before=v1<0;

    if(in_start==in_before) return true;

    std::cout<<"Not the first intersection: ";
    obj->Print();
    std::cout<<"Location "<<obj->Value(ray.Point(dist))<<std::endl;
    std::cout<<"Distance "<<dist<<std::endl;
    std::cout<<" Values "<<v0<<" "<<v1<<std::endl;
    return false;
}

bool has_intersection(Object* obj, const Ray& ray)
{
    // Intersection routine says there is no intersection.  Lets see
    // if we can find one by sampling along the ray to see if the
    // value changes sign.
    double v0=obj->Value(ray.Point(0));
    bool in0=v0<0,ok=true;
    for(double t=1e-2;ok&&t<100;t*=1.01)
    {
        double v1=obj->Value(ray.Point(t));
        bool in1=v1<0;
        if(in0!=in1)
        {
            std::cout<<"Missed intersection: ";
            obj->Print();
            std::cout<<"Distance "<<t<<std::endl;
            std::cout<<"Location "<<ray.Point(t)<<std::endl;
            std::cout<<"Value "<<v1<<std::endl;
            std::cout<<"Distance "<<(t-.01)<<std::endl;
            std::cout<<"Location "<<ray.Point(t-.01)<<std::endl;
            std::cout<<"Value "<<obj->Value(ray.Point(t-.01))<<std::endl;
            return true;
        }
    }
    return false;
}    

bool test_normal(Object* obj, const vec3& loc, const vec3& norm)
{
    bool ok=true;

    // Check if norm is normalized; normalize it anyway.
    if(fabs(norm.magnitude_squared()-1)>1e-6)
    {
        std::cout<<"Normal is not normalized: ";
        obj->Print();
        std::cout<<"Location "<<loc<<std::endl;
        std::cout<<"Normal "<<norm<<std::endl;
        ok=false;
    }
    vec3 n=norm.normalized();

    // To test the normal direction, lets try perturbing loc in the tangential
    // directions and see if Value changes much.
    for(int i=0;i<100;i++)
    {
        vec3 dir=rand_dir(); // Select a random direction
        dir-=dot(dir,n)*n; // project to a tangential direction.
        vec3 dx=dir.normalized()*1e-6; // move tiny amount in tangential direction
        vec3 loc2=loc+dx;
        double val=obj->Value(loc2); // See if we moved off the surface much
        if(fabs(val)>1e-9)
        {
            std::cout<<"Normal is not right: ";
            obj->Print();
            std::cout<<"Normal "<<norm<<std::endl;
            std::cout<<"dx "<<dx<<std::endl;
            std::cout<<"Original Location "<<loc<<std::endl;
            std::cout<<"Test Location "<<(loc+dx)<<std::endl;
            std::cout<<"Test Value "<<val<<std::endl;
            return false;
        }
    }
    return ok;
}

