#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <buffers/VAO.hpp>
#include <iostream>

VAO::VAO(){
    glGenVertexArrays(1,&ID);
    this->bind();
}

void VAO::setAttribute(GLuint layout, int size, int slide, int offset){
    glVertexAttribPointer(layout,size,GL_FLOAT, GL_FALSE, slide*sizeof(float), (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(layout);
}

void VAO::bind(){
    glBindVertexArray(ID);
}

void VAO::unbind(){
    glBindVertexArray(0);
}

void VAO::destroy(){
    glDeleteVertexArrays(1, &ID);
}