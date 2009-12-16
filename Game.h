/*
 * Game.h
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#ifndef GAME_H_
#define GAME_H_

#include <ClanLib/display.h>
#include <list>
#include <ClanLib/core.h>

class IsometricGrid;
class Overlay;

class Game
{
  public:
          Game();
          virtual ~Game();
          int start(const std::vector<CL_String> &args);
          void addOverlay(Overlay *);
          CL_GraphicContext* getGC(void);
          CL_ResourceManager* getRM(void);

  private:
          std::list<Overlay*> overlays;
          CL_GraphicContext* gc;
          CL_ResourceManager* rm;
          void on_input_up(const CL_InputEvent &key, const CL_InputState &state);
          void on_window_close();
          bool quit;

  };
#endif /* GAME_H_ */
