/**
 * @file GameObject.h
 *
 *  Created on: 25 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#define SPRITE_N  0
#define SPRITE_NE 1
#define SPRITE_E  2
#define SPRITE_SE 3
#define SPRITE_S  4
#define SPRITE_SW 5
#define SPRITE_W  6
#define SPRITE_NW 7

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
  CL_Sprite* static_sprites[8];
  CL_Sprite* static_current;
};

#endif /* GAMEOBJECT_H_ */
