/*
 * DiscreteRange.cpp
 *
 *  Created on: 22 Jan 2010
 *      Author: greg
 */

#include "DiscreteRange.h"
#include "../logging.h"

DiscreteRange::DiscreteRange(int range_start, int range_end)
{
  DEBUG_MSG("DiscreteRange::DiscreteRange(int, int) - Called.")
  start = range_start;
  end   = range_end;
}

DiscreteRange::~DiscreteRange()
{}

int DiscreteRange::selectValue()
{

}
