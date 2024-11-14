#ifndef VAO_H
#define VAO_H
#include <GLFW/glfw3.h>
#include <buffers/VBO.hpp>
#include <buffers/EBO.hpp>

class VAO{
    public:
        GLuint ID;
        VAO();
        void setAttribute(GLuint layout, int size,int slide, int offset);
        void bind();
        void unbind();
        void destroy();
};

#endif