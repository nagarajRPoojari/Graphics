#include <screen/screen.hpp>
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

bool Screen::instantiated = false;
std::unique_ptr<VAO> Screen::vao = nullptr;
std::unique_ptr<EBO> Screen::ebo = nullptr;
std::unique_ptr<VBO> Screen::vbo = nullptr;
std::vector<GLfloat> Screen::vertices; 
std::vector<GLuint> Screen::indices;


Screen::Screen(){
    initBuffers();   
}

void Screen::draw(Shader sh){
    Screen::vao->bind();
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    Screen::vao->unbind();
}


void Screen::initBuffers() {
    if(!Screen::instantiated){
        instantiated = true;
        Screen::vao = std::make_unique<VAO>();
        ScreenUtils::generateBufferData(Screen::vertices, Screen::indices);
        Screen::vbo = std::make_unique<VBO>(Screen::vertices.data(), Screen::vertices.size()*sizeof(GLfloat));
        Screen::ebo = std::make_unique<EBO>(Screen::indices.data(), Screen::indices.size()*sizeof(GLuint));
        Screen::vao->setAttribute(0,3,5,0);
        Screen::vao->setAttribute(1,2,5,3);
    }
}

