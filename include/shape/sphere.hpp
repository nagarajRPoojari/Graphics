#ifndef SPHERE_H
#define SPHERE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shape/shape.hpp>
#include <buffers/VBO.hpp>
#include <buffers/EBO.hpp>
#include <buffers/VAO.hpp>
#include <vector>
#include <utils/utils.hpp>
#include <memory>

class Sphere : public Shape{
    private:
        static bool instantiated;

    public:
        float radius;

        Sphere(float radius, glm::vec3 objectColor);
};

#endif