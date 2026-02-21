#ifndef RENDERER_H
#define RENDERER_H

// Custom Headers
#include "Camera.h"
#include "HyAtom.h"
#include "Shader.h"

// STL Headers
#include <cstddef>
#include <vector>

/**
 * Class to handle scene rendering
 */ 
class Renderer {

   public:

      /* Constructor */ 
      Renderer ();
      
      /* Destructor */ 
      ~Renderer ();

      /**
       * Setup function for the VAO and VBO
       *
       * @param particles vector of particles to read data from
       */ 
      void setupParticles (const std::vector<Particle>& particles);

      /**
       * Draws the particles to the screen 
       *
       * @param shader the shader object to apply to each particle
       * @param camera the camera object to apply the correct view and projection transformations
       */ 
      void draw (const Shader& shader, const Camera& camera) const;

   private:
      
      unsigned int VAO;
      unsigned int VBO;
      std::size_t particleCount_;

};

#endif
