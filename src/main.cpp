
#include <dependencies.hpp>


int main() {
    Config::loadConfig();
    GLFWwindow *window = initWindow();

    Camera camera(window,true);
    Screen back;



    Shader sh("../assets/vertex.glsl", "../assets/fragment.glsl");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                            (float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.1f, 100.0f);
    


    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(camera.processFrame()) break;
        sh.activate();

        glUniform1f(glGetUniformLocation(sh.ID, "iTime"), glfwGetTime());
        glUniform3f(glGetUniformLocation(sh.ID, "iResolution"), (float)Config::WINDOW_WIDTH, (float)Config::WINDOW_HEIGHT, 0.0f);
        
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
