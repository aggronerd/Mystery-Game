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

MonsterGeneratorDemo::MonsterGeneratorDemo(const CL_DisplayWindow &display_window) : ApplicationModule(display_window), _next_monster_x(0), _next_monster_y(0)
{
  DEBUG_MSG("MonsterGeneratorDemo::MonsterGeneratorDemo(CL_DisplayWindow &) - Called.")

	_window_editor = 0x0;
  _control_bbn = 0x0;
  _active_net = 0x0;
  _button_generate = 0x0;

  //Get the resource manager
  _rm = CL_ResourceManager("data/monster-resources.xml");

  std::map<CL_String, CL_String> preset_properties;

  for(int i=0; i < 4; i++)
  	_monsters.push_back(new Monster(get_next_monster_position(),this, preset_properties));

}

MonsterGeneratorDemo::~MonsterGeneratorDemo()
{
  DEBUG_MSG("MonsterGeneratorDemo::~MonsterGeneratorDemo() - Called.")

  // Delete all monsters
  std::list<Monster*>::iterator it_go;
  for(it_go = _monsters.begin(); it_go != _monsters.end(); ++it_go)
  	delete (*it_go);
  _monsters.clear();

  close_editor();

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
		_window_editor->func_close().set(this, &MonsterGeneratorDemo::close_editor);

		//Add bbn for editing if one doesn't exist
		if(_active_net == 0x0)
		{
			_active_net = new BBN_Plot("data/plots/monster.xml");
			_active_net->prepare_bn();
		}

		if(_control_bbn != 0x0)
			delete(_control_bbn);

		//Add bbn_info component.
		_control_bbn = new BBN_Info(_window_editor,_active_net);
		_control_bbn->set_geometry(CL_Rect(20,40,580,280));

		//Add button to create monster.
		_button_generate =  new CL_PushButton(_window_editor);
		_button_generate->set_text("Generate monster!");
		_button_generate->set_geometry(CL_Rect(460,285,580,335));
		_button_generate->func_clicked().set(this,&MonsterGeneratorDemo::generate_monster);

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

/**
 * Closes the active editor window and components.
 *
 * @return
 */
bool MonsterGeneratorDemo::close_editor()
{
	if(_window_editor != 0x0)
	{
		delete(_window_editor);
		_window_editor = 0x0;
	}
	if(_control_bbn != 0x0)
	{
		//Will have been deleted by the above so reset pointer
		_control_bbn = 0x0;
	}
	if(_active_net != 0x0)
	{
		delete(_active_net);
		_active_net = 0x0;
	}
	if(_button_generate != 0x0)
	{
		//Will have been deleted by the above
		_button_generate = 0x0;
	}

	return(true);
}

/**
 * Uses the bayes net represented in _control_bbn to
 * generate a monster and display it on the screen.
 */
void MonsterGeneratorDemo::generate_monster(void)
{
	_monsters.push_back(new Monster(get_next_monster_position(), this, *(_control_bbn->get_bayes_net())));
}

/**
 * Returns the next grid location spare to place a
 * generated monster.
 *
 * @return
 */
CL_Pointf MonsterGeneratorDemo::get_next_monster_position(void)
{
	//Determine which box in the grid to used for the next monster
	if(_next_monster_x > 8)
	{
		_next_monster_x = 0;
		_next_monster_y++;
	}
	if(_next_monster_y > 3)
		_next_monster_y = 0;

	//Create a rect
	CL_Pointf pos(64.0f*_next_monster_x, 128.0f*_next_monster_y);

	_next_monster_x ++;

	return(pos);


}
