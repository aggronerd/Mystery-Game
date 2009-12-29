/*
 * GameObject.h
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <ClanLib/core.h>

class World;

class GameObject
{
public:
  GameObject(World*, CL_Pointd&);
  virtual ~GameObject();
  virtual void draw() {};
  virtual bool update(unsigned int) = 0;
protected:
  World* world;
  CL_Pointd position;
};

#endif /* GAMEOBJECT_H_ */
