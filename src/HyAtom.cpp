// Custom Headers
#include "../include/HyAtom.h"

// STL Headers
#include <random>

// Constructor : initializes the atom to a default state and the random number generator
HyAtom::HyAtom() 
   : n {1}, l {0}, m {0}
{
   std::random_device rand;
   rng_ = std::mt19937(rand());
}
