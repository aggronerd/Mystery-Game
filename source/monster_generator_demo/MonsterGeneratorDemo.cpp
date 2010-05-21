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

MonsterGeneratorDemo::MonsterGeneratorDemo(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("MonsterGeneratorDemo::MonsterGeneratorDemo(CL_DisplayWindow &) - Called.")

  //Get the resource manager
  rm = CL_ResourceManager("data/monster-resources.xml");

  monsters.push_back(new Monster(CL_Pointf(300,300),this));
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
