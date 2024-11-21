#ifndef SPHERE_H
#define SPHERE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shape/shape.hpp>
#include <shape/material.hpp>
#include <buffers/VBO.hpp>
#include <buffers/EBO.hpp>
#include <buffers/VAO.hpp>
#include <vector>
#include <utils/utils.hpp>
#include <memory>

class Sphere : public Shape{
    public:
        static int BUFFER_INDEX;
        int buffer_index;
        
        float radius;
        Material material;
        Sphere(float radius, glm::vec4 color, float df, float sf, float kr, float kt, float n);
        void updateBuffer(Shader sh);
        std::string format(std::string field);
};

#endif