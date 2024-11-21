
#include <dependencies.hpp>


int main() {
    Config::loadConfig();
    GLFWwindow *window = initWindow();

    Camera camera(window,false);
    Screen back;



    Shader sh("../assets/vertex.glsl", "../assets/fragment.glsl");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                            (float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.1f, 100.0f);

    Plane plane = Plane(glm::vec3(1.0f,0.0f,1.0f),glm::vec3(0.0f,1.0f,1.0f),glm::vec4(0.3,0.0,0.2,1.0), 1.0, 16.0, 0.2, 0.0, 1.0);
    plane.scale(glm::vec3(15.0f,0.0f,15.0f));
    Sphere sphere1 = Sphere(1.0f, glm::vec4(1.0,0.1,0.1,1.0), 1.0, 16.0, 0.5, 0.0, 2.0);
    Sphere sphere2 = Sphere(1.0f, glm::vec4(0.3,0.3,1.0,1.0), 1.0, 16.0, 0.1, 0.0, 2.0);
    sphere1.tarnslate(glm::vec3(1.0f,1.0f,1.0f));
    sphere2.tarnslate(glm::vec3(-1.0f,-1.0f,-1.0f));
    
    Light light = Light(glm::vec4(0.7f,0.7f,0.7f,1.0f),glm::vec3(10.0f), 1.0f);
    


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(camera.processFrame()) break;
        sh.activate();

        glUniform1f(glGetUniformLocation(sh.ID, "iTime"), glfwGetTime());
        glUniform3f(glGetUniformLocation(sh.ID, "iResolution"), (float)Config::WINDOW_WIDTH, (float)Config::WINDOW_HEIGHT, 0.0f);
       
        glm::vec3 cameraPos(camera.view[3][0], camera.view[3][1], camera.view[3][2]);

        glm::vec3 right(camera.view[0][0], camera.view[0][1], camera.view[0][2]); // Right vector (X axis)
        glm::vec3 up(camera.view[1][0], camera.view[1][1], camera.view[1][2]); // Up vector (Y axis)
        glm::vec3 viewDir(-camera.view[2][0], -camera.view[2][1], -camera.view[2][2]); // View direction (Z axis)

        sh.setUniform3fv("cameraPosition", -cameraPos);
        sh.setUniform3fv("cameraViewDir", viewDir);
        sh.setUniform3fv("cameraRight", right);
        sh.setUniform3fv("cameraUp", up);

        sphere1.updateBuffer(sh);
        sphere2.updateBuffer(sh);
        plane.updateBuffer(sh);
        light.updateBuffer(sh);
        //sh.setUniformMatrix("view", camera.view);
        //sh.setUniformMatrix("projection", projection);


        back.draw(sh);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    //gui.destroy();
    CleanUp::clean(Screen::vao, Screen::vbo, Screen::ebo);    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
