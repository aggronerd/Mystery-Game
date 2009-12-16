/*
 * Entity.h
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <ClanLib/display.h>

class Entity
{
  private:
    CL_GraphicContext* gc;
  public:
    Entity(CL_GraphicContext &);
    virtual ~Entity();
    virtual void draw() = 0;
};

#endif /* ENTITY_H_ */
