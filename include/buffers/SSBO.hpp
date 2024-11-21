#ifndef SSBO_H
#define SSBO_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>

template <typename T>
class SSBO {
public:
    GLuint ID;
    void* bufferPointer;  // Persistent pointer to mapped buffer
    T* data;              // Data to send to the SSBO
    GLsizeiptr size;      // Size of the SSBO

    SSBO(T* data, GLsizeiptr size, GLuint binding_point = 0) {
        this->data = data;
        this->size = size;

        glGenBuffers(1, &ID);

        this->bind();

        glBufferStorage(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

        bufferPointer = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT);
        this->updateBuffer();

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point, ID);
    }

    void updateBuffer() {
        memcpy(bufferPointer, data, size);
    }

    void bind() {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
    }

    ~SSBO() {
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
};

#endif
