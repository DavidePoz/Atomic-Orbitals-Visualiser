#ifndef HY_ATOM_H
#define HY_ATOM_H

// GLM Headers
#include "glm/ext/vector_int3.hpp"
#include <glm/glm.hpp>

// STL Headers
#include <random>
#include <vector>

struct Particle {
   glm::vec3 position;
   float phase;
};

class HyAtom {

   public:

      HyAtom();
      ~HyAtom() = default;

   // ------- SIM-RELATED Functions --------------

      /**
       * Runs the simulation with (new) quantum numbers
       *
       * @param n principal quantum number
       * @param l angular quantum number
       * @param m magnetic quantum number
       * @param count number of particles to visualize on screen 
       */ 
      void runSim (int n, int l, int m, int count);

      /**
       * Updates the simulation state
       *
       * @param dt : elapsed time from previous sim state
       */ 
      void updateSim (float dt);

   // ------- Other utilities --------------
  
      /**
       * Returns the list of particles
       */  
      const std::vector<Particle>& getParticles () const { return particles_; };

      /**
       * Returns the quantum numbers
       */  
      const glm::ivec3 getQNumbers () const { return glm::ivec3(n,l,m); };

   private:

      std::vector<Particle> particles_;
      int n,l,m;

      static constexpr float PHASE_SPEED = 0.2f; 

      std::mt19937 rng_;
};

#endif
