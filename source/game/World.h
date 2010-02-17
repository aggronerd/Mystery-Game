/**
 * @file World.h
 *
 *  Created on: 6 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include <ClanLib/sound.h>
#include <ClanLib/mikmod.h>
#include <ClanLib/vorbis.h>
#include <list>
#include "../ApplicationModule.h"

class IsometricGrid;
class Overlay;
class GameObject;

/**
 * The world class constructs and runs the game.
 */
class World : public ApplicationModule
{
  public:
          World(CL_DisplayWindow &);
          virtual ~World();
          void addOverlay(Overlay *);
          void addGameObject(GameObject *);
          CL_ResourceManager* getRM(void);
  private:
          std::list<Overlay*> overlays;
          std::list<GameObject*> game_objects;
          CL_ResourceManager rm;
          CL_SoundBuffer* music;
          CL_SoundOutput sound_output;
          void initLevel(void);
          void draw(void);
          void update(void);
  };
#endif /* WORLD_H_ */
