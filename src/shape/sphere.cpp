#include <shape/sphere.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shape/shape.hpp>
#include <buffers/VBO.hpp>
#include <tuple>
#include <iostream>
#include <utils/utils.hpp>

int Sphere::BUFFER_INDEX = 0;

Sphere::Sphere(glm::vec4 color, float df, float sf, float kr, float kt, float n){
    this->buffer_index = BUFFER_INDEX;
    BUFFER_INDEX++;
    this->radius = 1.0;
    this->material = Material(color, df, sf, kr, kt, n);
}
    
void Sphere::updateBuffer(Shader sh){
    glm::vec3 center = this->getPosition(glfwGetTime());
    
    sh.setUniform3f(this->format("center"),center[0], center[1], center[2]);
    sh.setUniform1f(this->format("radius"),this->radius);
    sh.setUniform4f(this->format("mat.color"),material.color[0], material.color[1], material.color[2], material.color[3]);
    sh.setUniform1f(this->format("mat.kd"), material.diffuse_factor);
    sh.setUniform1f(this->format("mat.ks"), material.specular_factor);
    sh.setUniform1f(this->format("mat.kr"), material.reflectivity);
    sh.setUniform1f(this->format("mat.kt"), material.transmitivity);
    sh.setUniform1f(this->format("mat.n"), material.n);
}

std::string Sphere::format(std::string field){
    std::string i_str = std::to_string(this->buffer_index);
    return std::string("u_spheres[").append(i_str).append("].").append(field);
}

void Sphere::scale(float factor){
    radius*=factor;
}