/*
 * ApplicationModule.cpp
 *
 *  Created on: 15 Feb 2010
 *      Author: greg
 */

#include "ApplicationModule.h"
#include "misc/logging.h"

ApplicationModule::ApplicationModule(CL_DisplayWindow &display_window) : window(display_window)
{
  DEBUG_MSG("ApplicationModule::ApplicationModule(CL_DisplayWindow) - Called.")

  // Get the graphic context
  gc = window.get_gc();

  //Prepare input slots
  slot_quit       = window.sig_window_close().connect(this, &ApplicationModule::onWindowClose);
  slot_key_down   = window.get_ic().get_keyboard().sig_key_down().connect(this, &ApplicationModule::onKeyDown);
  slot_key_up     = window.get_ic().get_keyboard().sig_key_up().connect(this, &ApplicationModule::onKeyUp);
  slot_mouse_down = window.get_ic().get_mouse().sig_key_down().connect(this, &ApplicationModule::onMouseDown);
  slot_mouse_up   = window.get_ic().get_mouse().sig_key_up().connect(this, &ApplicationModule::onMouseUp);
  slot_mouse_move = window.get_ic().get_mouse().sig_pointer_move().connect(this, &ApplicationModule::onMouseMove);

  //TODO: Implement this:
  mouse_dragging = false;
  mouse_down = false;

  exit_code = 0;

}

ApplicationModule::~ApplicationModule()
{
  DEBUG_MSG("ApplicationModule::~ApplicationModule() - Called.")
}

/**
 * Initiates the main loop.
 */
int ApplicationModule::run()
{
  // Run until someone presses escape.
  while (exit_code==0)
  {
    draw();
    update();
    // This call processes user input and other events
    CL_KeepAlive::process(0);
  }
  return(0);
}

/**
 * Calculate amount of time since the last call.
 */
unsigned int ApplicationModule::calculateTimeElapsed()
{
  static unsigned int last_time = 0;
  unsigned int new_time = CL_System::get_time();

  if(last_time == 0)
    last_time = new_time;

  int delta_time = (new_time - last_time);
  last_time = new_time;

  return(delta_time);
}

void ApplicationModule::onKeyUp(const CL_InputEvent &key, const CL_InputState &state)
{
  if(key.id == CL_KEY_ESCAPE)
  {
    exit_code = 2;
  }
}

void ApplicationModule::onWindowClose()
{
  exit_code = 1;
}

void ApplicationModule::onKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{}

void ApplicationModule::onMouseDown(const CL_InputEvent &key, const CL_InputState &state)
{}

void ApplicationModule::onMouseUp(const CL_InputEvent &key, const CL_InputState &state)
{}

void ApplicationModule::onMouseMove(const CL_InputEvent &key, const CL_InputState &state)
{}

CL_GraphicContext* ApplicationModule::getGC()
{
  return(&gc);
}
