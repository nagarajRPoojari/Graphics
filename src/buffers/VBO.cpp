#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <buffers/VBO.hpp>

VBO::VBO(GLfloat* vertices, GLsizeiptr size){
    glGenBuffers(1, &ID);
    this->vertices = vertices;
    this->size = size;
    this->updateBuffer();
}

void VBO::updateBuffer(){
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy(){
    glDeleteBuffers(1, &ID);
}