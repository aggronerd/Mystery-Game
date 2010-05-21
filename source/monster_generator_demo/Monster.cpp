/*
 * Monster.cpp
 *
 *  Created on: 21 May 2010
 *      Author: greg
 */

#include "Monster.h"
#include "../misc/logging.h"
#include "../bbn/BBN_Plot.h"
#include "../bbn/BBN_Option.h"
#include "MonsterGeneratorDemo.h"

/**
 * Loads the Bayes net for the object and sets the
 * sprites to use for each of the body components.
 */
Monster::Monster(CL_Pointf location, MonsterGeneratorDemo* parent)
{
	DEBUG_MSG("Monster::Monster() - Called.")

	//Fetch the resource manager which should contain all the sprites.
	CL_ResourceManager* rm = parent->get_rm();

	CL_GraphicContext gc = *(parent->get_gc());

	BBN_Plot properties("data/plots/monster.xml");
	properties.prepare_bn();

	//Determine sprites:
	legs = CL_Sprite(gc, properties.query_result("legs")->get_name(), rm);
	body = CL_Sprite(gc, properties.query_result("body")->get_name(), rm);
	mouth = CL_Sprite(gc, properties.query_result("mouth")->get_name(), rm);
	eyes = CL_Sprite(gc, properties.query_result("eyes")->get_name(), rm);
	arms = CL_Sprite(gc, properties.query_result("arms")->get_name(), rm);
	background = CL_Sprite(gc, properties.query_result("background")->get_name(), rm);
	extra = CL_Sprite(gc, properties.query_result("extra")->get_name(), rm);

	//Calculate destination using the image size
	destination.set_top_left(location);
	destination.set_size(static_cast<CL_Sizef>(background.get_size()));

	rm = 0x0;

}

Monster::~Monster()
{
	DEBUG_MSG("Monster::~Monster() - Called.")
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
