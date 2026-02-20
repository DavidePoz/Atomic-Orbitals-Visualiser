// --- SIMULATION HEADERS ---
#include "HyAtom.h"
#include "QMechModel.h"

// --- VISUALISATION HEADERS ---
#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Renderer.h"

// Imgui Headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// --- GL HEADERS ---
#include <GLFW/glfw3.h>

// --- STL HEADERS ---
#include <iostream>
#include <vector>

// ------- GLOBALS FOR MOUSE INPUT HANDLING -------

constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 1000;
constexpr float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);

Camera* cam = nullptr;
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Watch the window for mouse movement
void mouseCallback (GLFWwindow* window, double xPosIn, double yPosIn) {
   
   // Mouse over UI: ignore camera input
   if (ImGui::GetIO().WantCaptureMouse) {
      firstMouse = true;
      return;
   }

   // Mouse action to control the camera
   if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      
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
   } else {
      firstMouse = true;
   }

}

// Watch for scroll wheel movement
void scrollCallback (GLFWwindow* window, double xoffset, double yoffset) {

   // Mouse over UI: ignore mouse input
   if (ImGui::GetIO().WantCaptureMouse) return;

   if (cam) {
      cam->handleScroll(static_cast<float>(yoffset));
   }

}

// --------- MAIN ---------

int main () {

   std::cout << "Initializing Hydrogen Atom simulation\n";

   // Quantum numbers default initialization
   int n = 1;
   int l = 0;
   int m = 0;

   // Camera init constants
   const float START_R = 6.0f * n * n;
   const float MIN_R = 0.5f;
   const float MAX_R = 7.5f * 8 * 8;
   const float START_CAM_ANGLE = 45.0f;

   // Create window
   Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hydrogen_Atom_Sim");
   GLFWwindow* natWindow = window.getNatWindow();
   
   // Create camera and link it to the global cam
   Camera camera(START_R, START_CAM_ANGLE, ASPECT_RATIO, MIN_R, MAX_R);
   cam = &camera;

   // Set input callbacks and mode
   glfwSetCursorPosCallback(natWindow, mouseCallback);
   glfwSetScrollCallback(natWindow, scrollCallback);
   glfwSetInputMode(natWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

   // Initialise atom and run the (first) simulation
   constexpr int PARTICLE_COUNT = 100000;
   
   HyAtom atom;
   atom.runSim(n, l, m, PARTICLE_COUNT);
   
   // Particles vector for the shaders
   std::vector<Particle> electronCloud = atom.getParticles();
   Shader shader("../shaders/particle.vert", "../shaders/particle.frag");
   
   // Setup particles for visualisation
   Renderer renderer;
   renderer.setupParticles(electronCloud);
   
   // View mode: 0 = phase view, 1 = probability view
   int viewMode = 0;
   bool vKeyPressed = false;

   // ImGui init shenanigans 
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGui::StyleColorsDark();
   ImGui_ImplGlfw_InitForOpenGL(natWindow, true);
   ImGui_ImplOpenGL3_Init("#version 330");

   while (window.isOpen()) {

      window.listenEvents();

      // Escape key closes the window
      if (glfwGetKey(natWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
         glfwSetWindowShouldClose(natWindow, true);
      }
     
      if (glfwGetKey(natWindow, GLFW_KEY_V) == GLFW_PRESS) {
         if (!vKeyPressed) {
            viewMode = (viewMode == 0) ? 1 : 0;
            vKeyPressed = true;
         }
      } else {
         vKeyPressed = false;
      }

      // More imgui shenanigans
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
     
      // ImGui Menu
      ImGui::Begin("Quantum State Settings");

         int prev_n = n, prev_l = l, prev_m = m;
         
         // Draw Sliders
         ImGui::SliderInt("Principal (n)", &n, 1, 8);
         ImGui::SliderInt("Angular (l)", &l, 0, n - 1); 
         ImGui::SliderInt("Magnetic (m)", &m, -l, l);
        
         // If any slider was moved, recalculate the cloud instantly!
         if (n != prev_n || l != prev_l || m != prev_m) {
             atom.runSim(n, l, m, PARTICLE_COUNT);
             renderer.setupParticles(atom.getParticles());
         }

      ImGui::End();

      // Background color
      window.clear(0.02f, 0.03f, 0.06f, 1.0f);
     
      // Use shader, pass view mode to visualise the correct colors
      shader.use();
      shader.setInt("uViewMode", viewMode);      

      // Draw particles
      renderer.draw(shader, camera);

      // Draw ImGui menu
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      window.swapBuffers();
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   return 0;
}
