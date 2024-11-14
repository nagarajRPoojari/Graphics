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
#include <memory>

bool Plane::instantiated = false;
std::unique_ptr<VAO> Plane::vao = nullptr;
std::unique_ptr<EBO> Plane::ebo = nullptr;
std::unique_ptr<VBO> Plane::vbo = nullptr;
std::vector<GLfloat> Plane::vertices; 
std::vector<GLuint> Plane::indices;


Plane::Plane(glm::vec3 objectColor){
    this->objectColor = objectColor;
    initBuffers();   
}

void Plane::draw(Shader sh){
    sh.setUniformMatrix("model", this->model);
    Plane::vao->bind();
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    Plane::vao->unbind();
}


void Plane::initBuffers() {
    if(!Plane::instantiated){
        instantiated = true;
        Plane::vao = std::make_unique<VAO>();
        PlaneUtils::generateBufferData(Plane::vertices, Plane::indices);
        Plane::vbo = std::make_unique<VBO>(Plane::vertices.data(), Plane::vertices.size()*sizeof(GLfloat));
        Plane::ebo = std::make_unique<EBO>(Plane::indices.data(), Plane::indices.size()*sizeof(GLuint));
        Plane::vao->setAttribute(0,3,3,0);
    }
}

