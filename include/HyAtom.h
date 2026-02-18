#ifndef HY_ATOM_H
#define HY_ATOM_H

// GLM Headers
#include "../dependencies/glm/glm.hpp"

// STL Headers
#include <random>
#include <vector>

struct Particle {
   glm::vec3 position;
   double phase;
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
      void updateSim ();

   // ------- Other utilities --------------
   
      const std::vector<Particle>& getParticles () const { return  particles_; };

   private:

      std::vector<Particle> particles_;
      int n,l,m;

      std::mt19937 rng_;
};

#endif
