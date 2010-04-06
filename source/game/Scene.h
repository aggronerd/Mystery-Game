/**
 * @file Scene.h
 *
 * Created on: 5 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Viewport.h"
#include <list>

class GameObject;
class World;

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

private:
  Viewport viewport;
  std::list<GameObject*> game_objects;
  World* world;

};

#endif /* SCENE_H_ */
