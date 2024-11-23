#ifndef SHAPE_H
#define SHAPE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <buffers/VAO.hpp>
#include <buffers/EBO.hpp>
#include <shader/shader.hpp>



class Shape{
    public:
        glm::mat4 model;
        Shape();

        Shape* rotate(float angle, glm::vec3 axis);
        Shape* tarnslate(glm::vec3 position);     
        Shape* scale(glm::vec3 factors);  
        glm::vec3 getPosition();        
};
#endif