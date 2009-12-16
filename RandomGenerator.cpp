/*
 * RandomGenerator.cpp
 *
 *  Created on: 2 Dec 2009
 *      Author: greg
 */

#include "RandomGenerator.h"
#include <cstdlib>

RandomGenerator::RandomGenerator(unsigned int seed)
{
  //Seeds itself with time.
  setSeed(seed);
}

RandomGenerator::~RandomGenerator()
{
  // TODO Auto-generated destructor stub
}

bool RandomGenerator::setSeed(unsigned int seed)
{
  srand(seed);
  return(true);
}
