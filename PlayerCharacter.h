/*
 * PlayerCharacter.h
 *
 *  Created on: 26 Dec 2009
 *      Author: greg
 */

#ifndef PLAYERCHARACTER_H_
#define PLAYERCHARACTER_H_

#include "MoveableGameObject.h"

class PlayerCharacter : public MoveableGameObject
{
public:
  PlayerCharacter(World*,CL_Pointd&);
  virtual ~PlayerCharacter();
};

#endif /* PLAYERCHARACTER_H_ */
