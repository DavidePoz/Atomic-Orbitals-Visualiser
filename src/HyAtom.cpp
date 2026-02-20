// Custom Headers
#include "HyAtom.h"
#include "QMechModel.h"

// STL Headers
#include <glm/fwd.hpp>
#include <iostream>
#include <random>

// Constructor : initializes the atom to a default state and the random number generator
HyAtom::HyAtom() : n {1}, l {0}, m {0} {
   std::random_device rd;
   rng_ = std::mt19937(rd());
}

// (Re)Runs the simulation
void HyAtom::runSim (int n, int l, int m, int count) {

   // Clear previous data
   particles_.clear();
   particles_.reserve(count);

   // Set (possibly new) quantum numbers
   this->n = n;
   this->l = l;
   this->m = m;

   // Scale simulation area with n^2
   float simRadius = 5.0 * n * n;

   // Setup distributions for positions and probabilities
   std::uniform_real_distribution<float> posDist(-simRadius, simRadius);
   std::uniform_real_distribution<float> probDist(0.0, 1.0);

   // Simulation counters 
   int pointsSet = 0;
   int attemps   = 0;
   const int SAFE_FACTOR  = 100;
   const int MAX_ATTEMPTS = count * SAFE_FACTOR;
   const int ACCEPTANCE   = 1000;

   // Simulation
   while (pointsSet < count && attemps < MAX_ATTEMPTS) {
      attemps++;

      // Generate candidate position
      glm::vec3 candidatePos(
         posDist(rng_),
         posDist(rng_),
         posDist(rng_)
      );
     
      // Get probability density at the candidate position
      float dens = WaveFunction::computeProbabilityDensity(candidatePos, n, l, m);

      // Rejection test
      if (dens * ACCEPTANCE > probDist(rng_)) {
         // Accepted: create particle
         Particle p;
         p.position = candidatePos;
         p.phase = WaveFunction::computePhase(candidatePos, n, l, m);
         // ... and register it
         particles_.push_back(p);
         pointsSet++;
      }

   }

   // For TESTING purposes (to be commented otherwise)
   std::cout << "Generated " << pointsSet << " particles for orbital (" 
             << n << ", " << l << ", " << m << ")\n";
}

void HyAtom::updateSim (float dt) {

   for (auto& p : particles_) {
      p.phase += PHASE_SPEED * dt;

      if (p.phase > 2 * QMathHelpers::PI) {
         p.phase -= 2 * QMathHelpers::PI; 
      }

   }

}
