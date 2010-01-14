/*
 * PlayerCharacter.cpp
 *
 *  Created on: 26 Dec 2009
 *      Author: greg
 */

#include "PlayerCharacter.h"
#include <ClanLib/core.h>
#include "World.h"

PlayerCharacter::PlayerCharacter(World* w, CL_Pointd& initial_position, CL_Angle& initial_direction) : GameObject(w, initial_position, initial_direction)
{
  static_sw = new CL_Sprite(*(world->getGC()), "characters/detective_standing", world->getRM());
}

PlayerCharacter::~PlayerCharacter()
{}
