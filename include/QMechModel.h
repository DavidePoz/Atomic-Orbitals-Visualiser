#ifndef QMECH_MODEL_H
#define QMECH_MODEL_H

#include <glm/glm.hpp>

namespace PhysConstants {
   constexpr float BOHR_R = 1.0f;
   constexpr float PI = 3.14159265f;
};

namespace WaveFunction {

   float computeProbabilityDensity (const glm::dvec3& pos, int n, int l, int m);

   float computePhase (const glm::dvec3& pos, int n, int l, int m);

};

#endif
