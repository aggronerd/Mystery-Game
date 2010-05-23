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

#include "ApplicationModuleExitCode.h"
#include <ClanLib/core.h>
#include <ClanLib/gui.h>


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
  ApplicationModule(const CL_DisplayWindow &);
  virtual ~ApplicationModule();
  ApplicationModuleExitCode run(void); //Returns exit code
  CL_GraphicContext* get_gc(void);
  CL_GUIManager* get_gui_manager(void);
protected:
  virtual void draw(void) {};
  virtual void update(void) {};
  virtual void wm_repaint(void) {};
  ApplicationModuleExitCode exit_code;
  //The order of the following is important
  CL_DisplayWindow window;
  CL_GUIThemeDefault gui_theme;
  CL_ResourceManager gui_rm;
  CL_GUIWindowManagerTexture wm;
  CL_GUIManager gui;
  CL_GraphicContext gc;
  CL_Slot slot_quit;
  CL_Slot slot_key_down;
  CL_Slot slot_key_up;
  CL_Slot slot_mouse_down;
  CL_Slot slot_mouse_up;
  CL_Slot slot_mouse_move;
  void draw_loading(void);
  virtual void on_window_close(void);
  virtual void on_key_down(const CL_InputEvent &key, const CL_InputState &state);
  virtual void on_key_up(const CL_InputEvent &key, const CL_InputState &state);
  virtual void on_mouse_down(const CL_InputEvent &key, const CL_InputState &state);
  virtual void on_mouse_up(const CL_InputEvent &key, const CL_InputState &state);
  virtual void on_mouse_move(const CL_InputEvent &key, const CL_InputState &state);
  unsigned int get_time_elapsed(void);
};

#endif /* APPLICATIONMODULE_H_ */
