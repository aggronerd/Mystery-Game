/*
 * GameObject.h
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#define SPRITE_SW = 0;
#define

class World;

class GameObject
{
public:
  GameObject(World*, CL_Pointd&, CL_Angle&);
  virtual ~GameObject();
  void setDirection(CL_Angle&);
  CL_Angle getDirection(void);
  void setPosition(CL_Pointd&);
  CL_Pointd getPosition(void);
  virtual void draw();
  virtual bool update(unsigned int);
protected:
  World* world;
  CL_Pointd position; //Isometric position, not world
  CL_Angle direction; //angle in degrees from north
  CL_Sprite* static_sprites[7];
  CL_Sprite* static_current;
};

#endif /* GAMEOBJECT_H_ */
