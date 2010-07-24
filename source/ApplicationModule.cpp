/**
 * @file ApplicationModule.cpp
 *
 * Created on: 15 Feb 2010
 *
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "ApplicationModule.h"
#include "misc/logging.h"
#include <ClanLib/display.h>

/**
 * Prepares object and displays loading message.
 */
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

  //Prepare the GUI
  gui_rm = CL_ResourceManager(CL_String8("data/gui/resources.xml"));
  gui.set_window_manager(wm);
  gui_theme.set_resources(gui_rm);
  gui.set_theme(gui_theme);
  gui.set_css_document("data/gui/theme.css");
  wm.func_repaint().set(this, &ApplicationModule::wm_repaint);

  exit_code = NO_EXIT;

  //Display loading text
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));
  draw_loading();
  window.flip(1);

}

/**
 *
 */
CL_GUIManager* ApplicationModule::get_gui_manager()
{
	return(&gui);
}

/**
 * Draws the loading screen on the graphics context.
 */
void ApplicationModule::draw_loading()
{
	CL_FontDescription desc;
	desc.set_typeface_name("Tahoma");
	desc.set_anti_alias(true);
	desc.set_height(30);
	CL_Font_System system_font = CL_Font_System(gc, desc);
	system_font.draw_text(gc, CL_Pointf(480.0f,280.0f), "Loading...", CL_Colorf(1.0f,1.0f,1.0f));
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
