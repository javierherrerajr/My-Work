#include "mesh.h"
#include "plane.h"
#include <fstream>
#include <limits>
#include <string>
#include <algorithm>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

Mesh::Mesh(const Parse* parse, std::istream& in)
{
    std::string file;
    in>>name>>file;
    Read_Obj(file.c_str());
}

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e, t;
    vec3 v;
    vec2 u;
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }

        if(sscanf(line.c_str(), "vt %lg %lg", &u[0], &u[1]) == 2)
        {
            uvs.push_back(u);
        }

        if(sscanf(line.c_str(), "f %d/%d %d/%d %d/%d", &e[0], &t[0], &e[1], &t[1], &e[2], &t[2]) == 6)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
            for(int i=0;i<3;i++) t[i]--;
            triangle_texture_index.push_back(t);
        }
    }
    num_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    Hit hit;
    hit.triangle = part;
    for (int i = 0; i < num_parts; i++) {
        Hit test_hit = Intersect_Triangle(ray, i);
        if (test_hit.Valid() && !hit.Valid()) {
            hit.dist = test_hit.dist;
            hit.triangle = i;
            hit.uv = test_hit.uv;
        }
        else if (test_hit.Valid() && test_hit.dist < hit.dist) {
            hit.dist = test_hit.dist;
            hit.triangle = i;
            hit.uv = test_hit.uv;
        }
    }
    if (hit.Valid()) {
        Pixel_Print("intersect test with: ", name, "; hit: ", hit );
    }
    return hit;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const Ray& ray, const Hit& hit) const
{
    assert(hit.triangle==0);
    vec3 a = vertices[triangles[hit.triangle][0]];
    vec3 b = vertices[triangles[hit.triangle][1]];
    vec3 c = vertices[triangles[hit.triangle][2]];

    vec3 n = cross(b - a, c - a).normalized();
    return n;
}

// helper function for area of triangle abc
double triArea(vec3 a, vec3 b, vec3 c, vec3 n) {
    vec3 AB = b - a;
    vec3 AC = c - a;
    return dot(cross(AB, AC), n); 
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
Hit Mesh::Intersect_Triangle(const Ray& ray, int tri) const
{
    Hit hit = Hit();
    hit.triangle = tri;
    vec3 a = vertices[triangles[tri][0]];
    vec3 b = vertices[triangles[tri][1]];
    vec3 c = vertices[triangles[tri][2]];

    double alpha, beta, gamma;

    vec3 n = cross(b - a, c - a).normalized();

    double t = (dot(n, a)-dot(ray.endpoint, n)) / (dot(ray.direction, n));
    if (t > small_t) {
        vec3 p = ray.Point(t);
        // calculate barycentric weights
        alpha = triArea(p, b, c, n) / triArea(a, b, c, n);
        beta = triArea(a, p, c, n) / triArea(a, b, c, n);
        gamma = triArea(a, b, p, n) / triArea(a, b, c, n);
        vec3 weights = {alpha, beta, gamma};
        if (alpha > -weight_tolerance && beta > -weight_tolerance && gamma > -weight_tolerance 
            && alpha < 1 && beta < 1 && gamma < 1) {
            Pixel_Print("mesh " , name, " triangle ", tri, " intersected; weights: ", weights, "; dist ", t);
            hit.dist = t;
            hit.triangle = tri;

            if (triangle_texture_index.size() > 0) {
                double ua = uvs[triangle_texture_index[tri][0]][0];
                double ub = uvs[triangle_texture_index[tri][1]][0];
                double uc = uvs[triangle_texture_index[tri][2]][0];
                double va = uvs[triangle_texture_index[tri][0]][1];
                double vb = uvs[triangle_texture_index[tri][1]][1];
                double vc = uvs[triangle_texture_index[tri][2]][1];

                // calculate uv
                double u = ua + beta * (ub - ua) + gamma * (uc - ua);
                double v = va + beta * (vb - va) + gamma * (vc - va);
                hit.uv = {u,v};
            }
          
            return hit;
        }
        else {
            return Hit();
        }
    }
    else {
        return Hit();
    }

    return hit;
}

std::pair<Box,bool> Mesh::Bounding_Box(int part) const
{
    if(part<0)
    {
        Box box;
        box.Make_Empty();
        for(const auto& v:vertices)
            box.Include_Point(v);
        return {box,false};
    }

    ivec3 e=triangles[part];
    vec3 A=vertices[e[0]];
    Box b={A,A};
    b.Include_Point(vertices[e[1]]);
    b.Include_Point(vertices[e[2]]);
    return {b,false};
}