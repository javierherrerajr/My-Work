#include "transparent_shader.h"
#include "parse.h"
#include "ray.h"
#include "render_world.h"

Transparent_Shader::
Transparent_Shader(const Parse* parse,std::istream& in)
{
    in>>name>>index_of_refraction>>opacity;
    shader=parse->Get_Shader(in);
    assert(index_of_refraction>=1.0);
}



// Use opacity to determine the contribution of this->shader and the Schlick
// approximation to compute the reflectivity.  This routine shades transparent
// objects such as glass.  Note that the incoming and outgoing indices of
// refraction depend on whether the ray is entering the object or leaving it.
// You may assume that the object is surrounded by air with index of refraction
// 1.
vec3 Transparent_Shader::
Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const
{
    vec3 v = (intersection_point - ray.endpoint).normalized();
    vec3 r = 2.0 * (dot(v, normal)) * normal - v;
    r = r.normalized();
    double incident_angle, r0, reflectivity;
    if (dot(r, normal) < 0) {
        incident_angle = asin(cross(v, -normal).magnitude());
        r0 = pow((((index_of_refraction) - 1) / (1 + index_of_refraction)), 2);
    }
    else {
        incident_angle = asin(cross(normal, v).magnitude());
        r0 = pow((((1/index_of_refraction)-1) / (1 + (1/index_of_refraction))), 2);
    }

    reflectivity = r0 + (1 - r0) * (pow((1 - cos(incident_angle)), 5));
    Ray reflected_ray(intersection_point, -r);

    vec3 reflected_color = render_world.Cast_Ray(reflected_ray, ++recursion_depth);
    Pixel_Print("reflected ray: ", reflected_ray, "reflected color: ", reflected_color);
    
    vec3 object_color = this->shader->Shade_Surface(render_world, ray, hit, intersection_point, normal, recursion_depth);

    Ray transmitted_ray(intersection_point, {0,0,0});
    double descriminant;
    vec3 color, transmitted_color;
    if (dot(r, normal) < 0)
    {
        descriminant = 1 - (1 / index_of_refraction) * (1 / index_of_refraction) * (1 - (pow(dot(normal, v), 2)));
        if (descriminant > 0) {
            // Pixel_Print("entering sphere");
            transmitted_ray.direction = -sqrt(descriminant) * normal +
                (1 / index_of_refraction) * (v - (dot(v, normal)) * normal);
            transmitted_color = render_world.Cast_Ray(transmitted_ray, ++recursion_depth);

            color = opacity * object_color + (1 - opacity) * (reflectivity * reflected_color + (1 - reflectivity) * transmitted_color);
            Pixel_Print("transmitted ray: ", transmitted_ray, " transmitted color: ", transmitted_color,
                        " Schlick reflectivity: ", reflectivity, " combined color: ", color);
        }
        else {
            Pixel_Print("complete internal reflection");
            color = reflected_color;
        }
    }
    else {
        descriminant = 1 - (index_of_refraction) * (index_of_refraction) * (1 - (pow(dot(-normal, v), 2)));
        if (descriminant > 0) {
            // Pixel_Print("exiting sphere");
            transmitted_ray.direction = -sqrt(descriminant) * -normal +
                (index_of_refraction) * (v - (dot(v, -normal)) * -normal);
            transmitted_color = render_world.Cast_Ray(transmitted_ray, ++recursion_depth);

            color = opacity * object_color + (1 - opacity) * (reflectivity * reflected_color + (1 - reflectivity) * transmitted_color);
            Pixel_Print("transmitted ray: ", transmitted_ray, " transmitted color: ", transmitted_color,
                        " Schlick reflectivity: ", reflectivity, " combined color: ", color);
        }
        else  {
            Pixel_Print("complete internal reflection");
            color=reflected_color;
        }
    }

    return color;
}
