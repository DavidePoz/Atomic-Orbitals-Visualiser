#ifndef QMECH_MODEL_H
#define QMECH_MODEL_H

#include <glm/glm.hpp>

// Functions related to the Hydrogen wave function
namespace WaveFunction {

   /**
    * Computes the probability density at a given position
    *
    * @param pos position to calculate the probability at
    * @param n principal quantum number
    * @param l angular quantum number
    * @param m magnetic quantum number
    */ 
   float computeProbabilityDensity (const glm::dvec3& pos, int n, int l, int m);

   /**
    * Computes the phase at a given position
    *
    * @param pos position to calculate the phase at
    * @param n principal quantum number
    * @param l angular quantum number
    * @param m magnetic quantum number
    */ 
   float computePhase (const glm::dvec3& pos, int n, int l, int m);

};

// Helper math to support the wave function implementations
namespace QMathHelpers {

   // CONSTANTS
   constexpr float BOHR_R = 1.0f;
   constexpr float PI = 3.14159265f;

   /**
    * Converts a position vector from cartesian to spherical coordinates
    *
    * @param pos vector to convert
    */ 
   glm::vec3 cartToSpherical (const glm::vec3& pos); 

   /**
    * Computes the radial component of the wavefunction using
    * laguerre polynomials 
    *
    * @param r radial distance from the nucleus
    * @param n principal quantum number
    * @param l angular quantum number 
    */ 
   float radialPart (float r, int n, int l);

   /**
    * Computes the angular component of the wavefunction using
    * legendre polynomials 
    *
    * @param theta polar angle
    * @param l angular quantum number 
    * @param m magnetic quantum number
    */ 
   float angularPart (float theta, int l, int m);

}

#endif
