/*
 * DiscreteRange.h
 *
 *  Created on: 22 Jan 2010
 *      Author: greg
 */

#ifndef DISCRETERANGE_H_
#define DISCRETERANGE_H_

#include "Range.h"

/**
 * Class for ranges of discrete integers. The constructor
 * defines the start and end integers. Distributions can
 * then be applied to the range of values to influence how
 * they are selected.
 */
class DiscreteRange : Range
{
public:
  DiscreteRange(int, int);
  virtual ~DiscreteRange();
  virtual int selectValue(void);
};

#endif /* DISCRETERANGE_H_ */
