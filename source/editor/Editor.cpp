/**
 * @file Editor.cpp
 *
 *  Created on: 15 Feb 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Editor.h"
#include "../misc/logging.h"

Editor::Editor(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("Editor::Editor(CL_DisplayWindow &) - Called.")


}

Editor::~Editor()
{
  DEBUG_MSG("Editor::~Editor() - Called.")
}

void Editor::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));

  //TODO: code.

  window.flip(1);
}

void Editor::update()
{
  //Nothing needs updating.
}
