cmake_minimum_required(VERSION 3.10)
project(AtomSimulation)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(AtomSimulation src/main.cpp)
