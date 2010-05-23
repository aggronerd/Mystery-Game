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
	DEBUG_MSG("Monster::Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String,CL_String>) - Called.")

	std::map<CL_String,CL_String> bayes_values;

	DEBUG_MSG("Monster::Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String,CL_String>) - Calling other constructor with empty list...")
	Monster::Monster(location, parent, bayes_values);

}

Monster::Monster(CL_Pointf location, MonsterGeneratorDemo* parent, std::map<CL_String,CL_String> bayes_values)
{
	DEBUG_MSG("Monster::Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String,CL_String>) - Called.")

	//Fetch the resource manager which should contain all the sprites.
	CL_ResourceManager* rm = parent->get_rm();
	CL_GraphicContext gc = *(parent->get_gc());

	properties = new BBN_Plot("data/plots/monster.xml");
	properties->prepare_bn();

	//Set preset properties
	if(bayes_values.size() > 0)
	{
		std::map<CL_String,CL_String>::iterator it;
		for(it = bayes_values.begin(); it != bayes_values.end(); ++it)
			if(!properties->set_result((*it).first,(*it).second))
				Application::log(LOG_LEVEL_WARN, "Failed to set the value of a bayes network node: " + (*it).first + " = " + (*it).second);
	}

	//Determine sprites:
	legs = CL_Sprite(gc, properties->query_result("legs")->get_name(), rm);
	body = CL_Sprite(gc, properties->query_result("body")->get_name(), rm);
	mouth = CL_Sprite(gc, properties->query_result("mouth")->get_name(), rm);
	eyes = CL_Sprite(gc, properties->query_result("eyes")->get_name(), rm);
	arms = CL_Sprite(gc, properties->query_result("arms")->get_name(), rm);
	background = CL_Sprite(gc, properties->query_result("background")->get_name(), rm);
	extra = CL_Sprite(gc, properties->query_result("extra")->get_name(), rm);

	//Create the info window for inspecting the generated values
	CL_GUITopLevelDescription desc;
	desc.set_allow_resize(false);
	desc.set_title("Monster");
	desc.set_position(CL_Rect(0,0,600,300),false);
	desc.set_decorations(true);
	properties_window = new BBN_Info(parent->get_gui_manager(), desc, properties);
	properties_window->set_draggable(true);

	//Calculate destination using the image size
	destination.set_top_left(location);
	destination.set_size(static_cast<CL_Sizef>(background.get_size()));

	rm = 0x0;
}

Monster::~Monster()
{
	DEBUG_MSG("Monster::~Monster() - Called.")

	if(properties != 0x0)
		delete(properties);

	if(properties_window != 0x0)
		delete(properties_window);
}

void Monster::draw(CL_GraphicContext* gc)
{
	//Draw order is important
	background.draw(*gc, destination);
	arms.draw(*gc, destination);
	legs.draw(*gc, destination);
	body.draw(*gc, destination);
	mouth.draw(*gc, destination);
	eyes.draw(*gc, destination);
	extra.draw(*gc, destination);
}
