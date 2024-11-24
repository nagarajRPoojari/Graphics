#ifndef CUBEMAP_H
#define CUBEMAP_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CubeMap{
    public:
        GLuint ID;
	    unsigned int cubemapTexture;
        unsigned int skyboxVAO; 
        CubeMap();
        void activate();
        void bind();
};


#endif
