// --- SIMULATION HEADERS ---
#include "HyAtom.h"
#include "QMechModel.h"

// --- VISUALISATION HEADERS ---
#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Renderer.h"

// --- GL HEADERS ---
#include <GLFW/glfw3.h>

// --- STL HEADERS ---
#include <iostream>
#include <vector>

// ------- GLOBALS FOR MOUSE INPUT HANDLING -------

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);

Camera* cam = nullptr;
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Watch the window for mouse movement
void mouseCallback (GLFWwindow* window, double xPosIn, double yPosIn) {
   
   float xPos = static_cast<float>(xPosIn);
   float yPos = static_cast<float>(yPosIn);

   if (firstMouse) {
      lastX = xPos;
      lastY = yPos;
      firstMouse = false;
   }

   float xoffset = xPos - lastX;
   float yoffset = lastY - yPos;

   lastX = xPos;
   lastY = yPos;

   if (cam) {
      cam->handleMouseMovement(xoffset, yoffset);
   }
}

// Watch for scroll wheel movement
void scrollCallback (GLFWwindow* window, double xoffset, double yoffset) {

   if (cam) {
      cam->handleScroll(static_cast<float>(yoffset));
   }

}

// ------- MAIN -------

int main () {

   std::cout << "Initializing Hydrogen Atom simulation\n";

   Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hydrogen_Atom_Sim");
   GLFWwindow* natWindow = window.getNatWindow();
   
   Camera camera(70.0f, 45.0f, ASPECT_RATIO);
   cam = &camera;

   glfwSetCursorPosCallback(natWindow, mouseCallback);
   glfwSetScrollCallback(natWindow, scrollCallback);
   glfwSetInputMode(natWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   constexpr int PARTICLE_COUNT = 100000;

   int n = 3;
   int l = 2;
   int m = 1;

   HyAtom atom;
   atom.runSim(n, l, m, PARTICLE_COUNT);
   std::vector<Particle> electronCloud = atom.getParticles();

   Shader shader("../shaders/particle.vert", "../shaders/particle.frag");
   Renderer renderer;
   renderer.setupParticles(electronCloud);

   while (window.isOpen()) {
      window.listenEvents();

      if (glfwGetKey(natWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
         glfwSetWindowShouldClose(natWindow, true);
      }
      
      //atom.updateSim(10);
      window.clear(0.02f, 0.03f, 0.06f, 1.0f);
      renderer.draw(shader, camera);
      window.swapBuffers();
   }

   return 0;
}
