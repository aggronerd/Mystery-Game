/*
 * HotelGroundFloor.cpp
 *
 *  Created on: 9 May 2010
 *      Author: greg
 */

#include "HotelGroundFloor.h"
#include "../Scene.h"
#include "../World.h"
#include <ClanLib/core.h>

HotelGroundFloor::HotelGroundFloor(Scene* s, CL_Pointd& initial_position, CL_Angle& initial_direction) : GameObject(s, initial_position, initial_direction)
{

	//Load the sprites.
	CL_GraphicContext gc = *(scene->get_world()->get_gc());
	CL_ResourceManager* rm = scene->get_world()->get_rm();

	static_sprites[SPRITE_N] = new CL_Sprite(gc, "areas/hotel/ground-floor", rm);

	set_direction(initial_direction);
}

bool HotelGroundFloor::update(unsigned int time_elapsed_ms)
{
  bool result = true;

  //Do what you want here.
  result = result && GameObject::update(time_elapsed_ms);

  return(result);
}

HotelGroundFloor::~HotelGroundFloor() {}
