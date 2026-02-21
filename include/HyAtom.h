#ifndef HY_ATOM_H
#define HY_ATOM_H

// GLM Headers
#include "glm/ext/vector_int3.hpp"
#include <glm/glm.hpp>

// STL Headers
#include <random>
#include <vector>

/**
 * Represents a dot in the probability cloud
 *
 * @param position stores the particle position
 * @param phase stores the associated phase for the particle position 
 * @param pDensity stores the probability density at the particle position
 */ 
struct Particle {
   glm::vec3 position;
   float phase;
   float pDensity;
};

/**
 * Class to handle the simulation
 */ 
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
       * @param count number of particles to render in the orbital 
       */ 
      void runSim (int n, int l, int m, int count);

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

      std::mt19937 rng_;
};

#endif
