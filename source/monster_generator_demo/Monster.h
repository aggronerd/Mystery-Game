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

class BBN_Plot;
class MonsterGeneratorDemo;

class Monster
{
	public:
		Monster(CL_Pointf, MonsterGeneratorDemo*);
		Monster(CL_Pointf, MonsterGeneratorDemo*, std::map<CL_String,CL_String>);
		Monster(CL_Pointf, MonsterGeneratorDemo*, BBN_Plot*);
		virtual ~Monster();
		void draw(CL_GraphicContext* gc);

	protected:
		CL_Sprite _legs;
		CL_Sprite _body;
		CL_Sprite _mouth;
		CL_Sprite _eyes;
		CL_Sprite _arms;
		CL_Sprite _background;
		CL_Sprite _extra;
		CL_Rectf _destination;
		BBN_Plot* _properties;
		MonsterGeneratorDemo* _parent;
		void load_sprites(void);
};

#endif /* MONSTER_H_ */
