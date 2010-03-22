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
  //Load the sprites.
  static_sprites[SPRITE_N] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_n", world->get_rm());
  static_sprites[SPRITE_NE] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_ne", world->get_rm());
  static_sprites[SPRITE_E] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_e", world->get_rm());
  static_sprites[SPRITE_SE] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_se", world->get_rm());
  static_sprites[SPRITE_S] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_s", world->get_rm());
  static_sprites[SPRITE_SW] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_sw", world->get_rm());
  static_sprites[SPRITE_W] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_w", world->get_rm());
  static_sprites[SPRITE_NW] = new CL_Sprite(*(world->get_gc()), "characters/detective_static_nw", world->get_rm());

  set_direction(initial_direction);
}

PlayerCharacter::~PlayerCharacter()
{}

bool PlayerCharacter::update(unsigned int time_elapsed_ms)
{
  bool result = true;

  //Do what you want here.

  result = result && GameObject::update(time_elapsed_ms);

  return(result);
}
