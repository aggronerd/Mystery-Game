/*
 * MoveableGameObject.h
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#ifndef MOVEABLEGAMEOBJECT_H_
#define MOVEABLEGAMEOBJECT_H_

#include "GameObject.h"

class World;
class CL_Pointd;
class CL_Sprite;

class MoveableGameObject : public GameObject
{
public:
  void draw(void);
  bool update(unsigned int);
  MoveableGameObject(World*,CL_Pointd&);
  virtual ~MoveableGameObject();
protected:
  CL_Sprite* still;
  CL_Sprite* move_n;
  CL_Sprite* move_ne;
  CL_Sprite* move_e;
  CL_Sprite* move_se;
  CL_Sprite* move_s;
  CL_Sprite* move_sw;
  CL_Sprite* move_w;
  CL_Sprite* move_nw;
private:
  int status;
  CL_Pointd destination;
};

#endif /* MOVEABLEGAMEOBJECT_H_ */
