/**
 * @file RandomGenerator.cpp
 *
 *  Created on: 2 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
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
