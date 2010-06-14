/**
 * @file MainMenu.cpp
 *
 *  Created on: 15 Feb 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "MainMenu.h"
#include "../misc/logging.h"

MainMenu::MainMenu(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("MainMenu::MainMenu(CL_DisplayWindow &) - Called.")

  //Get the resource managers
  menu_rm = CL_ResourceManager("data/menu-resources.xml");

  //Set the background image
  background_image = CL_Image(gc,"background",&menu_rm);
  float bg_scale_x = static_cast<float>(gc.get_width()) / background_image.get_width();
  float bg_scale_y = static_cast<float>(gc.get_height()) / background_image.get_height();
  background_image.set_scale(bg_scale_x,bg_scale_y);

  //Create window
  CL_DisplayWindowDescription desc;
  desc.set_allow_resize(false);
  desc.set_title("Main Menu");
  desc.set_position(CL_Rect(window.get_viewport().get_width()-210,
                            window.get_viewport().get_height()-140,
                            window.get_viewport().get_width()-10,
                            window.get_viewport().get_height()-10),true);
  desc.set_decorations(true);
  menu_window = new CL_Window(&gui,desc);

  //Create buttons
  button_mystery = new CL_PushButton(menu_window);
  button_mystery->set_geometry(CL_Rect(10, 30, CL_Size(180, 40)));
  button_mystery->set_text("Murder Mystery");
  button_mystery->func_clicked().set(this,&MainMenu::on_clicked_button_mystery_generator);
  button_monster = new CL_PushButton(menu_window);
  button_monster->set_geometry(CL_Rect(10, 80, CL_Size(180, 40)));
  button_monster->set_text("Monster Generator");
  button_monster->func_clicked().set(this,&MainMenu::on_clicked_button_monster_generator);

  menu_window->func_close().set(this, &MainMenu::on_quit);
  menu_window->set_draggable(true);

}

MainMenu::~MainMenu()
{
  DEBUG_MSG("MainMenu::~MainMenu() - Called.")

  delete button_mystery;
  delete button_monster;
  delete menu_window;
}

/**
 * Draws the main menu images and gui to the window.
 */
void MainMenu::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));
  background_image.draw(gc,0,0);
  gui.exec(false);
  wm.draw_windows(gc);
  window.flip(1);
}



bool MainMenu::on_quit()
{
  exit_code = EXIT_APPLICATION;
  return(true);
}

void MainMenu::on_clicked_button_mystery_generator()
{
  exit_code = EXIT_MODULE_AND_LOAD_MYSTERY_GENERATOR;
}

void MainMenu::on_clicked_button_monster_generator()
{
  exit_code = EXIT_MODULE_AND_LOAD_MONSTER_GENERATOR;
}
