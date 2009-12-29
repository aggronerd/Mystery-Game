/*
 * MoveableGameObject.cpp
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#include "MoveableGameObject.h"

MoveableGameObject::MoveableGameObject(Game* game, CL_Pointd& starting_pos) : GameObject(game, starting_pos)
{
  //Object always starts static
  destination = starting_pos;
}

MoveableGameObject::~MoveableGameObject()
{
  delete still;
  delete move_n;
  delete move_ne;
  delete move_e;
  delete move_se;
  delete move_s;
  delete move_sw;
  delete move_w;
  delete move_nw;
}

void MoveableGameObject::draw()
{
  //Have to translate world position to isometric position.
  CL_Pointd isometricPoint = IsometricConversions::worldToIsometric(position);
  //TODO: add animation state.
  still.draw(this->g->getGC(),isometricPoint.x,isometricPoint.y);
  delete isometricPoint;
}

}
