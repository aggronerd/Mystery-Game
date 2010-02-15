/*
 * Range.cpp
 *
 *  Created on: 22 Jan 2010
 *      Author: greg
 */

#include "Range.h"
#include "../logging.h"

Range::Range(double range_start, double range_end)
{

  DEBUG_MSG("Range::Range(double, double) - Called.")

  start = range_start;
  end   = range_end;

}

Range::~Range()
{
  DEBUG_MSG("Range::~Range() - Called.")
}
