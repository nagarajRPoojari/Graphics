#include <shape/light.hpp>
#include <string>

int Light::BUFFER_INDEX = 0;

Light::Light(glm::vec4 color, glm::vec3 dir, float strength){
    this->color = color;
    this->dir = dir;
    this->ray = dir*strength;
    this->mag = strength;
    this->buffer_index = BUFFER_INDEX;
    this->BUFFER_INDEX++;
}

void Light::updateBuffer(Shader sh){
    sh.setUniform3f(this->format("dir"),dir[0], dir[1], dir[2]);
    sh.setUniform3f(this->format("ray"),ray[0], ray[1], ray[2]);
    sh.setUniform4f(this->format("color"),color[0], color[1], color[2], color[3]);
    sh.setUniform1f(this->format("mag"),mag);
}

const char* Light::format(std::string field){
    std::string i_str = std::to_string(this->buffer_index);
    return std::string("u_lights[").append(i_str).append("]").append(field).c_str();
}