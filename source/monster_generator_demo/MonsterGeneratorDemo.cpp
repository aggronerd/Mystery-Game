/*
 * MonsterGeneratorDemo.cpp
 *
 *  Created on: 21 May 2010
 *      Author: greg
 */

#include "MonsterGeneratorDemo.h"
#include "../misc/logging.h"
#include "../game/GameObject.h"
#include "Monster.h"
#include "../bbn/BBN_Info.h"
#include "../bbn/BBN_Plot.h"
#include <map>

MonsterGeneratorDemo::MonsterGeneratorDemo(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("MonsterGeneratorDemo::MonsterGeneratorDemo(CL_DisplayWindow &) - Called.")

	_window_editor = 0x0;
  _control_bbn = 0x0;
  _active_net = 0x0;

  //Get the resource manager
  _rm = CL_ResourceManager("data/monster-resources.xml");

  std::map<CL_String, CL_String> preset_properties;

  for(int y=0; y < 4; y++)
    for(int x=0; x < 1; x++)
    {
      if(y==1)
    	  preset_properties["dwellings"] = "swamp";
      if(y==2)
    	  preset_properties["dwellings"] = "forest";
      if(y==3)
    	  preset_properties["dwellings"] = "desert";

      _monsters.push_back(new Monster(CL_Pointf(64.0f*x,128.0f*y),this, preset_properties));
    }
}

MonsterGeneratorDemo::~MonsterGeneratorDemo()
{
  DEBUG_MSG("MonsterGeneratorDemo::~MonsterGeneratorDemo() - Called.")

  // Delete all monsters
  std::list<Monster*>::iterator it_go;
  for(it_go = _monsters.begin(); it_go != _monsters.end(); ++it_go)
  	delete (*it_go);
  _monsters.clear();

  if(_window_editor != 0x0)
  {
  	delete(_window_editor);
  	_window_editor = 0x0;
  }

  if(_control_bbn != 0x0)
  {
  	delete(_control_bbn);
  	_control_bbn = 0x0;
  }

  if(_active_net != 0x0)
  {
  	delete(_active_net);
  	_active_net = 0x0;
  }

}

void MonsterGeneratorDemo::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));

  // Draw all monsters
  std::list<Monster*>::iterator it_go;
  for(it_go = _monsters.begin(); it_go != _monsters.end(); ++it_go)
    (*it_go)->draw(&gc);

  gui.exec(false);
  wm.draw_windows(gc);

  window.flip(1);
}

/**
 * Creates the monster bayes net editor window if one
 * doesn't already exit and ensures it is visible if
 * one does.
 */
void MonsterGeneratorDemo::show_editor()
{

	if(_window_editor == 0x0)
	{
		//Window doesn't exist, create:
		CL_GUITopLevelDescription desc;
		desc.set_allow_resize(false);
		desc.set_title("Monster Generator");
		desc.set_position(CL_Rect(0,0,600,340),false);
		desc.set_decorations(true);

		_window_editor = new CL_Window(&gui, desc);
		_window_editor->set_draggable(true);

		//Add bbn for editing if one doesn't exist
		if(_active_net == 0x0)
		{
			_active_net = new BBN_Plot("data/plots/monster.xml");
			_active_net->prepare_bn();
		}


		if(_control_bbn != 0x0)
			delete(_control_bbn);

		//Add bbn_info component.
		_control_bbn = new BBN_Info(static_cast<CL_GUIComponent>_window_editor,_active_net);
		_control_bbn->set_geometry(CL_Rect(20,20,580,280), true);
		_control_bbn->set_visible(true);

		//Add button to create monster.


	}
	else
	{
		//Window does exist ensure visible
		_window_editor->set_visible(true);
	}


}

void MonsterGeneratorDemo::update()
{}

CL_ResourceManager* MonsterGeneratorDemo::get_rm()
{
	return(&_rm);
}

/**
 *
 */
void MonsterGeneratorDemo::on_key_down(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_KEY_ESCAPE)
		exit_code = EXIT_MODULE_AND_LOAD_MAIN_MENU;

	if(key.id == CL_KEY_F12)
		show_editor();
}
