/**
 * @file World.cpp
 *
 *  Created on: 6 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "World.h"
#include "IsometricGrid.h"
#include "game_objects/PlayerCharacter.h"
#include "game_objects/HotelGroundFloor.h"
#include "GameObject.h"
#include "Viewport.h"
#include "../Application.h"
#include "../misc/logging.h"
#include "../bbn/BBN_Plot.h"
#include "../bbn/BBN_Option.h"
#include "../bbn/BBN_Decision.h"
#include "../bbn/BBN_Exception.h"
#include <vector>

/**
 * Creates the game world and sets up initial contents.
 */
World::World(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("World::World(CL_DisplayWindow &) - Called.")

  //Set object pointers to null
  music = 0x0;
  active_scene = 0x0;
  plot = 0x0;

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
    CL_String8 plot_filename = "data/plots/hotel.xml";
  	plot = new BBN_Plot(plot_filename);
    plot->prepare_bn();
  }
  catch (BBN_Exception e) {
    Application::log(LOG_LEVEL_INFO,"Error occurred while parsing bayesian net: '" + e.message + "'.");

    //Do not proceed to load level - instead returned to menu.
    exit_code = EXIT_MODULE_AND_LOAD_MAIN_MENU;
    return;
  }

//  plot->set_result("characters_dead","1");
//
//  CL_String8 victim;
//
//  if(plot->query_result("a_dead")->get_name() == CL_String8("1"))
//  {
//    victim = "a";
//    Application::log(LOG_LEVEL_INFO,CL_String8("The general is dead!!!"));
//  }
//  if(plot->query_result("b_dead")->get_name() == CL_String8("1"))
//  {
//    victim = "b";
//    Application::log(LOG_LEVEL_INFO,CL_String8("The hotel owner is dead!!!"));
//  }
//  if(plot->query_result("c_dead")->get_name() == CL_String8("1"))
//  {
//    victim = "c";
//    Application::log(LOG_LEVEL_INFO,CL_String8("The princess is dead!!!"));
//  }
//  if(plot->query_result("d_dead")->get_name() == CL_String8("1"))
//  {
//    victim = "d";
//    Application::log(LOG_LEVEL_INFO,CL_String8("The chef is dead!!!"));
//  }
//  Application::log(LOG_LEVEL_INFO,CL_String8("----------------------"));
//  Application::log(LOG_LEVEL_INFO,CL_String8("Evidence node values:"));
//
//  /*
//   * Lists all evidence nodes.
//   */
//  std::vector<BBN_Decision*>* decisions = plot->get_decisions();
//  std::vector<BBN_Decision*>::iterator it_dec;
//  for(it_dec =  decisions->begin(); it_dec != decisions->end(); ++it_dec)
//  {
//		//Check prefix
//  	if((*it_dec)->get_name().substr(0,3) == CL_String8("ev_"))
//  	{
//  		//Is evidence - prints to console
//			Application::log(LOG_LEVEL_INFO, (*it_dec)->get_name() + " = " + (*it_dec)->get_result()->get_name());
//  	}
//  }
//
//  Application::log(LOG_LEVEL_INFO,CL_String8("----------------------"));
//  Application::log(LOG_LEVEL_INFO,CL_String8("Who killed the victim?"));
//
//  CL_String8 query_string;
//  BBN_Option* result;
//
//  query_string = "a_murders_" + victim;
//  result = plot->query_result(query_string);
//  if(result != 0x0 && result->get_name() == CL_String8("1"))
//  {
//    CL_String8 motive_query = query_string.substr(0,1) + victim + "_motive" ;
//    Application::log(LOG_LEVEL_INFO,CL_String8("It was the general!!! Why though?"));
//    Application::log(LOG_LEVEL_INFO,plot->query_result(motive_query)->get_english());
//  }
//
//  query_string = "b_murders_" + victim;
//  result = plot->query_result(query_string);
//  if(result != 0x0 && result->get_name() == CL_String8("1"))
//  {
//    CL_String8 motive_query = query_string.substr(0,1) + victim + "_motive" ;
//    Application::log(LOG_LEVEL_INFO,CL_String8("It was the hotel owner!!! Why though?"));
//    Application::log(LOG_LEVEL_INFO,plot->query_result(motive_query)->get_english());
//  }
//
//  query_string = "c_murders_" + victim;
//  result = plot->query_result(query_string);
//  if(result != 0x0 && result->get_name() == CL_String8("1"))
//  {
//    CL_String8 motive_query = query_string.substr(0,1) + victim + "_motive" ;
//    Application::log(LOG_LEVEL_INFO,CL_String8("It was the princess!!! Why though?"));
//    Application::log(LOG_LEVEL_INFO,plot->query_result(motive_query)->get_english());
//  }
//
//  query_string = "d_murders_" + victim;
//  result = plot->query_result(query_string);
//  if(result != 0x0 && result->get_name() == CL_String8("1"))
//  {
//    CL_String8 motive_query = query_string.substr(0,1) + victim + "_motive" ;
//    Application::log(LOG_LEVEL_INFO,CL_String8("It was the chef!!! Why though?"));
//    Application::log(LOG_LEVEL_INFO,plot->query_result(motive_query)->get_english());
//  }

  //Where the player's character starts
  CL_Pointd pc_start(0,0);
  CL_Angle pc_direction(-90,cl_degrees);
  CL_Angle north(45,cl_degrees);
  CL_Pointd bg_start(-13,1);

  DEBUG_MSG("World::initLevel() - Creating test scene and adding level contents.")

  // Isometric grid overlay
  //add_overlay(new IsometricGrid(this));

  // Add player character
  add_scene(new Scene(this,CL_String8("data/scenes/hotel/hotel.tmx")));

  player_character = new PlayerCharacter(this->get_active_scene(),pc_start,pc_direction);
  this->get_active_scene()->add_game_object(player_character);

  DEBUG_MSG("World::initLevel() - Creating and playing music.")

  //Create & play the sound buffer.
  music = new CL_SoundBuffer("data/audio/music/lone.ogg");
  music->play(true, &sound_output);

  get_active_scene()->get_active_viewport()->center_on_world(CL_Pointd(0,0));

}

