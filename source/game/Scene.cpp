/**
 * @file Scene.cpp
 *
 * Created on: 5 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Scene.h"
#include "../misc/logging.h"

/**
 * Simple version of the constructor.
 *
 * @param owner
 * @return
 */
Scene::Scene(World* owner) : world(owner)
{
	DEBUG_MSG("Scene::Scene(World*) - Called.")

	//Set viewport to new one for configuring camera.
  active_viewport = new Viewport(this);
  add_viewport(active_viewport);
}

/**
 * Contructs scene from tiled level editor XML file.
 *
 * @param owner
 * @param file_name
 * @return
 */
Scene::Scene(World* owner, const CL_String& file_name) : world(owner)
{
	DEBUG_MSG("Scene::Scene(World*, const CL_String&) - Called.")

	//Set viewport to new one for configuring camera.
	active_viewport = new Viewport(this);
	add_viewport(active_viewport);

	//Parse the tilesets.

	//

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
