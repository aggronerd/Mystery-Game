/**
 * @file PlayerCharacter.cpp
 *
 *  Created on: 26 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "PlayerCharacter.h"
#include <ClanLib/core.h>
#include "../Scene.h"
#include "../World.h"

PlayerCharacter::PlayerCharacter(Scene* s, CL_Pointd& initial_position, CL_Angle& initial_direction) : GameObject(s, initial_position, initial_direction)
{
  //Load the sprites.
  CL_GraphicContext gc = *(scene->get_world()->get_gc());
  CL_ResourceManager* rm = scene->get_world()->get_rm();
  static_sprites[SPRITE_N] = new CL_Sprite(gc, "characters/detective_static_n", rm);
  static_sprites[SPRITE_NE] = new CL_Sprite(gc, "characters/detective_static_ne", rm);
  static_sprites[SPRITE_E] = new CL_Sprite(gc, "characters/detective_static_e", rm);
  static_sprites[SPRITE_SE] = new CL_Sprite(gc, "characters/detective_static_se", rm);
  static_sprites[SPRITE_S] = new CL_Sprite(gc, "characters/detective_static_s", rm);
  static_sprites[SPRITE_SW] = new CL_Sprite(gc, "characters/detective_static_sw", rm);
  static_sprites[SPRITE_W] = new CL_Sprite(gc, "characters/detective_static_w", rm);
  static_sprites[SPRITE_NW] = new CL_Sprite(gc, "characters/detective_static_nw", rm);

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
