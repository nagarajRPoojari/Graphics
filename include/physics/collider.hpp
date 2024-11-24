#ifndef COLLIDER_H
#define COLLIDER_H

#include <shape/shape.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>
#include <shape/sphere.hpp>
#include <shape/plane.hpp>

class Collider{
    public:
        std::vector<Shape*> objects;

        Collider(std::vector<Shape*> objects);
        void collide();
        void sphere_sphere(Sphere& s1, Sphere& s2);
        void plane_sphere(Sphere& s, Plane& p);

};






#endif