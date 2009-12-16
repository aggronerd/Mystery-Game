/*
 * Level.cpp
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#include "Level.h"

Level::Level(CL_GraphicContext& graphicsContext)
{
  //Set the pointer to the graphics context
  gc = &graphicsContext;
}

Level::~Level()
{
  //Destroy all entities in the level.
  entities.clear();
  //Set the graphics context to null
  gc = NULL;
}
