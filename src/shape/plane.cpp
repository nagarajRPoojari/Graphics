#include <shape/plane.hpp>
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

int Plane::BUFFER_INDEX = 0;

Plane::Plane(
    glm::vec3 size, 
    glm::vec3 normal, 
    glm::vec4 color, 
    float df, float sf, float kr, float kt, float n
){
    this->buffer_index = BUFFER_INDEX;
    BUFFER_INDEX++;
    this-> size = size;
    this-> normal = normal;
    this-> material = Material(color,df,sf,kr,kt,n);
}
    
void Plane::updateBuffer(Shader sh){
    glm::vec3 center = this->getPosition();
    sh.setUniform3f(this->format("center"),center[0], center[1], center[2]);
    sh.setUniform3f(this->format("size"),size[0], size[1], size[2]);
    sh.setUniform3f(this->format("normal"),normal[0], normal[1], normal[2]);
    sh.setUniform4f(this->format("mat.color"),material.color[0], material.color[1], material.color[2], material.color[3]);
    sh.setUniform1f(this->format("mat.kd"), material.diffuse_factor);
    sh.setUniform1f(this->format("mat.ks"), material.specular_factor);
    sh.setUniform1f(this->format("mat.kr"), material.reflectivity);
    sh.setUniform1f(this->format("mat.kt"), material.transmitivity);
    sh.setUniform1f(this->format("mat.n"), material.n);
}

std::string Plane::format(std::string field){
    std::string i_str = std::to_string(this->buffer_index);
    return std::string("u_planes[").append(i_str).append("].").append(field);
}
