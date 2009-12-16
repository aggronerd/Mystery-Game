/*
 * Entity.cpp
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#include "Entity.h"

Entity::Entity(CL_GraphicContext & graphicContext)
{
  //Stores a pointer to the graphics context for the draw function.
  gc = &graphicContext;
}

Entity::~Entity()
{
  //Sets the gc pointer to NULL
  gc = NULL;
}
