#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material{
    public:
        glm::vec4 color;
        float diffuse_factor;
        float specular_factor;
        float reflectivity;
        float transmitivity;
        float n;

        Material(glm::vec4 color, float df, float sf, float kr, float kt, float n);
        Material();
};

#endif

