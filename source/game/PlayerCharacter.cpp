/**
 * @file PlayerCharacter.cpp
 *
 *  Created on: 26 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "PlayerCharacter.h"
#include <ClanLib/core.h>
#include "World.h"

PlayerCharacter::PlayerCharacter(World* w, CL_Pointd& initial_position, CL_Angle& initial_direction) : GameObject(w, initial_position, initial_direction)
{
  static_sprites[SPRITE_SW] = new CL_Sprite(*(world->getGC()), "characters/detective_static_sw", world->getRM());
  setDirection(initial_direction);
}

PlayerCharacter::~PlayerCharacter()
{}
