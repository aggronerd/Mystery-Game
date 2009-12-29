/*
 * PlayerCharacter.cpp
 *
 *  Created on: 26 Dec 2009
 *      Author: greg
 */

#include "PlayerCharacter.h"
#include <ClanLib/core.h>
#include "World.h"

PlayerCharacter::PlayerCharacter(World* w,CL_Pointd& starting_pos) : MoveableGameObject(w, starting_pos)
{
  still = new CL_Sprite(*(world->getGC()), "characters/detective_standing", world->getRM());
}

PlayerCharacter::~PlayerCharacter()
{
  //TODO: do i need to put a destructor here for the sprites?
}
