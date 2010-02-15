/*
 * Range.h
 *
 *  Created on: 22 Jan 2010
 *      Author: greg
 */

#ifndef RANGE_H_
#define RANGE_H_

/**
 * Used to influence the values of choices that can be made.
 */
class Range
{
public:
  Range(double, double);
  virtual ~Range();
  void applyWeight(int);
  virtual double selectValue(void);
protected:
  double start;
  double end;
};

#endif /* RANGE_H_ */
