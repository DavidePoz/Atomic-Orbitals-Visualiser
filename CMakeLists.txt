cmake_minimum_required(VERSION 3.10)
project(AtomSimulation)

# Compile commands for auto completions
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Minimum C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Package dependencies
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Source files
set(SOURCES
   src/main.cpp
   src/Window.cpp
   src/Camera.cpp
   src/Shader.cpp
   src/Renderer.cpp
   src/HyAtom.cpp
   src/QMechModel.cpp
)

# Executable 
add_executable(AtomSimulation ${SOURCES})

# Header files location
target_include_directories(AtomSimulation PRIVATE include)

# Link OpenGL libraries
target_link_libraries(AtomSimulation PRIVATE 
    glad::glad 
    glfw 
    glm::glm
)
