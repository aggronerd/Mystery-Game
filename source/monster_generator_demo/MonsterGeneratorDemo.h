/*
 * MonsterGeneratorDemo.h
 *
 *  Created on: 21 May 2010
 *      Author: greg
 */

#ifndef MONSTERGENERATORDEMO_H_
#define MONSTERGENERATORDEMO_H_

#include "../ApplicationModule.h"
#include <list>

class Monster;
class BBN_Info;
class BBN_Plot;

/**
 * The monster generator demo aims to test how Bayes nets
 * can be use to determine cohesive properties of randomly
 * generated objects. In this case monsters. Each time the
 * object is instantiated so is a Bayes network and from
 * this a new kind of monster is generated.
 */
class MonsterGeneratorDemo : public ApplicationModule
{
	public:
		MonsterGeneratorDemo(const CL_DisplayWindow &);
		virtual ~MonsterGeneratorDemo();
		CL_ResourceManager* get_rm(void);
	protected:
		void draw(void);
		void update(void);
		void show_editor(void);
		virtual void on_key_down(const CL_InputEvent &key, const CL_InputState &state);
		CL_ResourceManager _rm;
		std::list<Monster*> _monsters;
		CL_Window* _window_editor;
		BBN_Info* _control_bbn;
		BBN_Plot* _active_net; //We hold on to this because we must destroy it.
};

#endif /* MONSTERGENERATORDEMO_H_ */
