/**
 * @file World.h
 *
 *  Created on: 6 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/sound.h>
#include <ClanLib/mikmod.h>
#include <ClanLib/vorbis.h>
#include <list>
#include "../ApplicationModule.h"
#include "Scene.h"

class IsometricGrid;
class PlayerCharacter;
class Overlay;
class Scene;

/**
 * The world class constructs and runs the game.
 */
class World : public ApplicationModule
{
  public:
          World(const CL_DisplayWindow &);
          virtual ~World();
          void add_overlay(Overlay*);
          Scene* get_active_scene(void);
          void add_scene(Scene*);
          CL_ResourceManager* get_rm(void);

  private:
          std::list<Overlay*> overlays;
          std::list<Scene*> scenes;
          Scene* active_scene;
          PlayerCharacter* player_character;
          CL_ResourceManager rm;
          CL_SoundBuffer* music;
          CL_SoundOutput sound_output;
          bool mouse_dragging;
          bool left_mouse_button_down;
          void init_level(void);
          void draw(void);
          void update(void);
          virtual void on_mouse_down(const CL_InputEvent &, const CL_InputState &);
          virtual void on_mouse_up(const CL_InputEvent &, const CL_InputState &);
          virtual void on_mouse_move(const CL_InputEvent &, const CL_InputState &);
};
#endif /* WORLD_H_ */
