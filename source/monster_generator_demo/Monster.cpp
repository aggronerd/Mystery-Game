/*
 * Monster.cpp
 *
 *  Created on: 21 May 2010
 *      Author: greg
 */

#include "Monster.h"
#include "../misc/logging.h"
#include "../bbn/BBN_Option.h"
#include "MonsterGeneratorDemo.h"
#include "../Application.h"
#include "../bbn/BBN_Info.h"
#include "../bbn/BBN_Plot.h"

/**
 * Loads the Bayes net for the object and sets the
 * sprites to use for each of the body components.
 */
Monster::Monster(CL_Pointf location, MonsterGeneratorDemo* parent)
{
	DEBUG_MSG("Monster::Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String8,CL_String8>) - Called.")

	std::map<CL_String8,CL_String8> bayes_values;

	DEBUG_MSG("Monster::Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String8,CL_String8>) - Calling other constructor with empty list...")
	Monster::Monster(location, parent, bayes_values);

}

/**
 * Generates monster from the provided bayes net. Makes a copy.
 */
Monster::Monster(CL_Pointf location, MonsterGeneratorDemo* parent, BBN_Plot* bbn)
{
	DEBUG_MSG("Monster::Monster(CL_Pointf, MonsterGeneratorDemo*, BBN_Plot*) - Called.")

	_parent = parent;

	//Create a new instance of the bayes net.
	_properties = new BBN_Plot(bbn->get_file_name());
	_properties->prepare_bn();
	_properties->clone_results(bbn);

	load_sprites();

	//Calculate destination using the image size
	_destination.set_top_left(location);
	_destination.set_size(static_cast<CL_Sizef>(_background.get_size()));
}

Monster::Monster(CL_Pointf location, MonsterGeneratorDemo* parent, std::map<CL_String8,CL_String8> bayes_values)
{
	DEBUG_MSG("Monster::Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String8,CL_String8>) - Called.")

	_parent = parent;

	//Load the bayes net for generation
	_properties = new BBN_Plot("data/plots/monster.xml");
	_properties->prepare_bn();

	//Set preset properties
	if(bayes_values.size() > 0)
	{
		std::map<CL_String8,CL_String8>::iterator it;
		for(it = bayes_values.begin(); it != bayes_values.end(); ++it)
			if(!_properties->set_result((*it).first,(*it).second))
				Application::log(LOG_LEVEL_WARN, "Failed to set the value of a bayes network node: " + (*it).first + " = " + (*it).second);
	}

	load_sprites();

	//Calculate destination using the image size
	_destination.set_top_left(location);
	_destination.set_size(static_cast<CL_Sizef>(_background.get_size()));

}

void Monster::load_sprites()
{
	//Fetch the resource manager which should contain all the sprites.
	CL_ResourceManager* rm = _parent->get_rm();
	CL_GraphicContext gc = *(_parent->get_gc());

	//Determine sprites:
	_legs = CL_Sprite(gc, _properties->query_result("legs")->get_name(), rm);
	_body = CL_Sprite(gc, _properties->query_result("body")->get_name(), rm);
	_mouth = CL_Sprite(gc, _properties->query_result("mouth")->get_name(), rm);
	_eyes = CL_Sprite(gc, _properties->query_result("eyes")->get_name(), rm);
	_arms = CL_Sprite(gc, _properties->query_result("arms")->get_name(), rm);
	_background = CL_Sprite(gc, _properties->query_result("background")->get_name(), rm);
	_extra = CL_Sprite(gc, _properties->query_result("extra")->get_name(), rm);

	rm = 0x0;
}

Monster::~Monster()
{
	DEBUG_MSG("Monster::~Monster() - Called.")

	if(_properties != 0x0)
		delete(_properties);

	_parent = 0x0;
}

void Monster::draw(CL_GraphicContext* gc)
{
	//Draw order is important
	_background.draw(*gc, _destination);
	_arms.draw(*gc, _destination);
	_legs.draw(*gc, _destination);
	_body.draw(*gc, _destination);
	_mouth.draw(*gc, _destination);
	_eyes.draw(*gc, _destination);
	_extra.draw(*gc, _destination);
}
