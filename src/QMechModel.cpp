// Custom headers
#include "QMechModel.h"

// GLM Headers
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"

// STL Headers
#include <cmath>
#include <cstdlib>

// ---------------------------- WAVE FUNCTION IMPLEMENTATION --------------------------

using namespace QMathHelpers;

// Acquires the radial and angular parts of the wave function and computes its squared magnitude
float WaveFunction::computeProbabilityDensity(const glm::dvec3 &pos, int n, int l, int m) {
   
   glm::vec3 sphericalPos = cartToSpherical(pos);
   float r = sphericalPos.x;
   float theta = sphericalPos.y;

   float R = radialPart(r, n, l);
   float Y = angularPart(theta, l, m);

   float psi = R * Y;

   return psi * psi;
}

// Computes the phase as m * phi
float WaveFunction::computePhase(const glm::dvec3 &pos, int n, int l, int m) {

   glm::vec3 sphericalPos = cartToSpherical(pos);

   float phase = static_cast<float>(m) * sphericalPos.z;

   float R = radialPart(sphericalPos.x, n, l);
   float Y = angularPart(sphericalPos.y, l, m);

   // Shift phase by PI if the amplitude is negative
   if (R * Y < 0.0f) {
      phase += PI;
   }
   
   return phase;
}

// ---------------------------- MATH HELPERS --------------------------

// Convert cartesian coordinates to spherical
glm::vec3 QMathHelpers::cartToSpherical (const glm::vec3& pos) {
   
   float r = glm::length(pos); 
   if (r < 0.0001f) return glm::vec3(0.0f); 
   
   float theta = std::acos(pos.z / r);
   float phi = std::atan2(pos.y, pos.x);

   return glm::vec3(r, theta, phi);
}

// Returns the radial part of the wavefunction
// R = rho^l * N * Lag(rho) * exp(-rho/2)
float QMathHelpers::radialPart (float r, int n, int l) {

   float rho = (2.0f * r) / (n * BOHR_R);                // Normalized distance
   float Lag = std::assoc_laguerre(n-l-1, 2*l +1, rho);  // Laguerre pol.

   // N = sqrt( (2/(n*a0))^3 * (n-l-1)! / (2n * (n+l)!) )
   float num = std::tgamma(n-l);
   float den = 2.0f * n * std::tgamma(n+l+1);
   float N   = std::sqrt( std::pow(2.0f / (n * BOHR_R), 3) * (num / den) );  
   
   return std::pow(rho, (float)l) * N * Lag * std::exp(-rho / 2.0f);
}

// Returns the magnitude of the angular part of the wavefunction (ignores exponential term)
// Y = k * P_l^m * exp : k * P_l^m is returned
float QMathHelpers::angularPart (float theta, int l, int m) {
   return std::sph_legendre(l, std::abs(m), theta);
}
