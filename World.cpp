/*
 * World.cpp
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#include "World.h"
#include "IsometricGrid.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "Overlay.h"
#include <ClanLib/core.h>

/**
 * Creates the game world and sets up initial contents.
 */
World::World(CL_DisplayWindow &display_window) : window(display_window), quit(false)
{
  cl_log_event("debug","Instance of World created.");

  // Get the graphic context
  gc = window.get_gc();

  //Get the resource manager
  rm = CL_ResourceManager("resources.xml");

  slot_quit       = window.sig_window_close().connect(this, &World::onWindowClose);
  slot_key_down   = window.get_ic().get_keyboard().sig_key_down().connect(this, &World::onKeyDown);
  slot_key_up     = window.get_ic().get_keyboard().sig_key_up().connect(this, &World::onKeyUp);
  slot_mouse_down = window.get_ic().get_mouse().sig_key_down().connect(this, &World::onMouseDown);
  slot_mouse_up   = window.get_ic().get_mouse().sig_key_up().connect(this, &World::onMouseUp);
  slot_mouse_move = window.get_ic().get_mouse().sig_pointer_move().connect(this, &World::onMouseMove);

  quit = false;
  mouse_dragging = false;
  mouse_down = false;

  initLevel();
}

/**
 * Adds content to the world.
 */
void World::initLevel()
{
  //Where the player's character starts
  CL_Pointd pc_start(0,0);
  CL_Angle pc_direction(225,cl_degrees);

  // Isometric grid overlay
  addOverlay(new IsometricGrid(this));

  // Add player character
  addGameObject(new PlayerCharacter(this,pc_start,pc_direction));
}

/**
 * Destructor.
 */
World::~World()
{
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
 * Initiates the game loop.
 */
int World::run()
{
  // Run until someone presses escape.
  while (!quit)
  {
    draw();
    update();
    // This call processes user input and other events
    CL_KeepAlive::process(0);
  }
  return(0);
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
  unsigned int time_elapsed_ms = calculateTimeElapsed();

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

// Calculate amount of time since last frame
unsigned int World::calculateTimeElapsed()
{
  static unsigned int last_time = 0;
  unsigned int new_time = CL_System::get_time();

  if(last_time == 0)
    last_time = new_time;

  int delta_time = (new_time - last_time);
  last_time = new_time;

  return(delta_time);
}

void World::onKeyUp(const CL_InputEvent &key, const CL_InputState &state)
{
  if(key.id == CL_KEY_ESCAPE)
  {
    quit = true;
  }
}

void World::onKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{}

void World::onMouseDown(const CL_InputEvent &key, const CL_InputState &state)
{}

void World::onMouseUp(const CL_InputEvent &key, const CL_InputState &state)
{}

void World::onMouseMove(const CL_InputEvent &key, const CL_InputState &state)
{}

void World::onWindowClose()
{
  quit = true;
}

CL_GraphicContext* World::getGC()
{
  return(&gc);
}

CL_ResourceManager* World::getRM()
{
  return(&rm);
}
