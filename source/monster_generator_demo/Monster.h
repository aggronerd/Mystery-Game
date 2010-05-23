/*
 * Monster.h
 *
 *  Created on: 21 May 2010
 *      Author: greg
 */

#ifndef MONSTER_H_
#define MONSTER_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <map>

class BBN_Info;
class BBN_Plot;

class MonsterGeneratorDemo;

class Monster
{
	public:
		Monster(CL_Pointf, MonsterGeneratorDemo*);
		Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String,CL_String>);
		virtual ~Monster();
		void draw(CL_GraphicContext* gc);

	protected:
		CL_Sprite legs;
		CL_Sprite body;
		CL_Sprite mouth;
		CL_Sprite eyes;
		CL_Sprite arms;
		CL_Sprite background;
		CL_Sprite extra;
		CL_Rectf destination;
		BBN_Info* properties_window;
		BBN_Plot* properties;
};

#endif /* MONSTER_H_ */
