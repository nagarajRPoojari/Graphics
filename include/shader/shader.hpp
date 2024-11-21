#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader{
    public:
        GLuint ID;
        Shader(const char* vertexFilename, const char* fragmentFilename);
        void activate();
        void deactivate();

        template <typename T>
        void setUniformMatrix(const GLchar *variable, T value){
            glUniformMatrix4fv(glGetUniformLocation(ID, variable), 1, GL_FALSE, glm::value_ptr(value));
        }

        template <typename T>
        void setUniform3fv(const GLchar *variable, T value){
            glUniform3fv(glGetUniformLocation(ID, variable), 1, glm::value_ptr(value));
        }
        
        template <typename T>
        void setUniform1f(std::string variable, T value){
            glUniform1f(glGetUniformLocation(ID, variable.c_str()), value);
        }

        template <typename T>
        void setUniform4f(std::string variable, T a, T b, T c, T d){
            glUniform4f(glGetUniformLocation(ID, variable.c_str()),a,b,c,d);
        }

        template <typename T>
        void setUniform3f(std::string variable, T  a, T b, T c){
            glUniform3f(glGetUniformLocation(ID, variable.c_str()),a,b,c);
        }
};


#endif