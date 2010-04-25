/**
 * @file Scene.cpp
 *
 * Created on: 5 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Scene.h"
#include "World.h"
#include "GameObject.h"
#include "../misc/logging.h"
#include "AccessibleArea.h"
#include "Room.h"
//#include "game_objects/GrandfatherClock.h"

Scene::Scene(World* owner) : world(owner)
{
  active_viewport = new Viewport(this);
  add_viewport(active_viewport);

  //add_accessible_area(static_cast<AccessibleArea*>(new Room(this, "Ballroom", 30, 20, 0, 0)));
  add_accessible_area(static_cast<AccessibleArea*>(new Room(this, "Study", 1, 0, -15, 20)));
  //add_game_object(new GrandfatherClock(this, CL_Pointd(20,-4), CL_Angle(270, cl_degrees)));

  DEBUG_MSG("Scene::Scene(World*) - Called.")
}

Scene::~Scene()
{
  DEBUG_MSG("Scene::~Scene() - Called.")

	// Delete all game objects
  std::list<GameObject *>::iterator it_go;
	for(it_go = game_objects.begin(); it_go != game_objects.end(); ++it_go)
	  delete (*it_go);
	game_objects.clear();

	// Delete all viewports
  std::list<Viewport *>::iterator it_vp;
  for(it_vp = viewports.begin(); it_vp != viewports.end(); ++it_vp)
    delete (*it_vp);
  viewports.clear();

  // Delete all accessible areas
  std::list<AccessibleArea*>::iterator it_aa;
  for(it_aa = accessible_areas.begin(); it_aa != accessible_areas.end(); ++it_aa)
    delete (*it_aa);
  accessible_areas.clear();

  world = 0x0;
}

/**
 * Adds a game object to the scene.
 */
void Scene::add_game_object(GameObject* game_object)
{
  game_objects.push_back(game_object);
}

/**
 * Draws all game objects etc.
 */
void Scene::draw()
{
  //TODO: determine something about depth.

  // Draw all accessible areas
  std::list<AccessibleArea*>::iterator it_aa;
  for(it_aa = accessible_areas.begin(); it_aa != accessible_areas.end(); ++it_aa)
    (*it_aa)->draw();

	// Draw all game objects
	std::list<GameObject*>::iterator it_go;
	for(it_go = game_objects.begin(); it_go != game_objects.end(); ++it_go)
	  (*it_go)->draw();
}

/**
 * Updates contents.
 */
void Scene::update(unsigned int time_elapsed_ms)
{
  // Update viewport
  active_viewport->update(time_elapsed_ms);

  // Update all game objects
  std::list<GameObject*>::iterator it_go;
  for(it_go = game_objects.begin(); it_go != game_objects.end(); )
  {
    //If update returns false the object should be deleted.
    if((*it_go)->update(time_elapsed_ms) == false)
    {
      delete((*it_go));
      it_go = game_objects.erase(it_go);
    }
    else
      ++it_go;
  }
}

Viewport* Scene::get_active_viewport()
{
  return(active_viewport);
}

World* Scene::get_world()
{
  return(world);
}

void Scene::add_viewport(Viewport* new_viewport)
{
  viewports.push_back(new_viewport);
}

void Scene::add_accessible_area(AccessibleArea* new_accessible_area)
{
  accessible_areas.push_back(new_accessible_area);
}
