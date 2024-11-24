
#include <dependencies.hpp>


int main() {
    Config::loadConfig();
    GLFWwindow *window = initWindow();

    Camera camera(window,false);
    Screen back;

    Gui gui(window);

    Shader sh;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                            (float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.1f, 100.0f);

    Plane plane = Plane(glm::vec3(0,1,0),glm::vec4(0.3f,0.8f,0.2f,1.0f), 1.0, 16.0, 0.2, 0.0, 1.0);
    plane.scale(glm::vec3(10.0f,0.0f,10.0f));
    Sphere sphere1 = Sphere(glm::vec4(1.0,0.1,0.1,1.0), 1.0, 16.0, 0.5, 0.0, 2.0);
    Sphere sphere2 = Sphere(glm::vec4(0.3,0.3,1.0,1.0), 1.0, 16.0, 0.1, 0.0, 2.0);
    sphere1.tarnslate(glm::vec3(1.0f,1.0f,1.0f));
    sphere2.tarnslate(glm::vec3(-1.0f,1.0f,-1.0f));
    Light light = Light(glm::vec4(1),glm::vec3(-0.4, -1.0, -1), 0.0f);

    sh.activate();


    

    //Texture tex("../resource/pz.png");
    //tex.activate();


    CubeMap sky;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(camera.processFrame()) break;

        glUniform1f(glGetUniformLocation(sh.ID, "iTime"), glfwGetTime());
        glUniform3f(glGetUniformLocation(sh.ID, "iResolution"), (float)Config::WINDOW_WIDTH, (float)Config::WINDOW_HEIGHT, 0.0f);
       

        //gui.newFrame();
        //ImGui::Begin("Hello, world!");
        //static float color[3] = {0,0,0};
        //ImGui::ColorEdit3("RGB Color", color);
        //plane.material.color.r = color[0];
        //plane.material.color.g = color[1];
        //plane.material.color.b = color[2];

        //std::cout << plane.material.color.r <<  " " << plane.material.color.g << " " << plane.material.color.b << std::endl;
 
        //ImGui::End();

        light.updateBuffer(sh);
        sphere1.updateBuffer(sh);
        sphere2.updateBuffer(sh);
        plane.updateBuffer(sh);

        sh.setUniform3fv("cameraPosition", cameraPos);
        sh.setUniform3fv("cameraViewDir", cameraFront);
        sh.setUniform3fv("cameraUp", cameraUp);

        sky.bind();
        sh.setUniform1i("iChannerl0",0);
        
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
