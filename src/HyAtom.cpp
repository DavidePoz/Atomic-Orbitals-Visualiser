// Custom Headers
#include "HyAtom.h"
#include "QMechModel.h"

// STL Headers
#include <algorithm>
#include <iterator>
#include <random>

// GL Headers
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>

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
   const int RESOLUTION = 4096;

   std::vector<float> cdf_r(RESOLUTION, 0.0f);
   std::vector<float> cdf_theta(RESOLUTION, 0.0f);

   float dr = simRadius / RESOLUTION;
   float dtheta = QMathHelpers::PI / RESOLUTION;

   float sum_r = 0.0f;
   float sum_theta = 0.0f;

   for (int i = 0; i < RESOLUTION; i++) {
      
      float r = i * dr;
      float R_val = QMathHelpers::radialPart(r, n, l);
      sum_r += (r * r * R_val * R_val);
      cdf_r[i] = sum_r;

      float theta = i * dtheta;
      float Y_val = QMathHelpers::angularPart(theta, l, m);
      sum_theta += (glm::sin(theta) * Y_val * Y_val);
      cdf_theta[i] = sum_theta;
      
   }
   
   for (int i = 0; i < RESOLUTION; i++) {
      cdf_r[i] /= sum_r;
      cdf_theta[i] /= sum_theta;
   }

   std::uniform_real_distribution<float> probDist(0.0f,1.0f);

   for (int i = 0; i < count; i++) {

      float u_r = probDist(rng_);
      float u_theta = probDist(rng_);
      float u_phi = probDist(rng_);

      auto it_r = std::lower_bound(cdf_r.begin(), cdf_r.end(), u_r);
      float r = (std::distance(cdf_r.begin(), it_r) + probDist(rng_)) * dr;

      auto it_theta = std::lower_bound(cdf_theta.begin(), cdf_theta.end(), u_theta);
      float theta = (std::distance(cdf_theta.begin(), it_theta) + probDist(rng_)) * dtheta;

      float phi = u_phi * 2.0f * QMathHelpers::PI;

      glm::vec3 pos;
      pos.x = r * std::sin(theta) * std::cos(phi);
      pos.z = r * std::sin(theta) * std::sin(phi);
      pos.y = r * std::cos(theta);

      Particle p;
      p.position = pos;
      p.phase = WaveFunction::computePhase(pos, n, l, m);
      p.pDensity = WaveFunction::computeProbabilityDensity(pos, n, l, m);
      particles_.push_back(p);

   }
   
   float maxDens = 0.0f;
   for (const auto& p : particles_) {
      if (p.pDensity > maxDens) maxDens = p.pDensity;
   }
   for (auto& p : particles_) {
      p.pDensity /= maxDens;
   }

}
