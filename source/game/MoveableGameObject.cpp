/**
 * @file MoveableGameObject.cpp
 *
 *  Created on: 25 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "MoveableGameObject.h"
#include <ClanLib/core.h>

MoveableGameObject::MoveableGameObject(Scene* s, CL_Pointd& initial_position, CL_Angle& initial_direction) : GameObject(s, initial_position, initial_direction)
{
  //Object always starts static
  destination = initial_position;
}

MoveableGameObject::~MoveableGameObject()
{
  /*delete still;
  delete move_n;
  delete move_ne;
  delete move_e;
  delete move_se;
  delete move_s;
  delete move_sw;
  delete move_w;
  delete move_nw;*/
}

void MoveableGameObject::draw()
{
  //Have to translate world position to isometric position.
  //CL_Point isometricPoint = world->get_active_viewport()->get_screen_position(world_position);
  //TODO: add animation state.
  //still->draw(*(world->getGC()),(float)(isometricPoint.x),(float)(isometricPoint.y));
}

bool MoveableGameObject::update(unsigned int time_elapsed)
{
  return(true);
}
