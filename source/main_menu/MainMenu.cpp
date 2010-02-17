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
  desc.set_position(CL_Rect(window.get_geometry().get_width()-210,
                            window.get_geometry().get_height()-190,
                            window.get_geometry().get_width()-10,
                            window.get_geometry().get_height()-10),false);
  desc.set_decorations(true);
  menu_window = new CL_Window(&gui,desc);

  //Create buttons
  button_new_game = new CL_PushButton(menu_window);
  button_new_game->set_geometry(CL_Rect(10, 30, CL_Size(180, 40)));
  button_new_game->set_text("New Game");
  button_new_game->func_clicked().set(this,&MainMenu::on_clicked_button_new_game);
  button_editor = new CL_PushButton(menu_window);
  button_editor->set_geometry(CL_Rect(10, 80, CL_Size(180, 40)));
  button_editor->set_text("Editor");
  button_editor->func_clicked().set(this,&MainMenu::on_clicked_button_editor);
  button_options = new CL_PushButton(menu_window);
  button_options->set_geometry(CL_Rect(10, 130, CL_Size(180, 40)));
  button_options->set_text("Options");

  menu_window->func_close().set(this, &MainMenu::on_quit);
  menu_window->set_draggable(true);

}

MainMenu::~MainMenu()
{
  DEBUG_MSG("MainMenu::~MainMenu() - Called.")

  delete button_new_game;
  delete button_editor;
  delete button_options;
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

void MainMenu::on_clicked_button_editor()
{
  exit_code = EXIT_MODULE_AND_LOAD_EDITOR;
}

void MainMenu::on_clicked_button_new_game()
{
  exit_code = EXIT_MODULE_AND_LOAD_GAME;
}
