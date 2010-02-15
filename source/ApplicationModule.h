/*
 * ApplicationModule.h
 *
 *  Created on: 15 Feb 2010
 *      Author: greg
 */

#ifndef APPLICATIONMODULE_H_
#define APPLICATIONMODULE_H_

#include <ClanLib/display.h>
#include <ClanLib/core.h>

/**
 * An application is a generalised class for a part
 * of the application which requires it's own graphics
 * context and design. This could be a game in itself
 * or the player for a cutscene.
 */
class ApplicationModule
{
public:
  ApplicationModule(CL_DisplayWindow &);
  virtual ~ApplicationModule();
  int run(void); //Returns exit code
  CL_GraphicContext* getGC(void);
protected:
  virtual void draw(void) {};
  virtual void update(void) {};
  int exit_code;
  CL_DisplayWindow window;
  CL_GraphicContext gc;
  CL_Slot slot_quit;
  CL_Slot slot_key_down;
  CL_Slot slot_key_up;
  CL_Slot slot_mouse_down;
  CL_Slot slot_mouse_up;
  CL_Slot slot_mouse_move;
  bool mouse_dragging;
  bool mouse_down;
  virtual void onWindowClose(void);
  virtual void onKeyDown(const CL_InputEvent &key, const CL_InputState &state);
  virtual void onKeyUp(const CL_InputEvent &key, const CL_InputState &state);
  virtual void onMouseDown(const CL_InputEvent &key, const CL_InputState &state);
  virtual void onMouseUp(const CL_InputEvent &key, const CL_InputState &state);
  virtual void onMouseMove(const CL_InputEvent &key, const CL_InputState &state);
  unsigned int calculateTimeElapsed(void);
};

#endif /* APPLICATIONMODULE_H_ */
