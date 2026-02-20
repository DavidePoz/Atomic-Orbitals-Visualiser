// Custom Headers
#include "Renderer.h"
#include "HyAtom.h"

// GL Headers
#include <glad/glad.h>

// STL Headers
#include <vector>
#include <cstddef>

// Default (empty state) initialization 
Renderer::Renderer () : VAO {0}, VBO {0}, particleCount_ {0} {}

// Destructor. Deletes VAO and VBO
Renderer::~Renderer () {
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
}

// Setup the VAO and VBO
void Renderer::setupParticles (const std::vector<Particle>& particles) {

   particleCount_ = particles.size();

   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);

   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_STATIC_DRAW);

   GLsizei partSize = sizeof(Particle);

   // Attribute 0: particle position (3 float values)
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, partSize, (void*)0);
   glEnableVertexAttribArray(0);
   
   // Attribute 1: associated phase (1 float value)
   glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, partSize, (void*)offsetof(Particle, phase));   
   glEnableVertexAttribArray(1);

   // Attribute 2: associated probability density (1 float value)
   glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, partSize, (void*)offsetof(Particle, pDensity));   
   glEnableVertexAttribArray(2);

   glBindVertexArray(0);   
}

// Draw particles to the screen
void Renderer::draw (const Shader& shader, const Camera& camera) const {

   shader.use();

   shader.setMat4("view", camera.getViewMatrix());
   shader.setMat4("projection", camera.getProjMatrix());

   glBindVertexArray(VAO);

   glDrawArrays(GL_POINTS, 0, particleCount_);

   glBindVertexArray(0);
}
