/*
 * PlayerCharacter.cpp
 *
 *  Created on: 26 Dec 2009
 *      Author: greg
 */

#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Game* game,CL_Pointd& starting_pos) : MoveableGameObject(game, starting_pos)
{
  still = new CL_Sprite(*(g->getGC()), "characters/detective_standing", g->getRM());
}

PlayerCharacter::~PlayerCharacter()
{
  //TODO: do i need to put a destructor here for the sprites?
}
