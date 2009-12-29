/*
 * GameObject.cpp
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#include "GameObject.h"
#include <ClanLib/core.h>

GameObject::GameObject(Game* game, CL_Pointd pos)
{
  g = game;
  position = &pos;
}

GameObject::~GameObject()
{
  g = NULL;
  delete position;
}
