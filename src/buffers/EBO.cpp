#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <buffers/EBO.hpp>


EBO::EBO(GLuint* indices, GLsizeiptr size){
    glGenBuffers(1, &ID);
    this->indices = indices;
    this->size = size;
    this->updateBuffer();
}

void EBO::updateBuffer(){
    this->bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy(){
    glDeleteBuffers(1, &ID);
}