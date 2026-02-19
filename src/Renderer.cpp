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

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, partSize, (void*)0);
   glEnableVertexAttribArray(0);
   
   glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, partSize, (void*)offsetof(Particle, phase));   
   glEnableVertexAttribArray(1);

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
