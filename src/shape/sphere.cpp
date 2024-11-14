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

bool Sphere::instantiated = false;
std::unique_ptr<VAO> Sphere::vao = nullptr;
std::unique_ptr<EBO> Sphere::ebo = nullptr;
std::unique_ptr<VBO> Sphere::vbo = nullptr;
std::vector<GLfloat> Sphere::vertices; 
std::vector<GLuint> Sphere::indices;


Sphere::Sphere(float radius, glm::vec3 objectColor){
    this->objectColor = objectColor;
    this->radius = radius;
    initBuffers();   
    this->scale(glm::vec3(radius));
}

void Sphere::draw(Shader sh){
    sh.setUniformMatrix("model", this->model);
    Sphere::vao->bind();
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    Sphere::vao->unbind();
}


void Sphere::initBuffers() {
    if(!Sphere::instantiated){
        instantiated = true;
        Sphere::vao = std::make_unique<VAO>();
        SphereUtils::generateBufferData(80,80, Sphere::vertices, Sphere::indices);
        Sphere::vbo = std::make_unique<VBO>(Sphere::vertices.data(), Sphere::vertices.size()*sizeof(GLfloat));
        Sphere::ebo = std::make_unique<EBO>(Sphere::indices.data(), Sphere::indices.size()*sizeof(GLuint));
        Sphere::vao->setAttribute(0,3,3,0);
    }
}
