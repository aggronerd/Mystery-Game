/**
 * @file ApplicationModule.h
 *
 * Created on: 15 Feb 2010
 *
 * @author Gregory Doran <www.gregorydoran.co.uk>
 *
 */

#ifndef APPLICATIONMODULE_H_
#define APPLICATIONMODULE_H_

#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include "ApplicationModuleExitCode.h"

/**
 * An ApplicationModule represents part of the overall application
 * where all inherent classes would not expect to be instantiated
 * at the same time but share common components, such as a window
 * manager, gui object, graphics context, input slots, a "run"
 * function to initiate the loop and a class variable for breaking
 * the loop.
 *
 * This ensures that the editor and the game do not have to repeat
 * this common code and instead inherit this object.
 */
class ApplicationModule
{
public:
  ApplicationModule(CL_DisplayWindow &);
  virtual ~ApplicationModule();
  ApplicationModuleExitCode run(void); //Returns exit code
  CL_GraphicContext* getGC(void);
protected:
  virtual void draw(void) {};
  virtual void update(void) {};
  ApplicationModuleExitCode exit_code;
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
