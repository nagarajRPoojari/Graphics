#include<camera/camera.hpp>

glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse=false;
float lastX = 400;
float lastY = 300;
float yaw=-90.0f; 
float pitch=0.0f;

Camera::Camera(GLFWwindow* window, bool disableCamera){
    
    this->window = window;
    this->view= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));

    if(!disableCamera){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
        glfwSetCursorPosCallback(window, this->mouse_callback);
    }
};

void Camera::mouse_callback(GLFWwindow *window,double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    direction = glm::normalize(direction);
    glm::vec3 cameraRight(-direction.z,0.0,direction.x);
    cameraUp = glm::cross(cameraRight, direction);
    cameraFront = direction;
}

int Camera::processFrame(){
    const float cameraSpeed = 0.05f; 
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        return 1;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront; 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    }
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return 0;
}

