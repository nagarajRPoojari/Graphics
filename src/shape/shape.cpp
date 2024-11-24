#include <shape/shape.hpp>
#include <iostream>

glm::vec3 g(0,-1.8,0);

Shape::Shape(){
    this->velocity = glm::vec3(0,0,0);
    this->time = 0.0f;
    this->model = glm::mat4(1.0f);
}

Shape* Shape::rotate(float angle, glm::vec3 axis){
    this->model =  glm::rotate(this->model, glm::radians(angle), axis); 
    updatePosition();
    return this;
}

Shape* Shape::tarnslate(glm::vec3 position){
    this->model =  glm::translate(this->model, position);
    updatePosition();
    return this;
}

Shape* Shape::scale(glm::vec3 factors){
    this->model =  glm::scale(this->model, factors);
    updatePosition();
    return this;
}
glm::vec3 Shape::getPosition(float currentTime) {
    float t = currentTime - time;

    if (t > 0) {
        glm::vec3 u = velocity; 
        velocity = u + g * t;
        position += u * t + 0.5f * g * t * t;
        time = currentTime;
    }
    return position;
}

void Shape::updatePosition(){
    position = glm::vec3(model[3][0], model[3][1], model[3][2]);
}