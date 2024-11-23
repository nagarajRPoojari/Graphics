#ifndef PLANE_H
#define PLANE_H
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


class Plane : public Shape{
    public:
        static int BUFFER_INDEX;
        int buffer_index;

        glm::vec3 size;
        glm::vec3 normal;
        Material material;
        Plane(
            glm::vec3 normal, 
            glm::vec4 color, 
            float df, 
            float sf, 
            float kr, 
            float kt, 
            float n
        );
        void updateBuffer(Shader sh);
        std::string format(std::string field);
        glm::vec3 getSize();
};

#endif