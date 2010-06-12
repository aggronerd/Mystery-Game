/**
 * @file Scene.h
 *
 * Created on: 5 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include "World.h"
#include "GameObject.h"
#include "Viewport.h"
#include <ClanLib/core.h>

class Scene
{
public:
  Scene(World*);
  Scene(World*, const CL_String&);
  virtual ~Scene();
  Viewport* get_active_viewport(void);
  World* get_world(void);
  void add_game_object(GameObject*);
  void draw(void);
  void update(unsigned int);
  void add_viewport(Viewport*);
  void add_accessible_area(AccessibleArea*);

private:
  std::list<CL_SharedPtr<Viewport> > viewports;
  std::list<CL_SharedPtr<GameObject> > game_objects;
  std::list<std::list<CL_Sprite> > tiles;
  World* world;
  CL_SharedPtr<Viewport> active_viewport;

};

#endif /* SCENE_H_ */
