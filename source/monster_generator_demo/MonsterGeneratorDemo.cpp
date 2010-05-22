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
#include <map>

MonsterGeneratorDemo::MonsterGeneratorDemo(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("MonsterGeneratorDemo::MonsterGeneratorDemo(CL_DisplayWindow &) - Called.")

  //Get the resource manager
  rm = CL_ResourceManager("data/monster-resources.xml");

  std::map<CL_String, CL_String> preset_properties;

  for(int y=0; y < 4; y++)
    for(int x=0; x < 16; x++)
    {
      if(y==1)
    	  preset_properties["dwellings"] = "swamp";
      if(y==2)
    	  preset_properties["dwellings"] = "forest";
      if(y==3)
    	  preset_properties["dwellings"] = "desert";

      monsters.push_back(new Monster(CL_Pointf(64.0f*x,128.0f*y),this, preset_properties));
    }
}

MonsterGeneratorDemo::~MonsterGeneratorDemo()
{
  DEBUG_MSG("MonsterGeneratorDemo::~MonsterGeneratorDemo() - Called.")

  // Delete all monsters
  std::list<Monster*>::iterator it_go;
  for(it_go = monsters.begin(); it_go != monsters.end(); ++it_go)
	delete (*it_go);
  monsters.clear();
}

void MonsterGeneratorDemo::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));

  // Draw all monsters
  std::list<Monster*>::iterator it_go;
  for(it_go = monsters.begin(); it_go != monsters.end(); ++it_go)
    (*it_go)->draw(&gc);

  window.flip(1);
}

void MonsterGeneratorDemo::update()
{}

CL_ResourceManager* MonsterGeneratorDemo::get_rm()
{
	return(&rm);
}

/**
 *
 */
void MonsterGeneratorDemo::on_key_down(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_KEY_ESCAPE)
		exit_code = EXIT_MODULE_AND_LOAD_MAIN_MENU;
}
