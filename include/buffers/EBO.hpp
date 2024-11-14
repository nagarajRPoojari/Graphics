#ifndef EBO_H
#define EBO_H
#include <GLFW/glfw3.h>
class EBO{
    public:
        GLuint ID;
        GLuint* indices;
        GLsizeiptr size;
        EBO(GLuint* indices, GLsizeiptr size);
        void updateBuffer();
        void bind();
        void unbind();
        void destroy();
};

#endif