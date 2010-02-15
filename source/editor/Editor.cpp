/*
 * Editor.cpp
 *
 *  Created on: 15 Feb 2010
 *      Author: greg
 */

#include "Editor.h"
#include "../misc/logging.h"

Editor::Editor(CL_DisplayWindow &display_window) : window(display_window), quit(false)
{
  DEBUG_MSG("Editor::Editor(CL_DisplayWindow &) - Called.")

  //Get the graphics context
  //gc = window.get_gc;

}

Editor::~Editor()
{
  // TODO Auto-generated destructor stub
}
