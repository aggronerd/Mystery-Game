/*
 * GameObject.h
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class Game;
class CL_Pointd;

class GameObject
{
public:
  GameObject(Game*, CL_Pointd);
  virtual ~GameObject();
  virtual void draw()=0;
protected:
  Game* g;
  CL_Pointd* position;
};

#endif /* GAMEOBJECT_H_ */
