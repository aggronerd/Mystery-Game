/**
 * @file World.cpp
 *
 *  Created on: 6 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "World.h"
#include "IsometricGrid.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "Overlay.h"
#include "../Application.h"
#include "../misc/logging.h"
#include "../mystery_xml/Plot.h"

/**
 * Creates the game world and sets up initial contents.
 */
World::World(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("World::World(CL_DisplayWindow &) - Called.")

  //Set object pointers to null
  music = 0x0;

  //Get the resource manager
  rm = CL_ResourceManager("data/game-resources.xml");

  //Setup sound output
  sound_output = CL_SoundOutput(44100);

  //Load objects into the world.
  initLevel();
}

/**
 * Adds content to the world.
 */
void World::initLevel()
{

  DEBUG_MSG("World::initLevel() - Loading plot data from XML file.")

  try
  {
    //Create the plot object to initiate generation.
    Plot plot("data/mystery.xml");
  }
  catch (CL_DomException e) {
    Application::log(LOG_LEVEL_INFO,"Error occurred while parsing level: '" + e.message + "'.");
  }

  //Where the player's character starts
  CL_Pointd pc_start(0,0);
  CL_Angle pc_direction(225,cl_degrees);

  DEBUG_MSG("World::initLevel() - Adding level contents.")

  // Isometric grid overlay
  addOverlay(new IsometricGrid(this));

  // Add player character
  addGameObject(new PlayerCharacter(this,pc_start,pc_direction));

  DEBUG_MSG("World::initLevel() - Creating and playing music.")

  //Create & play the sound buffer.
  music = new CL_SoundBuffer("data/audio/music/lone.ogg");
  music->play(true, &sound_output);

}

/**
 * Destructor.
 */
World::~World()
{

  DEBUG_MSG("World::~World() - Called.")

  // Delete all game objects
  std::list<GameObject *>::iterator it_go;
  for(it_go = game_objects.begin(); it_go != game_objects.end(); ++it_go)
    delete (*it_go);
  game_objects.clear();

  // Delete all overlays
  std::list<Overlay *>::iterator it_ov;
  for(it_ov = overlays.begin(); it_ov != overlays.end(); ++it_ov)
      delete (*it_ov);
  overlays.clear();

  // Stop and delete music.
  if(music != 0x0)
    delete music;

}

/**
 * Adds an overlay object to the world.
 */
void World::addOverlay(Overlay* overlay)
{
  overlays.push_back(overlay);
}

/**
 * Adds a game object to the world.
 */
void World::addGameObject(GameObject* game_object)
{
  game_objects.push_back(game_object);
}

/**
 * Draws all objects and overlays.
 */
void World::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));

  // Draw all game objects
  std::list<GameObject *>::iterator it_go;
  for(it_go = game_objects.begin(); it_go != game_objects.end(); ++it_go)
    (*it_go)->draw();

  // Draw all overlays
  std::list<Overlay *>::iterator it_ov;
  for(it_ov = overlays.begin(); it_ov != overlays.end(); ++it_ov)
    (*it_ov)->draw();

  window.flip(1);
}

void World::update()
{
  unsigned int time_elapsed_ms = get_time_elapsed();

  // Update all game objects
  std::list<GameObject *>::iterator it_go;
  for(it_go = game_objects.begin(); it_go != game_objects.end(); )
  {
    //If update returns false the object should be deleted.
    if((*it_go)->update(time_elapsed_ms) == false)
    {
      delete(*it_go);
      it_go = game_objects.erase(it_go);
    }
    else
      ++it_go;
  }
}

CL_ResourceManager* World::getRM()
{
  return(&rm);
}
