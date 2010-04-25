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
#include "Viewport.h"

class GameObject;
class World;
class AccessibleArea;

class Scene
{
public:
  Scene(World*);
  virtual ~Scene();
  Viewport* get_active_viewport(void);
  World* get_world(void);
  void add_game_object(GameObject*);
  void draw(void);
  void update(unsigned int);
  void add_viewport(Viewport*);
  void add_accessible_area(AccessibleArea*);

private:
  std::list<Viewport*> viewports;
  std::list<GameObject*> game_objects;
  std::list<AccessibleArea*> accessible_areas;
  World* world;
  Viewport* active_viewport;

};

#endif /* SCENE_H_ */
