/*
 * RandomGenerator.h
 *
 *  Created on: 2 Dec 2009
 *      Author: greg
 */

#ifndef RANDOMGENERATOR_H_
#define RANDOMGENERATOR_H_

/**
 * This provides random numbers for the
 */
class RandomGenerator
{

public:

  RandomGenerator(unsigned int);
  double generateFloat(void);

  virtual ~RandomGenerator();

private:

  bool setSeed(unsigned int);

};

#endif /* RANDOMGENERATOR_H_ */