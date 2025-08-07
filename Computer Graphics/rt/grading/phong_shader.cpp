#include "light.h"
#include "parse.h"
#include "object.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

Phong_Shader::Phong_Shader(const Parse* parse,std::istream& in)
{
    in>>name;
    color_ambient=parse->Get_Color(in);
    color_diffuse=parse->Get_Color(in);
    color_specular=parse->Get_Color(in);
    in>>specular_power;
}

vec3 Phong_Shader::
Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const
{

    if (Debug_Scope::enable) Debug_Scope::level++;
    vec3 color = render_world.ambient_color ? render_world.ambient_color->Get_Color({}) * color_ambient->Get_Color({}) * render_world.ambient_intensity :
        color_ambient->Get_Color({}) * render_world.ambient_intensity;
    Pixel_Print("ambient: ", color);
    
    vec3 e = ray.endpoint - intersection_point;
    e = e.normalized();
    for (size_t i = 0; i < render_world.lights.size(); i++) {

        vec3 l = render_world.lights[i]->position - intersection_point;
        if (render_world.enable_shadows) {
            Ray rayLight = Ray(intersection_point, l.normalized());
            std::pair<Shaded_Object, Hit> closest = render_world.Closest_Intersection(rayLight);
            // light L0 visible; closest object on ray too far away (light dist: 7.42643; object dist: inf)
            if (Debug_Scope::enable) Debug_Scope::level--;


            if (closest.second.dist > small_t && closest.second.dist < l.magnitude()) Pixel_Print("light ", render_world.lights[i]->name, " not visible; obscured by object ", closest.first.object->name,
                " at location: ", closest.second);
            else {
                Pixel_Print("light ", render_world.lights[i]->name, " visible; ", "closest object on ray too far away (light dist: ", 
                l.magnitude(), " object dist: ", closest.second.dist);
                vec3 intensity = render_world.lights[i]->Emitted_Light(l);
                l = l.normalized();

                // Pixel_Print("direction to light: ", l);
                Pixel_Print( render_world.lights[i]->name, " Intensity? : ", intensity);
                
                vec3 r = -l + (2.0 * (dot(normal, l)) * normal);
                // Pixel_Print(i.normalized(),  dot(normal, i.normalized()));
                vec3 diffuse = intensity * color_diffuse->Get_Color({}) * std::max(0.0, dot(normal, l));
                vec3 specular = intensity * color_specular->Get_Color({}) * pow(std::max(0.0, dot(e, r)), specular_power);

                Pixel_Print("shading for light ", render_world.lights[i]->name, ": diffuse: ", diffuse, "; specular: ", specular);
                color += diffuse + specular;
            }

        }
        else {
            vec3 intensity = render_world.lights[i]->Emitted_Light(l);
            l = l.normalized();

            // Pixel_Print("direction to light: ", l);
            // Pixel_Print( render_world.lights[i]->name, " Intensity? : ", intensity);

            vec3 r = -l + (2.0 * (dot(normal, l)) * normal);
            // Pixel_Print(i.normalized(),  dot(normal, i.normalized()));
            vec3 diffuse = intensity * color_diffuse->Get_Color({}) * std::max(0.0, dot(normal, l));
            vec3 specular = intensity * color_specular->Get_Color({}) * pow(std::max(0.0, dot(e, r)), specular_power);

            Pixel_Print("shading for light ", render_world.lights[i]->name, ": diffuse: ", diffuse, "; specular: ", specular);
            color += diffuse + specular;
        }
    }
    Pixel_Print("final color ", color);
    if (Debug_Scope::enable) Debug_Scope::level--;

    //ambient + diffuse + specular
    // color = this->color_ambient + color_diffuse + this->color_specular;
    return color;
}
