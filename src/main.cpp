
#include <dependencies.hpp>

int main() {
    Config::loadConfig();
    GLFWwindow *window = initWindow();

    Camera camera(window);
    Sphere sphere1(0.1,glm::vec3(0.7f));
    Sphere sphere2(0.1,glm::vec3(0.7f));
    sphere2.tarnslate(glm::vec3(-1.0f,-10.0f,1.0f));
    sphere1.tarnslate(glm::vec3(-1.0f,1.0f,1.0f));


    Plane plane(glm::vec3(0.4f));
    //plane.scale(glm::vec3(10.0f));
    Shader sh("../assets/vertex.glsl", "../assets/fragment.glsl");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                            (float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.1f, 100.0f);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(camera.processFrame()) break;  
        sh.setUniformMatrix("view", camera.view);
        sh.setUniformMatrix("projection", projection);

        sh.activate();


        sphere1.draw(sh);

        sphere2.draw(sh);
        plane.draw(sh);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    CleanUp::clean(Sphere::vao,Sphere::vbo, Sphere::ebo, Plane::vao, Plane::vbo, Plane::ebo);    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}