#ifndef QMECH_MODEL_H
#define QMECH_MODEL_H

#include "../dependencies/glm/glm.hpp"

namespace PhysConstants {
   constexpr double BOHR_R = 1.0;
   constexpr double PI = 3.14159265358979323846;
};

namespace WaveFunction {

   double computeProbabilityDensity (const glm::vec3& pos, int n, int l, int m);

   double computePhase (const glm::vec3& pos, int n, int l, int m);

};

#endif
