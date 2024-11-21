#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader/shader.hpp>

class Light{
    public:
        static int BUFFER_INDEX;
        int buffer_index;
        glm::vec3 dir; 
        glm::vec4 color;   
        glm::vec3 ray;     
        float mag;  
        Light(glm::vec4 color, glm::vec3 dir, float strength);
        void updateBuffer(Shader sh);
        const char* format(std::string field);
};


#endif