// Custom Headers
#include "Window.h"

// GL Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STL Headers
#include <iostream>
#include <string>

// Helper
void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
}

// Constructor
Window::Window (int width, int height, const std::string& title) 
   : width_ {width}, height_ {height}, window_ {nullptr}
{
   if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW\n";
      return;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
   if (!window_) {
      std::cerr << "Failed to create GLFW window\n";
      glfwTerminate();
      return;
   }

   glfwMakeContextCurrent(window_);
   glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

   if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ){
      std::cerr << "Failed to initialize GLAD\n";
      return;
   }

   glEnable(GL_DEPTH_TEST);
}

// Destructor
Window::~Window () {
   glfwTerminate();
}

// ---------- MEMBER FUNCTIONS

bool Window::isOpen () const {
   return !glfwWindowShouldClose(window_);
}

void Window::listenEvents () const {
   glfwPollEvents();
}

void Window::swapBuffers () const {
   glfwSwapBuffers(window_);
}

void Window::clear (float r, float g, float b, float a) const {
   glClearColor(r, g, b, a);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Window::getWidth () const { return width_; }
int Window::getHeight () const { return height_; }
GLFWwindow* Window::getNatWindow () const { return window_; }
