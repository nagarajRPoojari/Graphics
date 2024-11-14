cmake_minimum_required(VERSION 3.10)
project(GladExample)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Optionally disable compiler-specific extensions

find_package(OpenGL REQUIRED)
find_package(yaml-cpp REQUIRED)

# Include directories
include_directories(include)

# Optionally add the include directories for other libraries
include_directories(/usr/include/) 

# Specify the source files
set(SOURCES 
    lib/glad.c 
    lib/stb.cpp 
    src/main.cpp 
    src/utils.cpp 
    src/buffers/EBO.cpp 
    src/buffers/VAO.cpp 
    src/buffers/VBO.cpp 
    src/shader.cpp 
    src/texture.cpp 
    src/shape/shape.cpp 
    src/shape/sphere.cpp 
    src/shape/plane.cpp 
    src/camera.cpp
)

# Create the executable
add_executable(GladExample ${SOURCES})

# Link the necessary libraries
target_link_libraries(GladExample ${OPENGL_LIBRARIES} glfw yaml-cpp)

# Set include directories for the target
target_include_directories(GladExample PRIVATE include /usr/include)