
#include <dependencies.hpp>
#include <random>
float rand(float min=0.0f, float max=1.0f) {
    // Create a random device and a Mersenne Twister engine
    std::random_device rd;  // Random number generator seed
    std::mt19937 gen(rd()); // Mersenne Twister engine initialized with seed
    std::uniform_real_distribution<float> dis(min, max); // Uniform distribution between min and max
    
    return dis(gen);
}

int main() {
    Config::loadConfig();
    GLFWwindow *window = initWindow();

    Camera camera(window,false);

    Gui gui(window);
    

    Shader sh;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                            (float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.1f, 100.0f);

    Plane plane = Plane(glm::vec3(0,1,0),glm::vec4(0.3f,0.8f,0.2f,1.0f), 1.0, 16.0, 0.2, 0.0, 1.0);
    plane.scale(glm::vec3(100.0f,0.0f,100.0f));

    std::vector<Sphere*> spheres;
    std::vector<Shape*> objects;
    objects.push_back(&plane);

    for(int i=0;i<20;i++){
        Sphere* s= new Sphere(glm::vec4(rand(0,1),rand(0,1),rand(0,1),1.0), 1.0, 16.0, 0.5, 0.0, 2.0);

        s->velocity = glm::vec3(rand(0,1),rand(0,1),rand(0,1));
        s->tarnslate(glm::vec3(rand(-10,10),rand(0,10),rand(-10,10)));
        spheres.push_back(s);
        objects.push_back(s);

    }


    Light light = Light(glm::vec4(1),glm::vec3(-0.4, -1.0, -1), 0.0f);

    Cuboid box(glm::vec4(0.3), 1.0, 16.0, 0.2, 0.0, 1.0);
    box.scale(glm::vec3(2,2,2));



    sh.activate();


    


    Screen back;

    //Texture tex("../resource/pz.png");
    //tex.activate();


    CubeMap sky;
    Collider collider(objects);


    while (!glfwWindowShouldClose(window)) {
        //glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(camera.processFrame()) break;

        glUniform1f(glGetUniformLocation(sh.ID, "iTime"), glfwGetTime());
        glUniform3f(glGetUniformLocation(sh.ID, "iResolution"), (float)Config::WINDOW_WIDTH, (float)Config::WINDOW_HEIGHT, 0.0f);
       
       

        collider.collide();


        light.updateBuffer(sh);
        for(int i=0;i<spheres.size();i++){
            spheres[i]->updateBuffer(sh);
            std::cout << "DEBUG1" << std::endl;
        }
        plane.updateBuffer(sh);
        //box.updateBuffer(sh);

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
