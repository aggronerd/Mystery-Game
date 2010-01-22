/*
 * DiscreteRange.cpp
 *
 *  Created on: 22 Jan 2010
 *      Author: greg
 */

#include "DiscreteRange.h"
#include "../logging.h"

DiscreteRange::DiscreteRange(int range_start, int range_end) : Range(range_start, range_end)
{

  DEBUG_MSG("DiscreteRange::DiscreteRange(int, int) - Called.")

}

DiscreteRange::~DiscreteRange()
{

  DEBUG_MSG("DiscreteRange::~DiscreteRange() - Called.")

}

int DiscreteRange::selectValue()
{
  //TODO: Code this.
  return(0);
}
