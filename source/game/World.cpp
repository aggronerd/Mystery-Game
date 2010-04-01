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
#include "Viewport.h"
#include "../Application.h"
#include "../misc/logging.h"
#include "../mystery_xml/Plot.h"

/**
 * Creates the game world and sets up initial contents.
 */
World::World(const CL_DisplayWindow &display_window) : ApplicationModule(display_window), viewport(this)
{
  DEBUG_MSG("World::World(CL_DisplayWindow &) - Called.")

  //Set object pointers to null
  music = 0x0;

  mouse_dragging = false;
  left_mouse_button_down = false;

  //Get the resource manager
  rm = CL_ResourceManager("data/game-resources.xml");

  //Setup sound output
  sound_output = CL_SoundOutput(44100);

  //Load objects into the world.
  init_level();
}

/**
 * Adds content to the world.
 */
void World::init_level()
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
  CL_Pointd pc_start(15,15);
  CL_Angle pc_direction(0,cl_degrees);

  DEBUG_MSG("World::initLevel() - Adding level contents.")

  // Isometric grid overlay
  add_overlay(new IsometricGrid(this));

  // Add player character
  player_character = new PlayerCharacter(this,pc_start,pc_direction);
  add_game_object(player_character);

  DEBUG_MSG("World::initLevel() - Creating and playing music.")

  //Create & play the sound buffer.
  music = new CL_SoundBuffer("data/audio/music/lone.ogg");
  music->play(true, &sound_output);

  get_active_viewport()->center_on_world(CL_Pointd(0,0));

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

  player_character = 0x0;

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
void World::add_overlay(Overlay* overlay)
{
  overlays.push_back(overlay);
}

/**
 * Adds a game object to the world.
 */
void World::add_game_object(GameObject* game_object)
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

/**
 * Updates game logic by calling all GameObject::update() calls.
 */
void World::update()
{
  unsigned int time_elapsed_ms = get_time_elapsed();

  // Update viewport
  viewport.update(time_elapsed_ms);

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

/**
 *
 */
void World::on_mouse_down(const CL_InputEvent &key, const CL_InputState &state)
{
  DEBUG_MSG("World::on_mouse_down(const CL_InputEvent&, const CL_InputState&) - Called - key.id = " + CL_StringHelp::int_to_text(key.id))
  if(key.id == 0)
  {
    //Left mouse button
    left_mouse_button_down = true;
  }

/*
  DEBUG_MSG(CL_String("World::on_mouse_down() - Called - Screen position: ") + CL_StringHelp::int_to_text(key.mouse_pos.x) + CL_String(",")
      + CL_StringHelp::int_to_text(key.mouse_pos.y) + CL_String(" - World position: ") + CL_StringHelp::int_to_text(mouse_position_world.x)
      + CL_String(",") + CL_StringHelp::int_to_text(mouse_position_world.y) + CL_String("."))
*/

}

void World::on_mouse_up(const CL_InputEvent &key, const CL_InputState &state)
{
  DEBUG_MSG("World::on_mouse_up(const CL_InputEvent&, const CL_InputState&) - Called - key.id = " + CL_StringHelp::int_to_text(key.id))
  if(key.id == 0)
  {
    //Left mouse button
    left_mouse_button_down = false;
  }
}

void World::on_mouse_move(const CL_InputEvent &key, const CL_InputState &state)
{
  //Scrolling e, w, s and n using borders.
  if(key.mouse_pos.x >= (get_gc()->get_width() - VIEWPOINT_SCROLL_BORDER_WIDTH))
    get_active_viewport()->set_scroll_e(true);
  else
    get_active_viewport()->set_scroll_e(false);

  if(key.mouse_pos.x <= VIEWPOINT_SCROLL_BORDER_WIDTH)
    get_active_viewport()->set_scroll_w(true);
  else
    get_active_viewport()->set_scroll_w(false);

  if(key.mouse_pos.y >= (get_gc()->get_height() - VIEWPOINT_SCROLL_BORDER_WIDTH))
    get_active_viewport()->set_scroll_s(true);
  else
    get_active_viewport()->set_scroll_s(false);

  if(key.mouse_pos.y <= VIEWPOINT_SCROLL_BORDER_WIDTH)
    get_active_viewport()->set_scroll_n(true);
  else
    get_active_viewport()->set_scroll_n(false);

  //Make the character face the pointer.
  //Get the position of the mouse in terms of world co-ordinates.
  CL_Pointd mouse_position_world = viewport.get_world_position((static_cast<CL_Point>(key.mouse_pos)));

  //Set the character to face the mouse
  player_character->set_facing(static_cast<CL_Vec2<double> >(mouse_position_world));
}

Viewport* World::get_active_viewport()
{
  return(&viewport);
}

CL_ResourceManager* World::get_rm()
{
  return(&rm);
}
