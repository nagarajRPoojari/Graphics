#ifndef VBO_H
#define VBO_H
#include <GLFW/glfw3.h>

class VBO{
    public:
        GLuint ID;
        GLfloat* vertices;
        GLsizeiptr size;
        VBO(GLfloat* vertices, GLsizeiptr size);
        void updateBuffer();
        void bind();
        void unbind();
        void destroy();
};

#endif