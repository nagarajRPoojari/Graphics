#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture{
    public:
        GLuint ID;
        Texture(const char *path);
        void activate();
        void bind();
};


#endif
