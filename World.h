/*
 * World.h
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <ClanLib/display.h>
#include <list>
#include <ClanLib/core.h>

class IsometricGrid;
class Overlay;
class GameObject;

class World
{
  public:
          World(CL_DisplayWindow &);
          virtual ~World();

          int run();

          void addOverlay(Overlay *);
          void addGameObject(GameObject *);

          CL_GraphicContext* getGC(void);
          CL_ResourceManager* getRM(void);

  private:
          std::list<Overlay*> overlays;
          std::list<GameObject*> game_objects;

          CL_GraphicContext gc;
          CL_ResourceManager rm;
          CL_DisplayWindow window;

          CL_Slot slot_quit;
          CL_Slot slot_key_down;
          CL_Slot slot_key_up;
          CL_Slot slot_mouse_down;
          CL_Slot slot_mouse_up;
          CL_Slot slot_mouse_move;

          bool mouse_dragging;
          bool mouse_down;

          void onWindowClose(void);
          void onKeyDown(const CL_InputEvent &key, const CL_InputState &state);
          void onKeyUp(const CL_InputEvent &key, const CL_InputState &state);
          void onMouseDown(const CL_InputEvent &key, const CL_InputState &state);
          void onMouseUp(const CL_InputEvent &key, const CL_InputState &state);
          void onMouseMove(const CL_InputEvent &key, const CL_InputState &state);

          void initLevel(void);
          void draw(void);
          void update(void);


          unsigned int calculateTimeElapsed(void);

          bool quit;
  };
#endif /* WORLD_H_ */
