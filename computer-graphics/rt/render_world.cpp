#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool enable_acceleration;

Render_World::~Render_World()
{
    for(auto a:all_objects) delete a;
    for(auto a:all_shaders) delete a;
    for(auto a:all_colors) delete a;
    for(auto a:lights) delete a;
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
std::pair<Shaded_Object,Hit> Render_World::Closest_Intersection(const Ray& ray) const
{
    if (Debug_Scope::enable) Debug_Scope::level++;
    Shaded_Object nearest = Shaded_Object();
    Hit hit = Hit();
    double min_dist = __DBL_MAX__, test_dist;
    for (auto object: objects) {
        // get distance from intersection if there is one
        test_dist = object.object->Intersection(ray, 0).dist;
        if (test_dist > 0 && test_dist < min_dist) {
            min_dist = test_dist;
            nearest = object;
            hit.dist = min_dist;
        }
    }
    // closest intersection; obj: S; hit: (dist: 6.31796; triangle: -1; uv: (0 0))
    if (nearest.object) Pixel_Print("closest intersection; obj: ", nearest.object->name, "; hit: ", hit);
    else Pixel_Print("closest intersection; none");

    return {nearest, hit};
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    if (Debug_Scope::enable) Debug_Scope::level++;
    Ray ray;
    ray.endpoint = camera.position;
    vec3 image_point(camera.film_position);

    double x_coordinate = ((camera.max[0]-camera.min[0])/camera.number_pixels[0]) * (pixel_index[0] + 0.5) + camera.min[0];
    double y_coordinate = ((camera.max[1]-camera.min[1])/camera.number_pixels[1]) * (pixel_index[1] + 0.5) + camera.min[1];

    image_point += x_coordinate * camera.horizontal_vector + y_coordinate * camera.vertical_vector;
    ray.direction = (image_point - ray.endpoint).normalized();

    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth) const
{
    if (Debug_Scope::enable) Debug_Scope::level++;
    Pixel_Print("cast ray ", ray);
    vec3 color = {0,0,0};

    if (recursion_depth > recursion_depth_limit) {
        Pixel_Print("ray too deep; return black");
        return color;
    }

    std::pair<Shaded_Object, Hit> pair = Closest_Intersection(ray);
    Hit hit = pair.second;
    Shaded_Object object = pair.first;
    vec3 intersection = ray.endpoint + pair.second.dist * ray.direction;

                  // shade that pixel babyyyy
    if (Debug_Scope::enable) Debug_Scope::level--;
    if (hit.Valid()) {
        vec3 normal = object.object->Normal(ray, hit);
        Pixel_Print("call Shade_Surface with location: ", intersection, "; normal: ", normal);
        color = object.shader->Shade_Surface(*this, ray, hit, intersection, normal, recursion_depth);
    } 

    else {
        color = background_shader ?  background_shader->Shade_Surface(*this, ray, hit, intersection, intersection, recursion_depth) : color;
        if (!background_shader) Pixel_Print("no background; return black");
    }
    
    return color;
}