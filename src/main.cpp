
#include <dependencies.hpp>

static float color[3] = { 1.0f, 0.0f, 0.0f };

int main() {
    Config::loadConfig();
    GLFWwindow *window = initWindow();

    Gui gui(window);

    Camera camera(window,true);
    Sphere sphere1(0.1,glm::vec3(0.7f));
    sphere1.tarnslate(glm::vec3(-1.0f,1.0f,1.0f));



    Shader sh("../assets/vertex.glsl", "../assets/fragment.glsl");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                            (float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.1f, 100.0f);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(camera.processFrame()) break;

        sphere1.objectColor = glm::vec3(color[0], color[1], color[2]);
        sh.setUniform("color", sphere1.objectColor);
        sh.setUniformMatrix("view", camera.view);
        sh.setUniformMatrix("projection", projection);

        sh.activate();

        sphere1.draw(sh);


        gui.newFrame();

        {
            ImGui::Begin("Overlay Window");

            ImGui::ColorEdit3("Color Selector", color);

            ImGui::End(); 
        }

        gui.renderFrame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    gui.destroy();
    CleanUp::clean(Sphere::vao,Sphere::vbo, Sphere::ebo, Plane::vao, Plane::vbo, Plane::ebo);    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
