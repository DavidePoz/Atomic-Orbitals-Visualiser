cmake_minimum_required(VERSION 3.10)
project(AtomSimulation)

# Compile commands for auto completions
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Minimum C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Package dependencies
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Source files
set(SOURCES
   src/main.cpp
   src/Window.cpp
   src/Camera.cpp
   src/Shader.cpp
   src/Renderer.cpp
   src/HyAtom.cpp
   src/QMechModel.cpp
   
   # External sources
   src/Externals/glad.c
   src/Externals/Imgui/imgui.cpp
   src/Externals/Imgui/imgui_draw.cpp
   src/Externals/Imgui/imgui_tables.cpp
   src/Externals/Imgui/imgui_widgets.cpp
   src/Externals/Imgui/imgui_impl_glfw.cpp
   src/Externals/Imgui/imgui_impl_opengl3.cpp
)

# Executable 
add_executable(AtomSimulation ${SOURCES})

# Header files location
target_include_directories(AtomSimulation PRIVATE 
   include
   include/Externals
   include/Externals/Imgui
)

# Link OpenGL libraries
target_link_libraries(AtomSimulation PRIVATE 
    glfw 
    glm::glm
    ${CMAKE_DL_LIBS}
)
