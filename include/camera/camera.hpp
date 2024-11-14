#ifndef CAMERA_H
#define CAMERA_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
    public:
        GLFWwindow* window;
        glm::mat4 view;
        bool disableCamera;
        Camera(GLFWwindow *window, bool disableCamera);

        static void mouse_callback(GLFWwindow *window,double xpos, double ypos);
        int processFrame();

};


#endif