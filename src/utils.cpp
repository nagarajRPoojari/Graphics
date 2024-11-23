#include <utils/utils.hpp>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>
#include <iostream>

namespace Config{
    std::string TITLE;
    int WINDOW_WIDTH, WINDOW_HEIGHT;

    void loadConfig(){
        YAML::Node config = YAML::LoadFile("/home/nagaraj/Desktop/experiments/learn-glfw/config.yml");

        if (config["title"]) {
            TITLE = config["title"].as<std::string>();
        } else {
            throw std::runtime_error("Missing 'title' field in config.");
        }

        if (config["window"] && config["window"]["width"]) {
            WINDOW_WIDTH = config["window"]["width"].as<int>();
        } else {
            throw std::runtime_error("Missing 'window.width' field in config.");
        }
        if (config["window"] && config["window"]["height"]) {
            WINDOW_HEIGHT = config["window"]["height"].as<int>();
        } else {
            throw std::runtime_error("Missing 'window.height' field in config.");
        }
    }
}
const char* load_file(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + std::string(filename));
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    std::string fileContent = buffer.str();

    char* cstr = new char[fileContent.size() + 1]; 
    std::strcpy(cstr, fileContent.c_str());
    
    return cstr; 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::TITLE.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    return window;
}


void SphereUtils::generateBufferData(int lats, int longs, std::vector<GLfloat>& vertex_b, std::vector<GLuint>& index_b){
    int indicator = 0;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    for(int i = 0; i <= lats; i++) {
        float lat = glm::pi<float>() * (-0.5f + (float)(i) / lats);
        float z = sin(lat);
        float rz = cos(lat);
        for (int j = 0; j <= longs; j++) {
            float lng = 2 * glm::pi<float>() * (float)(j) / longs;
            float x = cos(lng) * rz; 
            float y = sin(lng) * rz; 
            vertices.push_back(x); 
            vertices.push_back(y); 
            vertices.push_back(z);

            indicator++;
            if (i < lats && j < longs) {
                GLuint first = (i * (longs + 1)) + j;
                GLuint second = first + longs + 1;
                if (i != 0) {
                    indices.push_back(first);
                    indices.push_back(second);
                    indices.push_back(first + 1);
                }
                if (i != (lats - 1)) {
                    indices.push_back(second);
                    indices.push_back(second + 1);
                    indices.push_back(first + 1);
                }
            }
        }
    }
    vertex_b.resize(vertices.size());
    index_b.resize(indices.size());
    std::copy(vertices.begin(), vertices.end(), vertex_b.begin());
    std::copy(indices.begin(), indices.end(), index_b.begin());
}


void ScreenUtils::generateBufferData(std::vector<GLfloat>& vertex_b, std::vector<GLuint>& index_b) {
    vertex_b.clear();  
    index_b.clear();
    GLfloat vertices_array[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };
    
    GLuint indices_array[] = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };
    
    // Resize the output vectors directly to fit the data
    vertex_b.resize(sizeof(vertices_array) / sizeof(vertices_array[0]));
    index_b.resize(sizeof(indices_array) / sizeof(indices_array[0]));
    
    // Copy data into the output vectors
    std::copy(std::begin(vertices_array), std::end(vertices_array), vertex_b.begin());
    std::copy(std::begin(indices_array), std::end(indices_array), index_b.begin());
}


