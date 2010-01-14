/*
 * PlayerCharacter.h
 *
 *  Created on: 26 Dec 2009
 *      Author: greg
 */

#ifndef PLAYERCHARACTER_H_
#define PLAYERCHARACTER_H_

#include "GameObject.h"

class PlayerCharacter : public GameObject
{
public:
  PlayerCharacter(World*,CL_Pointd&,CL_Angle&);
  virtual ~PlayerCharacter();
};

#endif /* PLAYERCHARACTER_H_ */
