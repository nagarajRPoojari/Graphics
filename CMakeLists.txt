cmake_minimum_required(VERSION 3.10)
project(GladExample)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Optionally disable compiler-specific extensions

find_package(OpenGL REQUIRED)
find_package(yaml-cpp REQUIRED)

# Include directories
include_directories(include)
include_directories(imgui/backends)

# Optionally add the include directories for other libraries
include_directories(/usr/include/) 
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/imgui")
include_directories(${IMGUI_DIR})

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
    src/cubemap.cpp
    src/shape/shape.cpp 
    src/shape/sphere.cpp 
    src/shape/material.cpp
    src/shape/light.cpp
    src/shape/cuboid.cpp
    src/shape/plane.cpp
    src/screen.cpp
    src/camera.cpp
    src/gui/gui.cpp
    src/physics/collider.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_tables.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Create the executable
add_executable(GladExample ${SOURCES})

# Link the necessary libraries
target_link_libraries(GladExample ${OPENGL_LIBRARIES} glfw yaml-cpp)

# Set include directories for the target
target_include_directories(GladExample PRIVATE include /usr/include)