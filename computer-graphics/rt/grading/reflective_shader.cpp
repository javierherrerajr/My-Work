#include "reflective_shader.h"
#include "parse.h"
#include "ray.h"
#include "render_world.h"

Reflective_Shader::Reflective_Shader(const Parse* parse,std::istream& in)
{
    in>>name;
    shader=parse->Get_Shader(in);
    in>>reflectivity;
    reflectivity=std::max(0.0,std::min(1.0,reflectivity));
}

vec3 Reflective_Shader::
Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const
{
    vec3 object_color = this->shader->Shade_Surface(render_world, ray, hit, intersection_point, normal, recursion_depth);

    vec3 v = ray.endpoint - intersection_point;
    v = v.normalized();
    vec3 r = 2.0 * (dot(v, normal)) * normal - v;
    r = r.normalized();
    Ray reflected_ray(intersection_point, r);

    vec3 reflected_color = render_world.Cast_Ray(reflected_ray, ++recursion_depth);

    vec3 color = object_color + reflectivity * (reflected_color - object_color);
    Pixel_Print("reflected ray: ", reflected_ray, "; reflected color: ", reflected_color,
        "; object color: ", object_color, "; final color: ", color);
    
    return color;
}
