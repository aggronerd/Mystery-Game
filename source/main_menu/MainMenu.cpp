/*
 * MainMenu.cpp
 *
 *  Created on: 15 Feb 2010
 *      Author: greg
 */

#include "MainMenu.h"
#include "../misc/logging.h"

MainMenu::MainMenu(CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("MainMenu::MainMenu(CL_DisplayWindow &) - Called.")

  //Get the resource manager
  rm = CL_ResourceManager("data/menu-resources.xml");

  background_image = CL_Image(gc,"background",&rm);
  background_image.set_scale(0.5f,0.5f);

}

MainMenu::~MainMenu()
{
  DEBUG_MSG("MainMenu::~MainMenu() - Called.")
}

void MainMenu::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));

  background_image.draw(gc,0,0);

  window.flip(1);
}

void MainMenu::update()
{
  //Nothing needs updating.
}
