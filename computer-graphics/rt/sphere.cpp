#include "sphere.h"
#include "ray.h"

Sphere::Sphere(const Parse* parse, std::istream& in)
{
    in>>name>>center>>radius;
}

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    Hit hit = Hit();
    vec3 w = ray.endpoint - center;
    vec3 d = ray.direction;
    double descriminant = (pow(dot(d, w), 2) - dot(d,d) * (dot(w,w) - (radius * radius)));
    if (descriminant < 0) {
        Pixel_Print("no intersect with ", this->name);
    }
    double t1 = (-dot(d, w) + sqrt(descriminant));
    double t2 = (-dot(d, w) - sqrt(descriminant)); 
    double t = (t1 > small_t) ? ((t2 > small_t) ? std::min(t1, t2) : t1) : t2;
    if (this->name == "St") {
        Pixel_Print("Testing intersect with St: ", "descriminant: ", descriminant, " t1: ", t1, " t2: ", t2, " t: ", t);
    }
    if (t > small_t)
    {
        hit.dist = t;
        Pixel_Print("intersect test with ", this->name, "; hit: ", hit);
    }
    return hit;
}

vec3 Sphere::Normal(const Ray& ray, const Hit& hit) const
{
    vec3 normal;
    vec3 intsct = ray.Point(hit.dist);
    normal = (intsct - center) / radius;

    // Pixel_Print("Calculating normal with intersection: ", insct, " and ray: ", ray);
    // Pixel_Print("Normal is: ", normal);
    return normal;
}

std::pair<Box,bool> Sphere::Bounding_Box(int part) const
{
    return {{center-radius,center+radius},false};
}
