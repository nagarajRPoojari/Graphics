#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <shader/shader.hpp>
#include <utils/utils.hpp>
#include <filesystem>
#include <stdexcept>
#include <regex>

Shader::Shader(){
    const char* vertexFilename = "../assets/vertex.glsl";
    const char* fragmentFolder = "../assets/fragment";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSrc = load_file(vertexFilename);

    const GLchar * vertexSrc = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSrc = load_shader(fragmentFolder);

    const GLchar * fragmentSrc = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);


    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);


    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate(){
    glUseProgram(ID);
}

void Shader::deactivate(){
    glUseProgram(0);
    glDeleteProgram(ID);
}


std::string Shader::load_shader(const std::string& dir_path) {
    std::string combined_content;
    
    try {
        std::string header_path = dir_path + "/header.glsl";
        std::string header_content = load_file(header_path.c_str());
        
        std::regex include_regex(R"(#include\s*<(.*)>)");
        std::smatch match;
        
        std::vector<std::string> included_files;
        std::istringstream header_stream(header_content);
        std::string line;
        
        while (std::getline(header_stream, line)) {
            if (std::regex_search(line, match, include_regex)) {
                std::string included_file = match[1].str(); 
                included_files.push_back(included_file);
            }
        }
        for (const auto& file : included_files) {
            std::string included_file_path = dir_path + "/" + file;
            combined_content += load_file(included_file_path.c_str());
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
    
    std::cout << combined_content << std::endl;

    return combined_content;
}