/*
 * Level.h
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "Entity.h"
#include <ClanLib/display.h>
#include <list>

class Level
{
  private:
    std::list<Entity *> entities;
    CL_GraphicContext* gc;
  public:
    Level(CL_GraphicContext &);
    virtual ~Level();
    virtual void draw() = 0;
};

#endif /* LEVEL_H_ */
