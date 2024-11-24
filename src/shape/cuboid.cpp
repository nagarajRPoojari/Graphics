#include <shape/cuboid.hpp>
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

int Cuboid::BUFFER_INDEX = 0;

Cuboid::Cuboid(
    glm::vec4 color, 
    float df, float sf, float kr, float kt, float n
){
    this->buffer_index = BUFFER_INDEX;
    BUFFER_INDEX++;
    this-> material = Material(color,df,sf,kr,kt,n);
}
    
void Cuboid::updateBuffer(Shader sh){
    glm::vec3 center = this->getPosition(glfwGetTime());
    glm::vec3 size = this->getSize();
    sh.setUniform3f(this->format("center"),center[0], center[1], center[2]);
    sh.setUniform3f(this->format("size"),size[0], size[1], size[2]);
    sh.setUniform4f(this->format("mat.color"),material.color[0], material.color[1], material.color[2], material.color[3]);
    sh.setUniform1f(this->format("mat.kd"), material.diffuse_factor);
    sh.setUniform1f(this->format("mat.ks"), material.specular_factor);
    sh.setUniform1f(this->format("mat.kr"), material.reflectivity);
    sh.setUniform1f(this->format("mat.kt"), material.transmitivity);
    sh.setUniform1f(this->format("mat.n"), material.n);
}

std::string Cuboid::format(std::string field){
    std::string i_str = std::to_string(this->buffer_index);
    return std::string("u_cuboids[").append(i_str).append("].").append(field);
}

glm::vec3 Cuboid::getSize(){
    glm::vec3 scale(
        glm::length(glm::vec3(model[0].x, model[1].x, model[2].x)), 
        glm::length(glm::vec3(model[0].y, model[1].y, model[2].y)), 
        glm::length(glm::vec3(model[0].z, model[1].z, model[2].z))  
    );
    return scale;
}