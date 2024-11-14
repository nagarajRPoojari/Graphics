#ifndef GUI_H
#define GUI_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Gui{
    public:

        Gui(GLFWwindow* window);
        void newFrame();
        void renderFrame();
        void destroy();
};


#endif