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
		virtual void on_key_down(const CL_InputEvent &key, const CL_InputState &state);
		CL_ResourceManager rm;
		std::list<Monster*> monsters;
};

#endif /* MONSTERGENERATORDEMO_H_ */
