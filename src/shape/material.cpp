#include <shape/material.hpp>

Material::Material(glm::vec4 color, float df, float sf, float kr, float kt, float n){
    this->color = color;
    this->diffuse_factor = df;
    this->specular_factor = sf;
    this->reflectivity = kr;
    this->transmitivity = kt;
    this->n = n;
}


Material::Material(){}