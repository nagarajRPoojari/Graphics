#include <shape/shape.hpp>
#include <iostream>



Shape::Shape(){
    this->model = glm::mat4(1.0f);
}

Shape* Shape::rotate(float angle, glm::vec3 axis){
    this->model =  glm::rotate(this->model, glm::radians(angle), axis); 
    return this;
}

Shape* Shape::tarnslate(glm::vec3 position){
    this->model =  glm::translate(this->model, position);
    return this;
}

Shape* Shape::scale(glm::vec3 factors){
    this->model =  glm::scale(this->model, factors);
    return this;
}

glm::vec4 Shape::getPosition(){
    return this->model[3];
}
