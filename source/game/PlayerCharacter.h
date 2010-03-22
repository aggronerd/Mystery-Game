/**
 * @file PlayerCharacter.h
 *
 *  Created on: 26 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef PLAYERCHARACTER_H_
#define PLAYERCHARACTER_H_

#include "GameObject.h"

class PlayerCharacter : public GameObject
{
public:
  PlayerCharacter(World*,CL_Pointd&,CL_Angle&);
  virtual ~PlayerCharacter();
  virtual bool update(unsigned int);
};

#endif /* PLAYERCHARACTER_H_ */
