#ifndef SCREEN_H
#define SCREEN_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shape/shape.hpp>
#include <buffers/VBO.hpp>
#include <buffers/EBO.hpp>
#include <utils/utils.hpp>
#include <vector>

class Screen {
    private:
        static bool instantiated;
        
    public:
        static std::vector<GLfloat> vertices;
        static std::vector<GLuint> indices;
        static std::unique_ptr<EBO> ebo;
        static std::unique_ptr<VBO> vbo;
        static std::unique_ptr<VAO> vao;

        Screen();
        void initBuffers();
        void draw(Shader sh);

};

#endif