/**
 * Destructor.
 */
World::~World()
{

  DEBUG_MSG("World::~World() - Called.")

  player_character = 0x0;
  active_scene = 0x0;

  // Delete all overlays
  std::list<Overlay*>::iterator it_ov;
  for(it_ov = overlays.begin(); it_ov != overlays.end(); ++it_ov)
      delete (*it_ov);
  overlays.clear();

  // Delete all scenes
  std::list<Scene*>::iterator it_sc;
  for(it_sc = scenes.begin(); it_sc != scenes.end(); ++it_sc)
      delete (*it_sc);
  scenes.clear();

  // Delete the plot
  if(plot != 0x0)
    delete plot;

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
 * Draws all objects and overlays.
 */
void World::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));

  // Draws the active scene
  this->get_active_scene()->draw();

  // Draw all overlays
  std::list<Overlay*>::iterator it_ov;
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

  this->get_active_scene()->update(time_elapsed_ms);

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
  DEBUG_MSG(CL_String8("World::on_mouse_down() - Called - Screen position: ") + CL_StringHelp::int_to_text(key.mouse_pos.x) + CL_String8(",")
      + CL_StringHelp::int_to_text(key.mouse_pos.y) + CL_String8(" - World position: ") + CL_StringHelp::int_to_text(mouse_position_world.x)
      + CL_String8(",") + CL_StringHelp::int_to_text(mouse_position_world.y) + CL_String8("."))
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
    get_active_scene()->get_active_viewport()->set_scroll_e(true);
  else
    get_active_scene()->get_active_viewport()->set_scroll_e(false);

  if(key.mouse_pos.x <= VIEWPOINT_SCROLL_BORDER_WIDTH)
    get_active_scene()->get_active_viewport()->set_scroll_w(true);
  else
    get_active_scene()->get_active_viewport()->set_scroll_w(false);

  if(key.mouse_pos.y >= (get_gc()->get_height() - VIEWPOINT_SCROLL_BORDER_WIDTH))
    get_active_scene()->get_active_viewport()->set_scroll_s(true);
  else
    get_active_scene()->get_active_viewport()->set_scroll_s(false);

  if(key.mouse_pos.y <= VIEWPOINT_SCROLL_BORDER_WIDTH)
    get_active_scene()->get_active_viewport()->set_scroll_n(true);
  else
    get_active_scene()->get_active_viewport()->set_scroll_n(false);

  //Make the character face the pointer.
  //Get the position of the mouse in terms of world co-ordinates.
  //CL_Pointd mouse_position_world = get_active_scene()->get_active_viewport()->get_world_position((static_cast<CL_Point>(key.mouse_pos)));

  //Set the character to face the mouse
  //player_character->set_facing(static_cast<CL_Vec2<double> >(mouse_position_world));
}

CL_ResourceManager* World::get_rm()
{
  return(&rm);
}

void World::add_scene(Scene* new_scene)
{
  scenes.push_back(new_scene);
}

/**
 * Returns a pointer to the active Scene object.
 * If there is no Scene object returns 0x0.
 *
 * @return
 */
Scene* World::get_active_scene()
{
  if(active_scene == 0x0)
  {
  	if(scenes.size() > 0)
  	{
  		return(scenes.front());
  	}
  	else
  	{
  		return(0x0);
  	}
  }
  else
  {
    return(active_scene);
  }
}

/**
 *
 */
void World::on_key_down(const CL_InputEvent &key, const CL_InputState &state)
{
	//ESC Returns the player to the main menu.
	if(key.id == CL_KEY_ESCAPE)
		exit_code = EXIT_MODULE_AND_LOAD_MAIN_MENU;

	//F12 Toggles the visibility of the collision map.
	if(key.id == CL_KEY_F12)
	{
		if(get_active_scene() != 0x0)
		{
			if(get_active_scene()->get_show_navigation_mesh())
			{
				get_active_scene()->set_show_navigation_mesh(false);
			}
			else
			{
				get_active_scene()->set_show_navigation_mesh(true);
			}
		}
	}
}
