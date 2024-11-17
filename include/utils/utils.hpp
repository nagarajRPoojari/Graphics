#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <yaml-cpp/yaml.h>
#include <tuple>

const char* load_file(const char* filename);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* initWindow();


namespace Config {
    extern std::string TITLE;
    extern std::string VERSION;
    extern int WINDOW_HEIGHT, WINDOW_WIDTH;
    void loadConfig();
}

namespace SphereUtils{ 
    void generateBufferData(int lats, int longs, std::vector<GLfloat>& vertex_b, std::vector<GLuint>& index_b);
}

namespace ScreenUtils{ 
    void generateBufferData(std::vector<GLfloat>& vertex_b, std::vector<GLuint>& index_b);
}


namespace CleanUp{    
    inline void clean() {
    }
    template<typename T, typename... Args>
    inline void clean(const T& first, const Args&... args) {
        first->destroy();
        clean(args...);
    }
}

#endif 