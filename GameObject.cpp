/*
 * GameObject.cpp
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#include "GameObject.h"
#include "World.h"
#include <ClanLib/core.h>

GameObject::GameObject(World* w, CL_Pointd& pos)
{
  world = w;
  position = pos;
}

GameObject::~GameObject()
{
  world = NULL;
}
