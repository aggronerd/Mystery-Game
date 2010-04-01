/**
 * @file ApplicationModule.cpp
 *
 * Created on: 15 Feb 2010
 *
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "ApplicationModule.h"
#include "misc/logging.h"

ApplicationModule::ApplicationModule(const CL_DisplayWindow &display_window) : window(display_window), wm(window)
{
  DEBUG_MSG("ApplicationModule::ApplicationModule(CL_DisplayWindow) - Called.")

  // Get the graphic context
  gc = window.get_gc();

  //Prepare input slots
  slot_quit       = window.sig_window_close().connect(this, &ApplicationModule::on_window_close);
  slot_key_down   = window.get_ic().get_keyboard().sig_key_down().connect(this, &ApplicationModule::on_key_down);
  slot_key_up     = window.get_ic().get_keyboard().sig_key_up().connect(this, &ApplicationModule::on_key_up);
  slot_mouse_down = window.get_ic().get_mouse().sig_key_down().connect(this, &ApplicationModule::on_mouse_down);
  slot_mouse_up   = window.get_ic().get_mouse().sig_key_up().connect(this, &ApplicationModule::on_mouse_up);
  slot_mouse_move = window.get_ic().get_mouse().sig_pointer_move().connect(this, &ApplicationModule::on_mouse_move);

  //Prepare the gui
  gui_rm = CL_ResourceManager("data/gui/resources.xml");
  gui.set_window_manager(wm);
  gui_theme.set_resources(gui_rm);
  gui.set_theme(gui_theme);
  gui.set_css_document("data/gui/theme.css");
  wm.func_repaint().set(this, &ApplicationModule::wm_repaint);

  exit_code = NO_EXIT;

}

ApplicationModule::~ApplicationModule()
{
  DEBUG_MSG("ApplicationModule::~ApplicationModule() - Called.")
}

/**
 * Initiates the main loop. Does not render the GUI
 * it is down the the inherent classes to do so.
 */
ApplicationModuleExitCode ApplicationModule::run()
{
  // Run until someone presses escape.
  while (exit_code==NO_EXIT)
  {
    update();
    draw();
    CL_KeepAlive::process(10);
  }
  return(exit_code);
}

/**
 * Calculate amount of time since the last call.
 */
unsigned int ApplicationModule::get_time_elapsed()
{
  //TODO: Don't think this will work as it is inherited.
  static unsigned int last_time = 0;
  unsigned int new_time = CL_System::get_time();

  if(last_time == 0)
    last_time = new_time;

  int delta_time = (new_time - last_time);
  last_time = new_time;

  return(delta_time);
}

/**
 *
 */
void ApplicationModule::on_key_up(const CL_InputEvent &key, const CL_InputState &state)
{}

/**
 *
 */
void ApplicationModule::on_window_close()
{
  exit_code = EXIT_APPLICATION;
}

/**
 *
 */
void ApplicationModule::on_key_down(const CL_InputEvent &key, const CL_InputState &state)
{}

/**
 *
 */
void ApplicationModule::on_mouse_down(const CL_InputEvent &key, const CL_InputState &state)
{}

/**
 *
 */
void ApplicationModule::on_mouse_up(const CL_InputEvent &key, const CL_InputState &state)
{}

/**
 *
 */
void ApplicationModule::on_mouse_move(const CL_InputEvent &key, const CL_InputState &state)
{}

/**
 *
 */
CL_GraphicContext* ApplicationModule::get_gc()
{
  return(&gc);
}
