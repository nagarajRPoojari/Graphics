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
    glm::vec3 normal, 
    glm::vec4 color, 
    float df, float sf, float kr, float kt, float n
){
    this->buffer_index = BUFFER_INDEX;
    BUFFER_INDEX++;
    this-> normal = normal;
    this-> material = Material(color,df,sf,kr,kt,n);
}
    
void Plane::updateBuffer(Shader sh){
    glm::vec3 center = this->getPosition();
    glm::vec3 size = this->getSize();
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

glm::vec3 Plane::getSize(){
    return glm::vec3(
        glm::length(glm::vec3(model[0][0], model[1][0], model[2][0])),  // s_x
        glm::length(glm::vec3(model[0][1], model[1][1], model[2][1])),  // s_y
        glm::length(glm::vec3(model[0][2], model[1][2], model[2][2]))   // s_z
    );
}